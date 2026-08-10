#!/usr/bin/env bash
# Download the latest GitHub Actions firmware artifact for this repo and
# flash it to one or both halves. Uses udisks2 automount (nixos default:
# /run/media/$USER/<label>) to auto-detect when a nice!nano bootloader
# drive appears, then copies the correct .uf2 and waits for the reboot.
#
# Usage:
#   scripts/flash.sh                  # both halves, right then left
#   scripts/flash.sh right            # right only
#   scripts/flash.sh left             # left only
#   scripts/flash.sh right left       # explicit order
#   scripts/flash.sh --reset both     # settings_reset then firmware, each half
#
# Env overrides:
#   BRANCH=main    workflow branch to pull the artifact from
#   RUN_ID=<id>    specific gh Actions run id (skips the latest-lookup)
#
# After launching, you don't need to type again — the script polls for
# the UF2 mount. Physically double-tap RST on each half when prompted.

set -euo pipefail
shopt -s nullglob

REPO="jackruder/zmk-config-dactyl"
WORKFLOW="build.yml"
BRANCH="${BRANCH:-main}"
ARTIFACT_NAME="firmware"
MOUNT_ROOTS=("/run/media/$USER" "/media/$USER" "/mnt")

WORK_DIR=""
cleanup() { [ -n "$WORK_DIR" ] && [ -d "$WORK_DIR" ] && rm -rf "$WORK_DIR"; }
trap cleanup EXIT

usage() { sed -n '2,20p' "$0" | sed 's/^# \{0,1\}//'; }

DO_RESET=0
TARGETS=()
while [ $# -gt 0 ]; do
    case "$1" in
        --reset)         DO_RESET=1 ;;
        -h|--help)       usage; exit 0 ;;
        right|left|both) TARGETS+=("$1") ;;
        *) echo "unknown arg: $1" >&2; usage >&2; exit 2 ;;
    esac
    shift
done

ORDER=()
if [ ${#TARGETS[@]} -eq 0 ]; then
    ORDER=(right left)
else
    for t in "${TARGETS[@]}"; do
        case "$t" in
            both)  ORDER+=(right left) ;;
            right) ORDER+=(right) ;;
            left)  ORDER+=(left) ;;
        esac
    done
fi

command -v gh >/dev/null 2>&1 || { echo "gh CLI not installed" >&2; exit 1; }
gh auth status >/dev/null 2>&1 || {
    echo "gh not authenticated — run: gh auth login" >&2; exit 1;
}

if [ -n "${RUN_ID:-}" ]; then
    run_id="$RUN_ID"
    echo "» Using RUN_ID=$run_id"
else
    echo "» Finding latest successful $WORKFLOW run on $BRANCH…"
    run_id=$(gh run list --repo "$REPO" --workflow "$WORKFLOW" \
        --branch "$BRANCH" --status success --limit 1 \
        --json databaseId --jq '.[0].databaseId')
    [ -n "$run_id" ] || { echo "no successful runs found" >&2; exit 1; }
    echo "» Using run $run_id"
fi

WORK_DIR=$(mktemp -d -t zmk-fw-XXXXXX)
echo "» Downloading $ARTIFACT_NAME → $WORK_DIR"
gh run download "$run_id" --repo "$REPO" -n "$ARTIFACT_NAME" -D "$WORK_DIR"

pick_uf2() {
    local pattern="$1"
    local -a hits=("$WORK_DIR"/**/$pattern "$WORK_DIR"/$pattern)
    for h in "${hits[@]}"; do
        [ -f "$h" ] && { printf '%s' "$h"; return 0; }
    done
    return 1
}
# nullglob + recursive is off by default in bash; enable globstar for **
shopt -s globstar

LEFT_UF2=$(pick_uf2  '*dactyl_manuform_4x6_left*.uf2')  || { echo "missing left uf2 in artifact" >&2; exit 1; }
RIGHT_UF2=$(pick_uf2 '*dactyl_manuform_4x6_right*.uf2') || { echo "missing right uf2 in artifact" >&2; exit 1; }
RESET_UF2=""
if [ "$DO_RESET" -eq 1 ]; then
    RESET_UF2=$(pick_uf2 '*settings_reset*.uf2') || {
        echo "missing settings_reset uf2 in artifact" >&2; exit 1
    }
fi

echo "  left:  $(basename "$LEFT_UF2")"
echo "  right: $(basename "$RIGHT_UF2")"
[ -n "$RESET_UF2" ] && echo "  reset: $(basename "$RESET_UF2")"

find_uf2_mount() {
    for root in "${MOUNT_ROOTS[@]}"; do
        [ -d "$root" ] || continue
        for m in "$root"/*/; do
            [ -f "${m}INFO_UF2.TXT" ] && { printf '%s' "${m%/}"; return 0; }
        done
    done
    return 1
}

wait_for_mount() {
    local m elapsed=0
    printf '  waiting for UF2 mount' >&2
    while true; do
        if m=$(find_uf2_mount); then
            printf ' → %s\n' "$m" >&2
            printf '%s' "$m"
            return 0
        fi
        sleep 0.5
        elapsed=$((elapsed+1))
        if [ $((elapsed % 20)) -eq 0 ]; then printf '.' >&2; fi
    done
}

wait_for_unmount() {
    local m="$1"
    printf '  flashing / awaiting reboot' >&2
    while [ -e "$m/INFO_UF2.TXT" ]; do
        sleep 0.5
        printf '.' >&2
    done
    printf ' done\n' >&2
}

flash_one() {
    local label="$1" uf2="$2"
    echo
    echo "==> $label"
    if find_uf2_mount >/dev/null; then
        echo "  (a UF2 drive is already mounted — using it)"
    else
        echo "  Double-tap RST on the $label half now."
    fi
    local mount
    mount=$(wait_for_mount)
    cp "$uf2" "$mount/"
    sync
    wait_for_unmount "$mount"
    # small settle time so the next iteration doesn't see the just-departed mount
    sleep 1
}

for side in "${ORDER[@]}"; do
    if [ "$DO_RESET" -eq 1 ]; then
        flash_one "$side (settings_reset)" "$RESET_UF2"
        echo "  wait ~5s for reset firmware to boot, then double-tap RST again for the real firmware."
        sleep 3
    fi
    case "$side" in
        right) flash_one "$side" "$RIGHT_UF2" ;;
        left)  flash_one "$side" "$LEFT_UF2" ;;
    esac
done

echo
echo "✓ All flashes complete."

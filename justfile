# Regenerate docs/keymap.html — tabbed per-layer keymap reference.
docs:
    ./scripts/gen_keymap_reference.sh

# Push HEAD, wait for CI to build firmware, notify + flash on success.
ship:
    #!/usr/bin/env bash
    set -euo pipefail

    echo "» Pushing…"
    git push

    sha=$(git rev-parse HEAD)
    echo "» Looking for CI run for $sha…"

    run_id=""
    for i in {1..30}; do
        run_id=$(gh run list --workflow build.yml --branch main --limit 10 \
            --json databaseId,headSha \
            --jq ".[] | select(.headSha == \"$sha\") | .databaseId" | head -1)
        [ -n "$run_id" ] && break
        sleep 2
    done
    [ -n "$run_id" ] || { echo "no CI run found for $sha after 60s" >&2; exit 1; }

    echo "» Watching run $run_id…"
    if gh run watch "$run_id" --exit-status; then
        notify-send -u normal "ZMK build ready" \
            "Firmware built for $(git log -1 --format=%s HEAD). Flashing now."
        RUN_ID="$run_id" ./scripts/flash.sh
    else
        notify-send -u critical "ZMK build failed" \
            "Run $run_id failed. Check: gh run view $run_id"
        exit 1
    fi

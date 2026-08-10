#!/usr/bin/env bash
# Regenerate docs/keymap.html: a single self-contained page with one
# tab per layer, each rendering the keymap as an SVG via keymap-drawer.
# Uses the physical layout in the shield dtsi so key positions and
# rotations match the actual dactyl.
#
# Requires: uv (uvx). Run from anywhere; paths resolve relative to repo.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
KEYMAP="$REPO_ROOT/config/dactyl_manuform_4x6.keymap"
DTS="$REPO_ROOT/config/boards/shields/dactyl_manuform_4x6/dactyl_manuform_4x6.dtsi"
OUT="$REPO_ROOT/docs/keymap.html"

YAML=$(mktemp -t kdyaml-XXXXXX.yaml)
trap 'rm -f "$YAML"' EXIT

echo "» Parsing $KEYMAP"
uvx --from keymap-drawer keymap -c "$REPO_ROOT/scripts/keymap_drawer.yaml" parse -z "$KEYMAP" -o "$YAML"

mkdir -p "$(dirname "$OUT")"

echo "» Rendering layers and assembling HTML"
python3 - "$YAML" "$DTS" "$OUT" "$REPO_ROOT/scripts/keymap_drawer.yaml" <<'PYEOF'
import sys, subprocess, html
from pathlib import Path

yaml_path, dts_path, out_path, config_path = sys.argv[1:5]

# Get layer names in declaration order without needing PyYAML installed.
# The parsed keymap has "  <LayerName>:" at column 3, layer body deeper.
layers = []
for line in Path(yaml_path).read_text().splitlines():
    if line.startswith("  ") and not line.startswith("   ") and line.rstrip().endswith(":"):
        # Skip the top-level "layers:" key itself (has 0 indent)
        name = line.strip()[:-1]
        # First "  X:" after "layers:" onward — skip anything before layers:
        layers.append(name)
# The parse output is: layout: ..., layers: <block>, then combos etc.
# The above pattern also matches "layout:" contents; filter to entries
# that appeared after the "layers:" line.
raw = Path(yaml_path).read_text().splitlines()
in_layers = False
layers = []
for line in raw:
    if line.rstrip() == "layers:":
        in_layers = True
        continue
    if in_layers:
        if line and not line.startswith(" "):
            break  # left the layers block
        if line.startswith("  ") and not line.startswith("   ") and line.rstrip().endswith(":"):
            layers.append(line.strip()[:-1])

print(f"    found layers: {', '.join(layers)}", file=sys.stderr)

def slug(name):
    return name.lower().replace(" ", "-")

svgs = {}
for name in layers:
    print(f"    drawing {name}", file=sys.stderr)
    result = subprocess.run(
        ["uvx", "--from", "keymap-drawer", "keymap",
         "-c", config_path, "draw",
         yaml_path, "-d", dts_path, "--select-layers", name],
        capture_output=True, text=True, check=True,
    )
    # Strip XML preamble so we can inline; keymap-drawer omits it anyway,
    # but be defensive.
    svg = result.stdout
    if svg.startswith("<?xml"):
        svg = svg.split("?>", 1)[1].lstrip()
    svgs[name] = svg

tab_buttons = "\n".join(
    f'  <button class="tab" data-target="{slug(n)}">{html.escape(n)}</button>'
    for n in layers
)
panels = "\n".join(
    f'<section class="layer" id="{slug(n)}">\n{svgs[n]}\n</section>'
    for n in layers
)

page = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Oponn Keymap Reference</title>
<style>
:root {{
  --bg: #1a1b26;
  --panel: #24283b;
  --edge: #414868;
  --text: #c0caf5;
  --muted: #a9b1d6;
  --accent: #7aa2f7;
}}
* {{ box-sizing: border-box; }}
html, body {{ margin: 0; padding: 0; background: var(--bg); color: var(--text); }}
body {{
  font-family: -apple-system, "SF Pro Text", "Segoe UI", system-ui, sans-serif;
  padding: 0.75rem 1rem 1.5rem;
  min-height: 100vh;
}}
header {{
  display: flex;
  align-items: baseline;
  gap: 0.75rem;
  margin-bottom: 0.75rem;
}}
h1 {{ font-size: 1rem; font-weight: 500; margin: 0; color: var(--muted); }}
.hint {{ font-size: 0.8rem; color: var(--muted); opacity: 0.6; }}
.tabs {{
  display: flex; flex-wrap: wrap; gap: 0.25rem;
  border-bottom: 1px solid var(--edge);
  margin-bottom: 1rem;
}}
.tab {{
  padding: 0.4rem 0.85rem;
  border: none;
  background: transparent;
  color: var(--muted);
  font-size: 0.85rem;
  font-family: inherit;
  cursor: pointer;
  border-radius: 4px 4px 0 0;
  border-bottom: 2px solid transparent;
}}
.tab:hover {{ color: var(--text); background: var(--panel); }}
.tab.active {{
  color: var(--text);
  background: var(--panel);
  border-bottom-color: var(--accent);
}}
.layer {{ display: none; }}
.layer.active {{ display: block; }}
.layer svg {{
  display: block;
  max-width: 100%;
  height: auto;
  margin: 0 auto;
}}
</style>
</head>
<body>
<header>
  <h1>Oponn keymap</h1>
  <span class="hint">← / → to switch layers</span>
</header>
<nav class="tabs">
{tab_buttons}
</nav>
{panels}
<script>
const tabs = document.querySelectorAll(".tab");
const panels = document.querySelectorAll(".layer");
function show(idx) {{
  tabs.forEach((t, i) => t.classList.toggle("active", i === idx));
  panels.forEach((p, i) => p.classList.toggle("active", i === idx));
  history.replaceState(null, "", "#" + tabs[idx].dataset.target);
}}
tabs.forEach((t, i) => t.addEventListener("click", () => show(i)));
document.addEventListener("keydown", (e) => {{
  const cur = [...tabs].findIndex(t => t.classList.contains("active"));
  if (e.key === "ArrowRight") show((cur + 1) % tabs.length);
  if (e.key === "ArrowLeft")  show((cur - 1 + tabs.length) % tabs.length);
}});
// Deep-link support: open #layer-name
const initial = location.hash.slice(1);
const initIdx = Math.max(0, [...tabs].findIndex(t => t.dataset.target === initial));
show(initIdx);
</script>
</body>
</html>
"""

Path(out_path).write_text(page)
print(f"    wrote {out_path} ({len(page):,} bytes, {len(layers)} layers)", file=sys.stderr)
PYEOF

echo "✓ $OUT"

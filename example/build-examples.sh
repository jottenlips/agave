#!/usr/bin/env bash
set -euo pipefail

# Build the example site with theme preview pages
# Run from the repo root: bash example/build-examples.sh

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
DOCS_DIR="$SCRIPT_DIR/../docs"
AGAVE="$SCRIPT_DIR/../_build/default/bin/Agave.exe"
cd "$SCRIPT_DIR"

echo "==> Building main site..."
"$AGAVE" -m markdown -p public

THEMES="arrakis caladan giediprime ix salusasecundus spice"

for theme in $THEMES; do
  echo "==> Building theme preview: $theme"
  mkdir -p "public/themes/$theme"
  "$AGAVE" -m theme-preview -p "public/themes/$theme" -t "$theme"
  # Fix stylesheet path: theme HTML uses /styles.css but we need a relative path
  sed -i '' 's|href="/styles.css"|href="styles.css"|' "public/themes/$theme/index.html"
done

echo "==> Copying theme previews to docs/themes/..."
rm -rf "$DOCS_DIR/themes"
cp -r public/themes "$DOCS_DIR/themes"

echo "==> Done! All theme previews built."

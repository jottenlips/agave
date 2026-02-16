#!/usr/bin/env bash
set -euo pipefail

# Build the example site with theme preview pages
# Run from the example/ directory: bash build-examples.sh

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

echo "==> Building main site..."
agave -m markdown -p public

THEMES="arrakis caladan giediprime ix salusasecundus spice randomphoto"

for theme in $THEMES; do
  echo "==> Building theme preview: $theme"
  mkdir -p "public/themes/$theme"
  agave -m theme-preview -p "public/themes/$theme" -t "$theme"
  # Fix stylesheet path: theme HTML uses /styles.css but we need a relative path
  sed -i '' 's|href="/styles.css"|href="styles.css"|' "public/themes/$theme/index.html"
done

echo "==> Done! All theme previews built."

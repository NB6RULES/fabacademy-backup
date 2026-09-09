#!/usr/bin/env bash
# Always run this instead of a bare `hugo` build. It refreshes every zip-download
# manifest (so newly added files under static/files/<dir> show up automatically,
# and anything gitignored stays excluded) before building the site.
set -e
cd "$(dirname "$0")/.."

for dir in data/zipmanifests/*.json; do
  name=$(basename "$dir" .json)
  python scripts/generate_zip_manifest.py "$name"
done

hugo --minify "$@"

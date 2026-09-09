"""
Builds a gitignore-aware file manifest for a folder under static/files/, so the
client-side zip-download button never ships secrets or build junk.

Walks the target folder, collects every .gitignore found in it (root-to-leaf
order, scoped to the directory it lives in, just like real git), and excludes
any file that matches. Writes the surviving relative paths to
data/zipmanifests/<name>.json for the `zipdownload` shortcode to read at build time.

Usage: python scripts/generate_zip_manifest.py week-20
"""
import json
import os
import sys

import pathspec

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Defense in depth: always excluded, gitignore or not. Real credentials / project
# config that must never ship in the downloadable zip (and are also excluded from the
# published site via hugo.toml's module-mount excludeFiles).
HARD_EXCLUDE_NAMES = {
    "cloud_secrets.h",
    "google-services.json",
    "firebase_options.dart",
    ".firebaserc",
    ".git",
}


def scope_pattern(reldir, pattern):
    negate = pattern.startswith("!")
    body = pattern[1:] if negate else pattern
    is_dir_only = body.endswith("/")
    body = body.rstrip("/")

    if reldir:
        if body.startswith("/"):
            scoped = f"/{reldir}{body}"
        elif "/" in body:
            scoped = f"/{reldir}/{body}"
        else:
            scoped = f"/{reldir}/**/{body}"
    else:
        scoped = body if body.startswith("/") else f"/**/{body}" if "/" not in body else f"/{body}"

    if is_dir_only:
        scoped = f"{scoped}/**"

    return ("!" + scoped) if negate else scoped


def build_spec(base_dir):
    patterns = []
    for dirpath, _, filenames in os.walk(base_dir):
        if ".gitignore" not in filenames:
            continue
        reldir = os.path.relpath(dirpath, base_dir).replace("\\", "/")
        reldir = "" if reldir == "." else reldir
        with open(os.path.join(dirpath, ".gitignore"), "r", encoding="utf-8", errors="ignore") as f:
            for line in f:
                line = line.rstrip("\n")
                stripped = line.strip()
                if not stripped or stripped.startswith("#"):
                    continue
                patterns.append(scope_pattern(reldir, stripped))
    return pathspec.PathSpec.from_lines("gitwildmatch", patterns)


def main():
    if len(sys.argv) != 2:
        print("Usage: python scripts/generate_zip_manifest.py <folder-name-under-static/files>")
        sys.exit(1)

    name = sys.argv[1]
    base_dir = os.path.join(REPO_ROOT, "static", "files", name)
    if not os.path.isdir(base_dir):
        print(f"Not a directory: {base_dir}")
        sys.exit(1)

    spec = build_spec(base_dir)

    kept = []
    skipped = []
    for dirpath, dirnames, filenames in os.walk(base_dir):
        reldir = os.path.relpath(dirpath, base_dir).replace("\\", "/")
        reldir = "" if reldir == "." else reldir
        for fname in filenames:
            if fname == ".gitignore":
                continue
            relpath = f"{reldir}/{fname}" if reldir else fname
            if fname in HARD_EXCLUDE_NAMES or spec.match_file(relpath):
                skipped.append(relpath)
            else:
                kept.append(relpath)

    kept.sort()
    skipped.sort()

    out_dir = os.path.join(REPO_ROOT, "data", "zipmanifests")
    os.makedirs(out_dir, exist_ok=True)
    out_path = os.path.join(out_dir, f"{name}.json")
    with open(out_path, "w", encoding="utf-8", newline="\n") as f:
        json.dump(kept, f, ensure_ascii=False, indent=2)
        f.write("\n")

    print(f"Wrote {len(kept)} files to {out_path}")
    print(f"Excluded {len(skipped)} files:")
    for p in skipped:
        print(f"  - {p}")


if __name__ == "__main__":
    main()

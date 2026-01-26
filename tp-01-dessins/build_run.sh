#!/usr/bin/env bash
set -euo pipefail

# ---- Réglages ----
SRC="squelette.c"          # fichier C
BIN="./ppm"           # binaire compilé
OUT="image.ppm"       # image générée

# ---- Compilation ----
gcc -Wall -Wextra -O2 "$SRC" -o "$BIN" -lm

# ---- Génération du PPM ----
"$BIN" > "$OUT"

echo "✅ Généré: $OUT"

#!/usr/bin/env bash

set -e

TMPDIR="build-asan build-valgrind"
trap "rm -rf $TMPDIR" EXIT


echo "[build] Running memory-safety checks..."

# Install deps (skip apt-get because it's slow)
# Expect valgrind and gcc installed already

# -------------------------
# 1. Build ASan + UBSan
# -------------------------
mkdir -p build-asan
gcc \
  -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 \
  -std=c11 \
  -g \
  -fsanitize=address,undefined \
  -fno-omit-frame-pointer \
  src/*.c -I include -lyaml -lm \
  -o build-asan/dbeetle

echo "[run] Running ASan + UBSan..."
./build-asan/dbeetle

# -------------------------
# 2. Build valgrind binary
# -------------------------
mkdir -p build-valgrind
gcc \
  -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 \
  -std=c11 \
  -g \
  src/*.c -I include -lyaml -lm \
  -o build-valgrind/dbeetle

echo "[run] Running valgrind..."
valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --errors-for-leak-kinds=all \
  --error-exitcode=1 \
  ./build-valgrind/dbeetle

echo "[ok] Memory checks passed."


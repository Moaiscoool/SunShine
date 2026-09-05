#!/usr/bin/env bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "================================"
echo "       Linux Test Build"
echo "================================"

cmake --preset linux-debug
cmake --build --preset linux-debug

EXECUTABLE="build/linux/debug/bin/MyGame"

# Get the actual executable name from CMake
EXECUTABLE="$(find build/linux/debug/bin -maxdepth 1 -type f -executable | head -n 1)"

if [[ -z "$EXECUTABLE" ]]; then
    echo "ERROR: Linux executable was not found."
    exit 1
fi

echo
echo "Build successful!"
echo "Running:"
echo "  $EXECUTABLE"
echo

"$EXECUTABLE"

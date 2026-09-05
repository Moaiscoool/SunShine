#!/usr/bin/env bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "================================"
echo "      Windows Test Build"
echo "================================"

cmake --preset windows-debug
cmake --build --preset windows-debug

EXECUTABLE="$(find build/windows/debug/bin -maxdepth 1 -type f -iname '*.exe' | head -n 1)"

if [[ -z "$EXECUTABLE" ]]; then
    echo "ERROR: Windows executable was not found."
    exit 1
fi

echo
echo "Windows build successful!"
echo
echo "Executable:"
echo "  $EXECUTABLE"
echo

# Run with Wine if available
if command -v wine >/dev/null 2>&1; then
    echo "Wine detected."
    echo "Running Windows executable..."
    echo

    wine "$EXECUTABLE"
else
    echo "Wine is not installed."
    echo
    echo "The Windows executable was successfully compiled,"
    echo "but it cannot be run directly on Linux."
    echo
    echo "Executable:"
    echo "  $EXECUTABLE"
fi

#!/usr/bin/env bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "=================================="
echo " Building MyGame - Windows"
echo "=================================="

cmake --preset windows-debug
cmake --build --preset windows-debug

echo
echo "Build complete!"
echo
echo "Executable:"
echo "  $PROJECT_ROOT/build/windows/debug/bin/MyGame.exe"
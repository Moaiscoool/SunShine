#!/usr/bin/env bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "================================"
echo " Building MyGame - Linux"
echo "================================"

cmake --preset linux-debug
cmake --build --preset linux-debug

echo
echo "Build complete!"
echo
echo "Executable:"
echo "  $PROJECT_ROOT/build/linux/debug/bin/MyGame"
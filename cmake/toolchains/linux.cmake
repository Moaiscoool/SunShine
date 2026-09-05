#!/usr/bin/env bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "Cleaning build directories..."

rm -rf build/linux
rm -rf build/windows

echo "Clean complete!"
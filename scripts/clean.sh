#!/usr/bin/env bash

set -e

cd "$(dirname "$0")/.."

echo "Cleaning build directories..."

rm -rf build/linux
rm -rf build/windows

echo "Clean complete!"
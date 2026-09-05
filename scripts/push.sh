#!/usr/bin/env bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "================================"
echo "        MyGame Git Commit"
echo "================================"
echo

# Make sure this is a Git repository
if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "ERROR: This is not a Git repository."
    exit 1
fi

# Show changes
echo "Changes:"
echo "--------------------------------"
git status --short
echo "--------------------------------"
echo

# Ask for commit message
read -r -p "Commit message: " COMMIT_MESSAGE

# Don't allow an empty message
if [[ -z "$COMMIT_MESSAGE" ]]; then
    echo
    echo "ERROR: Commit message cannot be empty."
    exit 1
fi

echo
echo "Staging files..."
git add .

echo "Creating commit..."
git commit -m "$COMMIT_MESSAGE"

echo
echo "Pushing to GitHub..."
git push

echo
echo "================================"
echo "       Push successful!"
echo "================================"

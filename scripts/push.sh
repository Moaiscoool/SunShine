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

# CHECK: Do we actually have local modifications?
if [[ -n $(git status --porcelain) ]]; then
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
else
    echo "Working tree clean. No new changes to commit."
    echo "Proceeding directly to push options..."
fi

# New Feature: Select Push Destination
echo
echo "Where would you like to push?"
echo "1) GitHub (origin)"
echo "2) Local Git Server (local)"
echo "3) Both"
echo "4) Skip pushing"
read -r -p "Select an option [1-4]: " PUSH_CHOICE

# Get the current branch name automatically
CURRENT_BRANCH=$(git branch --show-current)

echo
case "$PUSH_CHOICE" in
    1)
        echo "Pushing to GitHub..."
        git push origin "$CURRENT_BRANCH"
        ;;
    2)
        echo "Pushing to Local Git Server..."
        git push local "$CURRENT_BRANCH"
        ;;
    3)
        echo "Pushing to GitHub..."
        git push origin "$CURRENT_BRANCH"
        echo "Pushing to Local Git Server..."
        git push local "$CURRENT_BRANCH"
        ;;
    4)
        echo "Skipping push step."
        exit 0
        ;;
    *)
        echo "Invalid selection. Skipping push."
        exit 1
        ;;
esac

echo
echo "================================"
echo "       Push successful!"
echo "================================"

#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "================================"
echo "        MyGame Git Commit"
echo "================================"
echo

if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "ERROR: This is not a Git repository."
    exit 1
fi

CURRENT_BRANCH=$(git branch --show-current)
if [[ -z "$CURRENT_BRANCH" ]]; then
    echo "ERROR: Detached HEAD. Check out a branch first."
    exit 1
fi

echo "Changes:"
echo "--------------------------------"
git status --short
echo "--------------------------------"
echo

if [[ -n $(git status --porcelain) ]]; then
    read -r -p "Commit message: " COMMIT_MESSAGE
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

# ---- Discover remotes dynamically ----
mapfile -t REMOTES < <(git remote)
if [[ ${#REMOTES[@]} -eq 0 ]]; then
    echo
    echo "No remotes configured. Add one with: git remote add <name> <url>"
    exit 0
fi

# Optional per-remote branch restriction, set with:
#   git config remote.<name>.allowedbranches "main release"
allowed_branches() {
    git config --get "remote.$1.allowedbranches" || true
}

branch_allowed() {
    local allowed b
    allowed=$(allowed_branches "$1")
    [[ -z "$allowed" ]] && return 0
    for b in $allowed; do
        [[ "$b" == "$CURRENT_BRANCH" ]] && return 0
    done
    return 1
}

# ---- Build the menu ----
SELECTED=()
while true; do
    echo
    echo "Where would you like to push? (branch: $CURRENT_BRANCH)"
    for i in "${!REMOTES[@]}"; do
        r="${REMOTES[$i]}"
        url=$(git remote get-url --push "$r")
        note=""
        allowed=$(allowed_branches "$r")
        [[ -n "$allowed" ]] && note="  [only: $allowed]"
        printf "  %d) %-10s %s%s\n" $((i + 1)) "$r" "$url" "$note"
    done
    echo "  a) All"
    echo "  s) Skip pushing"
    read -r -p "Select (e.g. 2 or 1 3): " CHOICE
    CHOICE="${CHOICE//,/ }"

    SELECTED=()
    if [[ "$CHOICE" == "s" ]]; then
        echo "Skipping push step."
        exit 0
    elif [[ "$CHOICE" == "a" ]]; then
        SELECTED=("${REMOTES[@]}")
        break
    else
        valid=1
        for n in $CHOICE; do
            if [[ "$n" =~ ^[0-9]+$ ]] && (( n >= 1 && n <= ${#REMOTES[@]} )); then
                SELECTED+=("${REMOTES[$((n - 1))]}")
            else
                valid=0
            fi
        done
        if [[ $valid -eq 1 && ${#SELECTED[@]} -gt 0 ]]; then
            break
        fi
        echo "Invalid selection."
    fi
done

# ---- Push to each selected remote independently ----
echo
RESULTS=()
FAILED=0
for remote in "${SELECTED[@]}"; do
    if ! branch_allowed "$remote"; then
        RESULTS+=("SKIPPED  $remote (branch '$CURRENT_BRANCH' not allowed)")
        continue
    fi
    echo "Pushing to $remote..."
    if git push -u "$remote" "$CURRENT_BRANCH"; then
        RESULTS+=("OK       $remote")
    else
        RESULTS+=("FAILED   $remote")
        FAILED=1
    fi
done

echo
echo "================================"
printf '%s\n' "${RESULTS[@]}"
echo "================================"
exit $FAILED
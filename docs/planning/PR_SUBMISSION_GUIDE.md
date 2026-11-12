# StudentRMS — Historical Pull Request Submission Guide

> **Archive note (12 November 2026):** This document records the original Sprint 1 contribution workflow prepared for Rohan M. It is retained as project history, not as the current submission procedure. Do not copy its old branch names, dates, Windows paths, story-point counts, or PR description as evidence of current work.

## Current repository workflow

1. Start from an up-to-date local clone of `main`.
2. Create a focused feature or documentation branch.
3. Make one logically scoped change and run the relevant tests.
4. Inspect `git status` and `git diff --check`.
5. Commit with a descriptive message and push the branch to the repository.
6. Open a pull request against `main`, describe the change, list tests actually run, and link related issues.
7. Wait for required CI checks and review. Merge only after repository-owner/team approval.

## Historical context

The original guide described Rohan M's Sprint 1 search/list contribution and a pull request for the initial working product. Its machine-specific PowerShell paths and copied PR template are intentionally not reproduced as current instructions.

## Current verification commands

Linux/macOS:

```bash
make clean
make all
make test
git diff --check
```

Windows/MinGW:

```bat
cmd /c build.bat
```

Never state that a test, review, or approval passed unless its output or GitHub status is available.

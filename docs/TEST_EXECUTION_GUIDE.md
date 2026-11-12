# StudentRMS — Test Execution Guide

## Prerequisites

- Linux/macOS: GCC, GNU Make, and gcov.
- Windows: MinGW-w64 GCC on PATH. Use the supplied \`build.bat\` as the supported native Windows build-and-test entry point.
- Coverage collection is configured for GCC/gcov.

## Standard Linux/macOS test run

From the repository root:

\`\`\`bash
make clean
make all
make test
\`\`\`

The test target runs \`test_suite\`, \`test_search_list\`, \`test_sprint2\`, \`test_part3_unit\`, and \`test_perf\`.

## Standard Windows/MinGW build and test

Open a MinGW-w64 terminal or PowerShell with MinGW \`bin\` on PATH:

\`\`\`bat
cmd /c build.bat
\`\`\`

The script compiles the interactive application and all five test executables, then runs every test executable. If a test fails, the script exits with a non-zero status.

The Makefile uses Unix shell utilities such as \`rm\`; therefore \`mingw32-make clean\` is not the supported clean command in a native Windows shell. Use \`build.bat\` for the documented Windows workflow.

## Coverage run (GCC/gcov)

\`\`\`bash
make clean
make coverage
\`\`\`

The coverage target rebuilds with \`--coverage -O0 -g\`, runs the test binaries, and invokes gcov. Preserve generated \`.gcov\` files and record compiler/tool versions. Do not compare measurements across different compiler versions or flags without documenting the difference.

## System validation checklist

Run the application in an isolated temporary working directory. Do not use or overwrite team working data.

1. Confirm first launch creates the sample data file.
2. Login with valid credentials; separately verify invalid credentials are denied.
3. Add a valid record and confirm percentage/CGPA calculation.
4. Attempt duplicate roll, invalid marks, and invalid semester; confirm rejection.
5. Update a record and verify recalculated academic fields.
6. Cancel deletion with \`N\` and verify the record remains.
7. Confirm deletion with \`Y\` and verify the record is removed.
8. Exit and restart; verify the updated record remains and the deleted record is absent.
9. Export reports and inspect both the complete student list and descending rank list.
10. Inspect \`login.log\` for timestamped authentication events.

Record tester, date/time, environment, outcome, and evidence filename in \`SYSTEM_VALIDATION_REPORT.md\`. A menu option or an automated unit test alone is not evidence of a completed interactive walkthrough.

## Evidence to capture

- Console output for all five automated test executables.
- GitHub Actions run and successful job steps.
- gcov output and generated coverage files.
- Screenshots/video of login, add, update, delete-cancel, delete-confirm, restart, and report export.
- Compiler, GNU Make, OS, and version information.

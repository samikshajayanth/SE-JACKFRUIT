# StudentRMS — Part 3 Test Execution Guide

## Prerequisites

Linux: GCC, GNU Make, and gcov (`gcc`, `make`, `gcov`). Windows: MinGW-w64 GCC and GNU Make (or use `build.bat` for the standard build). Coverage collection with gcov is configured for GCC-compatible Linux toolchains.

## Standard Linux test run

From the repository root:

```bash
make clean
make all
./test_suite
./test_search_list
./test_sprint2
./test_part3_unit
./test_perf
```

## Standard Windows/MinGW build

Open a MinGW-w64 terminal or PowerShell with MinGW `bin` on PATH, then run:

```bat
cmd /c build.bat
test_search_list.exe
test_part3_unit.exe
```

The supported Windows build entry point compiles the application and all test targets, then executes the integrated, Sprint 2, and performance suites. The dedicated search/list and Part 3 robustness executables are run separately in the Windows CI job.

## Coverage run (GCC/gcov)

```bash
make clean
make coverage
```

The coverage target rebuilds binaries with `--coverage -O0 -g`, runs the test binaries, and invokes `gcov -b -c` for each production source. Preserve generated `.gcov` files and record the toolchain version. Do not compare coverage numbers across different build flags or compiler versions without documenting the difference.

## System validation checklist (manual)

1. Run the application from a clean temporary working directory.
2. Confirm first launch creates `students.dat` with initial sample records.
3. Login with valid credentials; repeat with invalid credentials in a fresh directory and confirm access is denied after configured attempts.
4. Add a valid record and confirm success plus derived percentage/CGPA.
5. Attempt duplicate roll, invalid marks, and invalid semester; confirm each is rejected.
6. Update one record and confirm displayed derived fields change.
7. Delete a record, choose `N`, and verify it remains; repeat and choose `Y`, then verify it is removed.
8. Exit and restart. Confirm the modified record set is restored from `students.dat`.
9. Export reports and inspect both the all-records and rank-list sections in `reports.txt`.
10. Inspect `login.log` for timestamped authentication events.

Record each outcome, date/time, tester, environment, and evidence filename in `SYSTEM_VALIDATION_REPORT.md`. Never mark a step passed based only on the presence of a menu option.

## Evidence to capture

- Terminal output for each automated test executable.
- Full GitHub Actions run page and successful job steps.
- gcov output and generated `.gcov` files.
- Screenshots/video of add, update, delete-cancel, delete-confirm, restart, and report export flows.
- Compiler version (`gcc --version`), GNU Make version, and OS/version.

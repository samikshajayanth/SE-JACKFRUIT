# StudentRMS — Part 3 Test Execution Guide

## Prerequisites

Linux: GCC, GNU Make, and gcov (`gcc`, `make`, `gcov`). Windows: MinGW-w64 GCC and GNU Make (or use `build.bat` for the standard build). Coverage collection with gcov is configured for GCC-compatible Linux toolchains.

## Standard test run

From the repository root:

```bash
make clean
make all
./test_suite
./test_search_list
./test_sprint2
./test_perf
```

Each executable returns a non-zero exit code if its assertions fail. Save complete console output to `docs/evidence/` when performing the scheduled test window.

## Coverage run (GCC/gcov)

```bash
make clean
make coverage
```

The coverage target rebuilds binaries with `--coverage -O0 -g`, runs the test binaries, and invokes `gcov -b -c` for each production source. Preserve the generated `.gcov` text files and record the toolchain version. Do not compare coverage numbers across different build flags or compiler versions without documenting the difference.

For a clean summary, run:

```bash
gcov -b -c src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c
```

`Lines executed` is line coverage. `Branches executed`/ `Taken at least once` is branch information. gcov's branch coverage percentage is not identical to line coverage. Review the generated file-level results and calculate aggregate percentages using executable-line and branch counts, not an unweighted average of file percentages.

## System validation checklist (manual)

1. Run `studentrms_app` from a clean temporary working directory.
2. Confirm first launch creates `students.dat` with initial sample records.
3. Login with valid credentials; then repeat with invalid credentials in a fresh directory and confirm access is denied after the configured attempts.
4. Add a valid record and confirm the success message plus derived percentage/CGPA.
5. Attempt duplicate roll, invalid marks, and invalid semester; confirm each is rejected.
6. Update one record and confirm the displayed derived fields change.
7. Delete a record, choose `N`, and verify the record remains; repeat and choose `Y`, then verify it is removed.
8. Exit and restart. Confirm the modified record set is restored from `students.dat`.
9. Export reports and inspect both the all-records and academic-rank-list sections in `reports.txt`.
10. Inspect `login.log` for timestamped authentication events.

Record each outcome, date/time, tester, environment, and evidence filename in `SYSTEM_VALIDATION_REPORT.md`. Never mark a step passed based only on the presence of a menu option.

## Evidence to capture

- Terminal output for each automated test executable.
- Full GitHub Actions run page and the successful job steps.
- gcov output and generated `.gcov` files.
- Screenshots/video of add, update, delete-cancel, delete-confirm, restart, and report export flows.
- Compiler version (`gcc --version`), `make --version`, and OS/version.

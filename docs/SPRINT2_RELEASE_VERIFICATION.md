# Sprint 2 Release Verification

Issue: [#32](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/32)
Verified source commit: `e6b274e12385470335e7a3d7ea4a5f18350b56cc` (`origin/main`)
Verification branch: `feature/rohan-sprint2-release-verification`

## Environment

- Native Windows PowerShell environment.
- MinGW-w64 GCC 15.2.0 (MSYS2, `x86_64-w64-mingw32`).
- GNU Make 4.4.1.
- Runtime files were created in the isolated working directory `evidence/interactive/`; no pre-existing `students.dat` or team working data was used. The first launch seeded the application's built-in sample records.

## Automated verification

| Command | Result | Observed outcome |
|---|---|---|
| `cmd /c build.bat` | PASS | All five Windows targets compiled; integrated suite 28/28, Sprint 2 suite 18/18, and final performance benchmark 0.0550 seconds. |
| `.\test_search_list.exe` | PASS | Search/list suite 22/22. |
| `mingw32-make` | PASS | Targets compiled successfully after the native `make clean` limitation below. |
| `git diff --check` | PASS | No whitespace errors. |

The documented `mingw32-make clean` command was also attempted. It is not portable to this native MinGW shell because the Makefile invokes Unix `rm`; it failed before compilation with `CreateProcess ... rm ... failed`. This does not affect the supported Windows entry point, `build.bat`, which completed successfully. No code change was made for this unrelated build-script portability limitation.

## Interactive acceptance matrix

The application was launched from an isolated directory with the supported credentials shown by the existing application (`admin` / `admin123`). The update used a synthetic name and marks; the application also loaded its built-in sample records.

| ID | Check | Result | Evidence |
|---|---|---|---|
| INT-UPD-01 | Update an existing record with valid fields | PASS; replacement values displayed and academic values recalculated to 100.00% / 10.00 CGPA | `evidence/interactive/first_run.log` |
| INT-UPD-02 | Invalid mark during update | PASS; mark above 100 was rejected and no update was saved | `evidence/interactive/negative_updates.log` |
| INT-UPD-03 | Duplicate roll number during update | PASS; update rejected and original record remained unchanged | `evidence/interactive/negative_updates.log` |
| INT-DEL-01 | Cancel deletion | PASS; `[CANCELLED] Record was not changed.` was displayed | `evidence/interactive/first_run.log` |
| INT-DEL-02 | Confirm deletion | PASS; deletion succeeded and record count changed from 6 to 5 | `evidence/interactive/first_run.log` |
| INT-DEL-03 | Delete unknown record | PASS; clear not-found message displayed | `evidence/interactive/first_run.log` |
| INT-PERSIST-01 | Restart after update and deletion | PASS; restart loaded 5 records, updated record was present, and deleted record was absent | `evidence/interactive/second_run.log` |
| INT-REPORT-01 | Export report | PASS; `reports.txt` was created and readable | `evidence/interactive/reports.txt` |
| INT-REPORT-02 | Report contents and ranking | PASS; listing and rank sections were present and rank CGPAs were descending | `evidence/interactive/reports.txt` |

## Evidence and limitations

The raw interactive logs and runtime files are kept locally under `evidence/interactive/` and are ignored or intentionally uncommitted because the seeded application dataset contains team-member identifiers. The report records the observed outcomes without committing those records.

The native Windows/MinGW build was executed successfully. A graphical recording was not produced automatically; the reproducible demonstration sequence is in [SPRINT2_DEMO_CHECKLIST.md](SPRINT2_DEMO_CHECKLIST.md). Team review, release-freeze sign-off, and video upload remain outside this verification run.

# StudentRMS — System Validation Report (Part 3)

**Execution date:** 31 October 2026  
**Branch / PR:** `part3/testing-docs`, [PR #34](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/34)  
**Workflow:** [Run 41163252707 — StudentRMS Part 3 Verification](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/41163252707)  
**Environment:** Ubuntu 24.04.5 LTS, GCC 13.2.0

## 1. Objective

Validate the integrated StudentRMS application against the Sprint 1 and Sprint 2 functional requirements, including authentication, record lifecycle, persistence across restart, and text report export.

## 2. Automated system and integration evidence

Both jobs in the Part 3 workflow completed successfully.

The Build & Verify job passed:
1. Compilation of all application and test targets.
2. First-launch smoke test in a clean temporary directory.
3. Verification that `students.dat` was created.
4. Second launch from the same working directory.
5. Verification that six student records were restored from `students.dat`.
6. Existing integrated, search/list, Sprint 2, and Part 3 robustness test executables.
7. The 1,000-record performance benchmark (0.0389 seconds; threshold 2.0000 seconds).

The Sprint 2 regression executable passed tests for update/recalculation, duplicate updates, invalid updates, unknown records, deletion/count consistency, binary save/load, corrupt-storage rejection, and report output content. This is automated integration evidence; it is not the same as an interactive acceptance demonstration.

## 3. Validation results

| ID | Validation scenario | Status | Evidence / remaining action |
|---|---|---|---|
| SV-01 | First launch in clean directory creates and persists seed data | **CI PASS** | Build & Verify smoke-test step |
| SV-02 | Second launch restores six persisted records | **CI PASS** | Build & Verify smoke-test step |
| SV-03 | Valid and invalid administrator login in interactive session | **UNIT PASS / MANUAL PENDING** | Unit suite passed; capture interactive console evidence |
| SV-04 | Add a valid record and reject duplicate/invalid values | **UNIT PASS / MANUAL PENDING** | Automated validations passed; capture UI interaction |
| SV-05 | Update an existing record and recalculate academics | **REGRESSION PASS / MANUAL PENDING** | Sprint 2 suite passed; capture before/after UI output |
| SV-06 | Cancel delete by choosing `N` | **MANUAL PENDING** | Confirm record remains visible after cancellation |
| SV-07 | Confirm delete by choosing `Y` | **REGRESSION PASS / MANUAL PENDING** | Core deletion passed; capture interactive confirmation |
| SV-08 | Restart after update/delete and restore mutated state | **PARTIAL / MANUAL PENDING** | CI checks seeded-data restart; manually verify persisted mutations |
| SV-09 | Export and inspect student/rank reports | **UNIT PASS / MANUAL PENDING** | Export API and content tests passed; capture actual `reports.txt` |
| SV-10 | View authentication audit log | **UNIT PASS / MANUAL PENDING** | Login API logs events; capture `login.log` through menu |
| SV-11 | Windows/MinGW build and run | **NOT VERIFIED** | Run `build.bat` on Windows and capture terminal output |

## 4. Conclusion

Automated build, unit/regression, seed-data restart smoke, and performance checks passed on the PR candidate. The project is **not yet fully system-validated** until the manual console scenarios (especially delete cancellation/confirmation and persistence after mutations) and Windows/MinGW build are demonstrated and recorded. Do not change the manual-pending rows to PASS without attaching those observations.

# StudentRMS — Unit Test Report (Part 3)

**Execution date:** 31 October 2026  
**Branch / PR:** `part3/testing-docs`, [PR #34](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/34)  
**Workflow:** [Run 41163252707 — StudentRMS Part 3 Verification](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/41163252707)  
**Environment:** Ubuntu 24.04.5 LTS, GCC 13.2.0, GNU Make 4.3

## 1. Scope

The unit test execution covers authentication/session state, record creation and validation, academic computation, search and sorting, update/delete operations, binary storage, report generation, and robustness/error inputs. The complete case catalogue is in `TEST_CASE_DOCUMENT_PART3.md`.

## 2. Executed test results

| Test executable | Assertions passed | Assertions failed | Result |
|---|---:|---:|---|
| `test_suite` | 28 | 0 | PASS |
| `test_search_list` | 22 | 0 | PASS |
| `test_sprint2` | 18 | 0 | PASS |
| `test_part3_unit` | 34 | 0 | PASS |
| **Total** | **102** | **0** | **PASS** |

All four functional/robustness test executables completed with exit code 0. The performance benchmark is reported separately: it completed the 1,000-record operations in **0.0294 seconds**, within the 2.0000-second NFR-001 limit (1.47% of the budget).

## 3. Key areas verified

- Authentication: valid/invalid credentials, state transitions, logout, and null credential input.
- Record management: valid insertion, duplicate roll rejection, invalid marks, invalid semester, and null argument handling.
- Academic engine: percentage calculation, CGPA cap, and null marks handling.
- Search and sort: case-insensitive roll/name searches, not-found handling, invalid parameters, valid sort, and invalid sort order.
- Sprint 2 regression: update/recalculation, duplicate update, invalid update, unknown update, deletion/count integrity, binary save/load, corrupt storage rejection, and report content.
- Report API robustness: null path, negative count, and inaccessible output location.

## 4. CI result

Both jobs in the Part 3 workflow completed successfully:
- **Build & Verify (Linux GCC):** compile-all, first-launch/restart smoke test, all four test executables, and the performance benchmark passed.
- **GCC Line and Branch Coverage:** instrumented compilation, all test executables, gcov report generation, and artifact upload passed.

The full raw console output is available from the workflow run linked above. The gcov evidence is attached as a workflow artifact and summarized in the code/branch coverage reports.

## 5. Limitations

The automated unit suites do not replace interactive system validation. Delete cancellation/confirmation, update through the console UI, mutation persistence across an application restart, manual report-file inspection, audit-log viewing, and Windows/MinGW execution still require evidence from the system-validation checklist.

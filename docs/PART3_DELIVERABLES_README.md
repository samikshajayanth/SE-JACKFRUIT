# Part 3 Deliverables — StudentRMS

This folder contains the updated test-case document, execution instructions, traceability matrix, and four reports requested in Software Engineering Mini-Project Deliverables Part 3.

| Deliverable | File | Status |
|---|---|---|
| Updated Test Case Document | `TEST_CASE_DOCUMENT_PART3.md` | Updated for Sprint 1 + Sprint 2; includes 34 new robustness assertions |
| Test Case Traceability | `PART3_TEST_CASE_TRACEABILITY.csv` | Updated with requirements, test levels, automation, and execution status |
| Unit Test Report | `UNIT_TEST_REPORT.md` | **PASS:** 102/102 assertions across four test executables |
| System Validation Report | `SYSTEM_VALIDATION_REPORT.md` | CI build/smoke/regression checks passed; interactive console and Windows checks remain pending |
| Code Coverage Report | `CODE_COVERAGE_REPORT.md` | **77.67% line coverage** (240/309 executable lines) |
| Branch Coverage Report | `BRANCH_COVERAGE_REPORT.md` | **62.70% branch-outcome coverage** (200/319 branch outcomes taken at least once) |
| Test Execution Guide | `TEST_EXECUTION_GUIDE.md` | Standard, gcov, manual system-validation, and evidence-capture steps |

## Part 3 CI evidence

Workflow run [41163252707 — StudentRMS Part 3 Verification](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/41163252707) passed the Linux build, application restart smoke test, all four unit/regression executables, performance benchmark, instrumented coverage run, and gcov artifact upload.

The 1,000-record benchmark completed in 0.0389 seconds against the 2.0000-second limit. The gcov artifact from this run contains annotated source coverage files and instrumented build data.

## Remaining work for the assignment window (2–6 November 2026)

Complete the interactive console checks listed in `SYSTEM_VALIDATION_REPORT.md`: especially delete cancellation (`N`), delete confirmation (`Y`), update and mutation persistence across restart, report-file inspection, audit-log viewing, and the Windows/MinGW build. Capture terminal screenshots or video, and update the manual-pending rows only after observing the results.

Optional Sprint 3 should be recorded only if actual development spillover remains; testing and documentation alone should not be mislabeled as Sprint 3 development.

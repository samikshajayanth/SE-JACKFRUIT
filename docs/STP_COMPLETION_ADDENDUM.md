# Software Test Plan — Completion Addendum

This addendum supplies operational detail for the test-plan sections that were only headings or brief placeholders in the submitted final PDF. It does not claim that unexecuted manual tests have passed.

## 3. Features to be Tested

| Feature | Related requirements | Planned verification |
|---|---|---|
| Administrator authentication and session gating | FR-001, SEC-002, SEC-005 | Valid/invalid login, unauthenticated access denial, logout, audit event |
| Add record and field validation | FR-002, FR-003, FR-012, SEC-003 | Valid insert, duplicate roll, empty mandatory fields, mark and semester boundaries |
| Search and view | FR-004 | Exact roll search, case-insensitive name search, not-found result |
| Update and delete | FR-005, FR-006 | Valid update, invalid update, duplicate update, cancel delete, confirm delete |
| Listing and sorting | FR-007 | Roll, name, and CGPA order; empty and invalid input |
| Percentage and CGPA | FR-008 | Known-value arithmetic, boundary values, null/invalid input |
| Rank list and export | FR-009, FR-011 | Descending CGPA order, report sections, output errors |
| Persistence and recovery | FR-010, NFR-002, SEC-004 | Save/load round trip, restart, corrupt store, write failure |
| Performance and portability | NFR-001, NFR-006 | Up to 1,000 records within 2 seconds; Linux GCC and Windows MinGW builds |

## 4. Features Not to be Tested

The following are outside the agreed product scope: university ERP integration, web/mobile GUI, multi-user network access, relational database behavior, and operating-system/compiler internals. These exclusions do not waive testing of the local console application or its file handling.

## 6. Test Environment

| Item | Environment / control |
|---|---|
| Hardware | Reference desktop/laptop; record CPU and RAM with each performance run |
| Operating systems | Ubuntu/Linux with GCC; Windows with MinGW-w64 |
| Compiler | Record exact `gcc --version` output |
| Build tools | GNU Make on Linux; supplied `build.bat` on native Windows |
| Test data | Synthetic student records, boundary values, duplicate identifiers, and controlled corrupt-file fixtures |
| Storage | Isolated temporary working directory; never use or overwrite team working data |
| Evidence | Console output, CI run URL, screenshots/log filenames, test date, tester |

## 7. Test Schedule

The original planned milestones were 28 September–2 October 2026. The following is the planned sequence represented by the completed evidence set; it is not a claim that every item was executed on those original dates.

| Activity | Planned sequence | Evidence |
|---|---|---|
| Test design and requirements mapping | Before feature integration | Test case catalogue and RTM |
| Environment/build verification | Before test execution | GCC/MinGW versions and build logs |
| Unit and integration execution | After module integration | Test executables and CI results |
| Security and reliability checks | After authentication/storage integration | Security test results and fault-handling evidence |
| Regression and traceability review | Before release candidate | Updated traceability CSV |
| Interactive acceptance and portability review | Release verification | Sprint 2 release verification report |
| Final review | Before submission | Team approval and release sign-off |

## 9. Roles and Responsibilities

| Role | Responsibility |
|---|---|
| QA/Test Lead | Maintain test plan, coordinate execution, review evidence and RTM completeness |
| Test Engineer(s) | Prepare test data, execute assigned cases, record actual results and defects |
| Developer/Module Owner | Support test setup, diagnose failures, implement fixes, and provide unit-level evidence |
| Product Owner / Team | Review acceptance outcomes, confirm scope, and approve release readiness |

The team should record the actual person against each role in the execution record; role labels alone are not evidence of individual execution.

## 10. Risks and Mitigation

| Risk | Impact | Mitigation |
|---|---|---|
| Unstable build | Tests cannot start or results are unreliable | Run clean build and smoke test before the full suite |
| Contaminated/shared data | Existing records may be overwritten | Use isolated temporary directories and synthetic data |
| File corruption during tests | Data loss or misleading persistence results | Keep baseline copies and use controlled corruption fixtures |
| Late defect discovery | Insufficient time for regression | Execute high-priority authentication, CRUD, and persistence cases early |
| Platform differences | Build/runtime behavior differs between Linux and Windows | Run both CI jobs and the native Windows script |
| Incomplete evidence | Passing behavior cannot be independently reviewed | Record exact command, environment, result, and evidence location |
| Credential exposure | Unauthorized access or false security claims | Use demo-only credentials, do not commit secrets, and track SEC-001 as open until remediated |

## 13. Test Case Management and Traceability

Each test case has a stable ID, linked requirement, test level, setup/input, expected result, and execution status. The authoritative case-to-requirement mapping is `PART3_TEST_CASE_TRACEABILITY.csv`. Automated execution evidence is linked to the named test executable and CI run. Interactive acceptance evidence is linked to the corresponding row in `SPRINT2_RELEASE_VERIFICATION.md`.

A case may be marked PASS only when its execution result and evidence are recorded. A requirement with no executed test or with a known implementation gap must remain open/partial; do not infer compliance from a related unit test.

## 15. Approvals

| Approval role | Name | Status |
|---|---|---|
| QA/Test Lead | To be completed by team | Pending |
| Developer Lead | To be completed by team | Pending |
| Product Owner / Team Representative | To be completed by team | Pending |
| Course Coordinator | University review | Pending |

Signatures and dates must be completed by the actual approvers. They are intentionally not fabricated in this addendum.

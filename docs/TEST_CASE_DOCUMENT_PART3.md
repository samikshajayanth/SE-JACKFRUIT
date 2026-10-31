# StudentRMS — Updated Test Case Document (Part 3)

**Project:** Student Record Management System (StudentRMS)  
**Course:** Software Engineering (UE24CS341A)  
**Team 4:** Samiksha Jayanth (M1), Rohan M (M2), Saksham Bajpayi (M3), Riddhi Mundada (M4)  
**Baseline:** `main` after Sprint 2 merge; Part 3 test update prepared 31 October 2026.

## 1. Purpose and scope

This document updates the original Sprint 1 cases and adds Sprint 2 regression coverage for record update/delete, versioned binary persistence, restart restoration, and report export. The test scope includes module-level functions, integration between modules, startup/restart behavior, and performance. Console confirmation prompts are system-level checks and are marked manual unless automated terminal interaction is recorded.

## 2. Test environment

- Language/build: C11, GCC, GNU Make.
- Build flags used by the repository: `-Wall -Wextra -std=c11 -Iinclude`.
- Automated CI target: Ubuntu latest, GCC, Make.
- Runtime files are relative to the current working directory: `students.dat`, `reports.txt`, and `login.log`.
- Performance target: at most 2.0 seconds for the 1,000-record benchmark. Timing is hardware-dependent and should be reported with the workflow run or local environment.

## 3. Updated test cases

| ID | Module / Requirement | Test scenario and input | Expected result | Test level |
|---|---|---|---|---|
| TC-AUTH-01 | Authentication / FR-001 | Login as `admin` with valid password | Login succeeds; authenticated state becomes true | Unit + system |
| TC-AUTH-02 | Authentication / FR-001 | Use an incorrect password | Credentials rejected; state remains unauthenticated | Unit + system |
| TC-AUTH-03 | Authentication / SEC-005 | Logout after successful login | Session state resets; logout is audit logged | Unit + system |
| TC-AUTH-04 | Authentication / input safety | Pass a null username or password to login API | Credentials rejected safely; no crash | Unit |
| TC-ADD-01 | Student management / FR-002 | Add valid student with 6 marks in [0,100] | Record inserted once; count increments; percentage and CGPA derived | Unit + system |
| TC-ADD-02 | Student management / FR-003 | Add a record with an existing roll number | Duplicate error; original array and count unchanged | Unit |\n| TC-ADD-03 | Student management / robustness | Call the insert API with a null record array | Invalid-field error; no crash or mutation | Unit |
| TC-VAL-01 | Validation / FR-012 | Submit marks below 0 and above 100 | Record rejected; no mutation | Unit |
| TC-VAL-02 | Validation | Submit semester outside supported 1–8 range | Record rejected | Unit |
| TC-SEARCH-01 | Search / FR-004 | Search an existing roll number using original and lower-case forms | Matching student returned case-insensitively | Unit + system |
| TC-SEARCH-02 | Search / FR-004 | Search by a name substring with mixed case | All matching records returned up to result capacity | Unit + system |
| TC-SEARCH-03 | Search | Pass null/invalid search arguments | Error code returned safely | Unit |
| TC-LIST-01 | Sorting / FR-007 | Sort populated records by CGPA descending, name, and roll number | Order matches selected comparator | Unit + system |
| TC-LIST-02 | Sorting | Sort with null/empty invalid input | Error returned; no crash | Unit |
| TC-CGPA-01 | Academic engine / FR-008 | Use six equal marks | Percentage is the arithmetic mean | Unit |
| TC-CGPA-02 | Academic engine / FR-008 | Use 100% input | CGPA does not exceed 10.0 | Unit |
| TC-CGPA-03 | Academic engine | Pass null marks array | Safe zero result | Unit |
| TC-RANK-01 | Rank list / FR-009, FR-011 | Export or view records with differing CGPAs | Highest CGPA appears first and rank numbering begins at 1 | Integration + system |
| TC-PERF-01 | Performance / NFR-001 | Search/sort 1,000 synthetic records | Combined benchmark does not exceed 2.0 seconds | Performance |
| TC-UPD-01 | Update / FR-005 | Update an existing record using valid fields and changed marks | Update succeeds; derived academic values recalculated | Unit + system |
| TC-UPD-02 | Update / FR-005 | Change a record's roll number to one already used | Duplicate rejected; original record unchanged | Unit |
| TC-UPD-03 | Update / FR-005 | Update using a mark above 100 | Rejected; original record unchanged | Unit |
| TC-UPD-04 | Update / FR-005 | Update an unknown roll number | Not-found result returned | Unit + system |
| TC-DEL-01 | Delete / FR-006 | Delete an existing roll number | Record removed; count decremented; later records compacted | Unit + system |
| TC-DEL-02 | Delete / FR-006 | At console prompt choose `N` or any non-`y` response | Cancellation message; record remains | Manual system |
| TC-DEL-03 | Delete / FR-006 | Delete an unknown roll number | Not-found result; no mutation | Unit + system |
| TC-PERSIST-01 | Storage / FR-010 | Save then load a valid data file | Same count and record data restored | Unit + integration |
| TC-PERSIST-02 | Storage / NFR-002 | Start with no `students.dat` | Initial records seeded and persisted | System / CI smoke |
| TC-PERSIST-03 | Storage / NFR-002 | Restart after a persisted change | Updated state is loaded; no duplicate reseeding | System / CI smoke |
| TC-REL-01 | Reliability / NFR-002 | Corrupt storage header or checksum | Load rejected as corrupt; existing file not silently overwritten | Unit + system |
| TC-EXPORT-01 | Report / FR-011 | Export a non-empty student list | `reports.txt` contains full list and CGPA-descending rank list | Unit + system |
| TC-EXPORT-02 | Report | Pass a null path or invalid count | Parameter error returned | Unit |
| TC-EXPORT-03 | Report | Export to inaccessible/nonexistent directory | I/O error returned | Unit |
| TC-PORT-01 | Portability / NFR-005, NFR-006 | Build and run with supported compiler/CI target | No compiler errors; tests pass | CI |

## 4. Traceability and status conventions

- **Automated:** test case is executed by a committed test executable or CI job.
- **CI verified:** latest recorded GitHub Actions run passed the relevant workflow step.
- **Manual pending:** requires interactive terminal input or human observation not captured by the automated harness.
- **Not measured:** no trustworthy runtime/coverage value has been collected for the current candidate.

The CI run on `main` dated 27 October 2026 passed compile-all, first-launch and restart-persistence smoke test, integrated unit suite, Sprint 2 regression suite, and 1,000-record performance benchmark. See [Build & Verify run](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/40484833650). This does not itself verify manual delete cancellation or Windows/MinGW execution.

## 5. Test execution procedure

```bash
make clean
make all
./test_suite
./test_search_list
./test_sprint2
./test_perf
```

The coverage build is described in `TEST_EXECUTION_GUIDE.md`. Run the suite in a disposable working directory because Sprint 2 tests create and remove temporary data files.

# Software Architecture & Design — Interface Design Addendum

This addendum documents the current module boundaries and public interfaces at a design level. It should be reviewed against the current headers before the final SAD PDF is regenerated.

## Component responsibilities

| Component | Main responsibility | Collaborators |
|---|---|---|
| Console application (`src/main.c`) | Menu workflow, prompts, input collection, and orchestration | Authentication, student management, search/list, CGPA, storage, reporting |
| Authentication (`src/auth.c`) | Login state, credential comparison, logout, timestamped audit events | Console application |
| Student management (`src/student_mgmt.c`) | Add/update/delete operations and record validation | Student model, CGPA |
| Academic computation (`src/cgpa.c`) | Percentage and CGPA derivation from marks | Student model |
| Search and listing (`src/search_list.c`) | Search by roll/name and sorting/listing | Student model |
| Storage (`src/storage.c`) | Binary serialization, load/save, integrity checks, safe replacement | Student model |
| Reporting (`src/report.c`) | Student report and descending academic rank output | Search/list and student model |

## Public interface catalogue

The declarations in the corresponding `include/*.h` headers are authoritative. The following table records the current API groups without inventing parameter types or return codes not stated in those headers.

| Header | Interface group | Caller-facing contract |
|---|---|---|
| `include/auth.h` | `int auth_login(const char *username, const char *password)`, `void auth_logout(void)`, `int auth_is_authenticated(void)`, `void log_auth_event(const char *username, const char *status)` | Authenticate, end session, query session state, and record audit events |
| `include/student_mgmt.h` | `validate_marks`, `validate_student_fields`, `find_student_by_roll`, `add_student_record`, `update_student_record`, `delete_student_record` | Validate fields/marks and create, locate, update, or delete records; return the declared `MGMT_*` status codes |
| `include/cgpa.h` | `float compute_percentage(const float marks[NUM_SUBJECTS])`, `float compute_cgpa(float percentage)`, `void update_student_academics(Student *s)` | Compute percentage and CGPA from the six subject marks |
| `include/search_list.h` | `search_by_roll_no`, `search_by_name`, `sort_students`, `display_student_card`, `display_student_table` | Case-insensitive search, in-place sort by `SortOrder`, and console display; status values are `SEARCH_SUCCESS`, `SEARCH_NOT_FOUND`, and `SEARCH_ERR_PARAM` |
| `include/storage.h` | `int load_students(const char *path, Student *students, int *count, int capacity)`, `int save_students(const char *path, const Student *students, int count)` | Load/save the local binary store; statuses are `STORAGE_SUCCESS`, `STORAGE_NOT_FOUND`, `STORAGE_ERR_IO`, `STORAGE_ERR_CORRUPT`, `STORAGE_ERR_PARAM`, and `STORAGE_ERR_CAPACITY` |
| `include/report.h` | `int export_student_reports(const char *path, const Student *students, int count)` | Write student listing and CGPA rank report; statuses are `REPORT_SUCCESS`, `REPORT_ERR_IO`, and `REPORT_ERR_PARAM` |
| `include/student.h` | Student data model | Shared record representation used by modules |

## Error handling and data contracts

- Validate pointers, counts, field lengths, and mark/semester ranges before dereferencing or persisting caller-supplied data.
- Return the status values declared by the relevant header; callers must check them before reporting success.
- File open/read/write/close failures must not be presented as successful persistence or export.
- Corrupt or unsupported storage data must be rejected safely; do not silently reinterpret it as a valid record set.
- Console-facing messages should be actionable and must not disclose passwords or credential material.
- Destructive deletion requires explicit confirmation in the console workflow.
- Derived percentage and CGPA values are computed from marks and should not be accepted as independent user-entered values.

## Security architecture and accepted demonstration decision

The current authentication implementation uses compile-time demonstration credentials (`admin` / `admin123`). The project owner has accepted this for the academic demonstration; it is a documented deviation from the original SEC-001 wording, not production-grade credential handling. The remaining controls—pre-login access gating, input validation, safe file handling, and timestamped audit logging—remain in scope. See `SECURITY_REQUIREMENT_GAP.md`.

## Traceability

| Requirement group | Responsible component(s) | Verification |
|---|---|---|
| FR-001, SEC-002, SEC-005 | Authentication + console | Authentication/session tests and audit-event tests |
| FR-002, FR-003, FR-005, FR-006, FR-012 | Student management + console | CRUD and validation suites; interactive update/delete checks |
| FR-004, FR-007 | Search/list | Search/list unit tests |
| FR-008, FR-009 | CGPA + search/list + report | Calculation and rank-list tests |
| FR-010, NFR-002, SEC-004 | Storage | Save/load, restart, corrupt-store and I/O tests |
| FR-011 | Report | Export tests and report inspection |
| NFR-001 | Search/list | 1,000-record performance benchmark |
| NFR-006 | Build/CI | Linux GCC and Windows MinGW workflows |


## Architecture details for previously empty SAD sections

### 3.1 Goals and constraints

**Goals:** Separate console interaction from business rules and persistence; validate student fields before mutation; keep academic calculations reusable; preserve records across restart and reject corrupt stores; support GCC/Linux and MinGW/Windows.

**Constraints:** C11 console application; no network service or web UI; local file-based persistence; maximum 1,000 student records; six subject marks per student; semester range 1–8; one administrator role; demonstration-only credential configuration.

### 3.2 Stakeholders and concerns

| Stakeholder | Main concern | Design response |
|---|---|---|
| Department academic office / administrator | Correct, quick record operations | Menu-driven CRUD, search, sorting, CGPA and rank reports |
| Student-record data owner | Avoid accidental loss or corruption | Validation, checked storage results, version/checksum validation and safe replacement |
| Developers / maintainers | Clear module boundaries and testability | Public headers, separate C modules, status codes and headless tests |
| QA / course evaluator | Verifiable and repeatable evidence | Test IDs, traceability CSV, Linux/Windows CI and release verification |

### 3.4 Component descriptions

- Console application (src/main.c): loads or initializes storage, authenticates the administrator, renders the 12-option menu, collects bounded input, calls module interfaces and reports outcomes.
- Authentication (src/auth.c): maintains process-local session state, checks the approved demonstration credential, logs authentication events with timestamps to login.log, and exposes login/logout/session functions.
- Student management (src/student_mgmt.c): validates mandatory fields, semester and marks; checks unique roll numbers; and performs add/update/delete operations.
- Academic computation (src/cgpa.c): computes percentage and CGPA from six subject marks.
- Search/list (src/search_list.c): performs case-insensitive roll/name search, selected in-place sorting and console display.
- Storage (src/storage.c): serializes records to the local versioned binary store, validates metadata/checksum on load and returns distinct missing/corrupt/invalid/capacity/I/O statuses.
- Reporting (src/report.c): writes student listing and CGPA-descending rank output to a text file.

### 3.7 Risks and mitigations

| Risk | Effect | Mitigation / limitation |
|---|---|---|
| Interrupted or failed file write | Incomplete or lost records | Versioned/checksummed storage and safe replacement logic; test failure paths |
| Corrupt/incompatible data file | Invalid records may be loaded | Validate metadata/checksum and fail safely |
| Invalid/oversized console input | Incorrect fields or memory corruption | Bounded input formats and field/range validation |
| Compiler/platform differences | Build/runtime mismatch | Linux GCC and Windows MinGW CI; keep build.bat aligned with CI |
| Demo credential embedded | Not suitable for real accounts or production | Accepted academic-demo-only deviation; use synthetic data only |
| Incomplete test evidence | Evaluator cannot reproduce claims | Link tests to CI/manual evidence and leave unexecuted scenarios pending |

### 3.8 Traceability to requirements

| Requirement | Component | Design element | Verification evidence |
|---|---|---|---|
| FR-001, FR-014, FR-015; SEC-002 | Authentication + console | Login/logout/session functions and three-attempt startup loop | Unit authentication tests; interactive lockout/menu-gating test still to record |
| FR-002, FR-003, FR-005, FR-006, FR-012 | Student management + console | CRUD and validation APIs; update/delete handlers | Integrated/Sprint 2 suites; interactive update/delete evidence |
| FR-004, FR-007 | Search/list | Roll/name search and sort functions | Search/list suite |
| FR-008, FR-009 | CGPA + search/list + report | Percentage/CGPA and rank ordering | CGPA and rank tests |
| FR-010; NFR-002; SEC-004 | Storage | Load/save and format/checksum validation | Storage regression, corruption and restart tests |
| FR-011 | Reporting | Report export function | Report tests and interactive report inspection |
| FR-013; SEC-005 | Console + authentication | Audit-log menu handler and event logger | Automated audit-event tests; interactive menu-view test still to record |
| SO-01 | Authentication + console | Session checks before record-management handlers | Authorization tests |
| SO-02 | Validation + storage + authentication | Field validation, safe file handling and timestamped logs | Input, storage and audit tests |

### 4.3 API / interface design — key contracts

The application is a single-process C program; interfaces are C function calls, not HTTP endpoints. Header declarations are authoritative.

- Authentication: auth_login(username, password) returns AUTH_SUCCESS, AUTH_ERR_CREDENTIALS or AUTH_ERR_LOCKED; auth_logout() clears the process session; auth_is_authenticated() reports session state.
- Student management: add_student_record(...), update_student_record(...) and delete_student_record(...) return declared MGMT_* status values. Callers report success only for MGMT_SUCCESS.
- Search: search_by_roll_no(...) returns SEARCH_SUCCESS, SEARCH_NOT_FOUND or SEARCH_ERR_PARAM; search_by_name(...) returns match count or -1.
- Sorting: sort_students(..., SortOrder) mutates the supplied array in place and returns 0 on success or -1 for invalid parameters.
- Storage: load_students(...) and save_students(...) return declared STORAGE_* status codes.
- Reporting: export_student_reports(...) returns REPORT_SUCCESS, REPORT_ERR_IO or REPORT_ERR_PARAM.

No public network API is exposed. Storage/report paths are local filesystem paths passed to module functions by the console controller.

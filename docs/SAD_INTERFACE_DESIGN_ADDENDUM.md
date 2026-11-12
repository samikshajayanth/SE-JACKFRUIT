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

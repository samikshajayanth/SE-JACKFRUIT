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
| `include/auth.h` | `auth_login`, `auth_logout`, `auth_is_authenticated`, `log_auth_event` | Authenticate, end session, query session state, and record audit events |
| `include/student_mgmt.h` | Student CRUD and validation functions | Create, update, delete, and validate student records |
| `include/cgpa.h` | Percentage and CGPA functions | Compute derived academic values from subject marks |
| `include/search_list.h` | Search, list, and sorting functions | Find records and produce selected ordering |
| `include/storage.h` | Load/save functions | Read and persist the local student data store |
| `include/report.h` | Report generation/export functions | Write student and rank-list output to a text file |
| `include/student.h` | Student data model | Shared record representation used by modules |

## Error handling and data contracts

- Validate pointers, counts, field lengths, and mark/semester ranges before dereferencing or persisting caller-supplied data.
- Return the status values declared by the relevant header; callers must check them before reporting success.
- File open/read/write/close failures must not be presented as successful persistence or export.
- Corrupt or unsupported storage data must be rejected safely; do not silently reinterpret it as a valid record set.
- Console-facing messages should be actionable and must not disclose passwords or credential material.
- Destructive deletion requires explicit confirmation in the console workflow.
- Derived percentage and CGPA values are computed from marks and should not be accepted as independent user-entered values.

## Security architecture limitation

The current authentication implementation uses compile-time demo credentials. This does not satisfy the SRS SEC-001 requirement for a separate restricted-access credentials file. The current design must be described as a demonstration-only authentication mechanism until that requirement is implemented. See `SECURITY_REQUIREMENT_GAP.md`.

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

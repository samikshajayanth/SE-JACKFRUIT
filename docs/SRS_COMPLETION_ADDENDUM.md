# SRS Completion Addendum — StudentRMS

**Purpose:** Complete requirement coverage and record the agreed demonstration-scope security decision for SRS v1.0. This addendum supplements, and does not silently rewrite, the submitted PDF.

## 1. Additional functional requirements

The submitted SRS lists FR-001 through FR-012. The university-provided SRS template asks for at least 15 functional requirements. The following three additional requirements describe functions already present in the current application; they do not introduce new product scope.

| ID | Functional requirement | Priority | Verification |
|---|---|---|---|
| FR-013 | The system shall allow an authenticated administrator to view the local authentication audit log from the main menu. | Medium | System test: log in, select audit-log menu item, verify timestamped events are displayed. |
| FR-014 | The system shall allow the authenticated administrator to log out, clear the authenticated session state, and terminate the application. | High | Unit/system test: call auth_logout(), verify auth_is_authenticated() returns false, then verify the application exits through the logout menu option. |
| FR-015 | The system shall stop accepting login attempts after three consecutive failed administrator login attempts during application startup and exit without exposing the record-management menu. | High | Negative/security system test: submit three invalid credential pairs and verify lockout message, non-zero exit, and no menu access. |

These requirements are supported by the current console menu and authentication flow in src/main.c, src/auth.c, and include/auth.h. Link their implementation and tests in the final RTM.

## 2. Security objectives

| Objective ID | Security objective | Related requirements | Verification |
|---|---|---|---|
| SO-01 — Access control | Prevent unauthenticated users from performing student record-management operations. | FR-001, SEC-002 | Attempt record operations without an authenticated session; verify access is denied. |
| SO-02 — Record integrity and auditability | Protect the integrity of student records through input validation and safe file handling, and maintain timestamped authentication events without logging passwords. | FR-012, SEC-003, SEC-004, SEC-005 | Negative input tests, storage failure/corruption tests, and audit-log inspection for timestamps and absence of passwords. |

## 3. Accepted demonstration credential deviation

The original SEC-001 wording requires credentials to be read from a separate restricted-access file and not embedded in source code. The project owner has accepted the current compiled demonstration credentials (admin / admin123) for this academic console project.

Record this as an explicit, accepted scope deviation. It is not technical compliance with the original SEC-001 text and is not a production security recommendation. The application is intended for synthetic academic demonstration data only. The final submission should state this decision consistently in the SRS, SAD, STP, traceability matrix, and final report. The other security controls remain in scope and must be verified.

## 4. Data model correction

The submitted SRS Appendix B lists an admin_password_hash field and the SAD lists credentials.dat. Those do not describe the current implementation. The Student structure in include/student.h contains only student record fields. Demonstration credentials are compile-time constants in src/auth.c; there is no credentials.dat credential store in the current application.

Update Appendix B to remove admin_username and admin_password_hash from the Student structure field layout. Describe the demo credential separately as a fixed demonstration configuration, with the accepted deviation above.

## 5. Traceability update

Add the following mappings to the final RTM:

| Requirement | Architecture/module | Design/interface | Test mapping |
|---|---|---|---|
| FR-013 | Authentication / Console UI | ui_view_audit_log() in src/main.c | Interactive audit-log inspection |
| FR-014 | Authentication / Console UI | auth_logout(), auth_is_authenticated() | Logout/session reset unit and system tests |
| FR-015 | Authentication / Console UI | Three-attempt startup loop in main() | Three invalid login attempts; verify lockout and no menu access |
| SO-01 | Authentication / Console UI | Session gate in record-management handlers | SEC-002 authorization tests |
| SO-02 | Validation / Storage / Authentication | Student validation, storage status handling, audit logging | SEC-003/004/005 tests |

## 6. SRS completeness checklist

- [x] At least 15 functional requirements: FR-001 to FR-015 after this addendum.
- [x] At least 5 non-functional requirements: the submitted SRS contains NFR-001 to NFR-006.
- [x] At least 2 explicit security objectives: SO-01 and SO-02 above.
- [x] At least 5 security requirements: SEC-001 to SEC-005 in the submitted SRS; SEC-001 has the accepted demonstration-scope deviation documented above.
- [ ] Update and re-export the final SRS PDF so the addendum, corrected team SRNs, actual data model, and accepted security deviation are incorporated into one consistent document.

# SEC-001 — Demonstration Credential Design Decision

## Agreed project scope

The project owner has confirmed that the current demonstration credentials are acceptable for this academic console application. The repository documents the demo login as `admin / admin123`; the credentials are compiled into the current authentication implementation.

This is an accepted demonstration-scope decision. It is not a claim that the application is suitable for production or that plaintext/embedded credentials are a recommended security practice.

## Relationship to the submitted SRS

The submitted SRS SEC-001 currently says that the administrator password must not be embedded in source code and must be read from a separate restricted-access credentials file.

The implemented demo behavior differs from that original wording. Record this as an explicit scope deviation/accepted exception for the academic demonstration. Do not mark the original SEC-001 wording as technically satisfied unless the SRS is formally revised and the change is accepted by the course/team evaluator.

## Controls that remain in scope

The accepted demo credential choice does not waive the other security checks:

- SEC-002: record-management operations are inaccessible before successful authentication.
- SEC-003: user input is length/type validated before use. Interactive text fields now reject empty and overlong values rather than silently truncating them; numeric parsing and all malformed-input paths should continue to be tested.
- SEC-004: file I/O failures are handled without corrupting stored records.
- SEC-005: failed login attempts are timestamped in the local audit log.
- Passwords or credential material must not be written into logs.

## Operational limitation

Use the demonstration credentials only with synthetic academic test data. Do not reuse them for personal, institutional, or production accounts.

## Submission disposition

**Decision:** retain the current demo credentials; no credentials-file implementation is planned for this project scope.

**Documentation action still required:** update the SRS/SAD security wording or include this deviation in the final report, and obtain any required team/course approval. The existing SRS text is otherwise inconsistent with the implemented design.

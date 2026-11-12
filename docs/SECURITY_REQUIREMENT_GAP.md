# Security Requirement Gap — SEC-001

## Current implementation

The current demonstration build defines the administrator username and password in `src/auth.c`:

- Username: `admin`
- Password: `admin123`

The README explicitly identifies these as hard-coded educational/demo credentials and warns against production reuse.

## SRS requirement

SEC-001 in the submitted SRS requires that administrator credentials are not embedded in source code and are read from a separate, restricted-access credentials file.

## Compliance status

**NOT COMPLIANT.** The current source does not read a separate credentials file. Authentication and session gating tests do not demonstrate compliance with credential-at-rest requirements. This is a documented gap, not a passed security control.

## Required remediation before claiming SEC-001 compliance

1. Replace compile-time credential constants with a credentials provider that reads from a configurable local file.
2. Fail closed if the file is missing, unreadable, malformed, or has unsafe permissions; do not silently fall back to embedded credentials.
3. Document the file format, location, access-control expectations, and setup procedure without committing real credentials.
4. Update authentication tests to cover valid credentials, invalid credentials, missing file, unreadable file, malformed file, and permission errors.
5. Ensure logs never include passwords or credential-file contents.
6. Re-run Linux and Windows CI and update the SRS, SAD security architecture, test plan, and traceability matrix together.

## Disposition for this submission

Until that implementation and its tests exist, retain SEC-001 as an open requirement gap. The demo credential is for local academic demonstration only and must not be used for real accounts or production data.

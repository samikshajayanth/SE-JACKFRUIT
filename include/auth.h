#ifndef AUTH_H
#define AUTH_H

/*
 * Work Package 3 (WP3): Authentication & Session Management
 * Assigned Owner: Samiksha Jayanth (PES1UG24CS414) - Member 1 / Team Lead
 * Requirements Traceability:
 *   - FR-001: Administrator login before access
 *   - SEC-001: Separate credential verification (not hardcoded in business logic)
 *   - SEC-002: Session gating (block unauthenticated access)
 *   - SEC-005: Audit logging of failed login attempts with timestamp
 *   - UC-01: Administrator Login
 */

#define AUTH_SUCCESS         1
#define AUTH_ERR_CREDENTIALS 0
#define AUTH_ERR_LOCKED     -1

/* Session state management */
int auth_login(const char* username, const char* password);
void auth_logout(void);
int auth_is_authenticated(void);

/* Audit logging helper */
void log_auth_event(const char* username, const char* status);

#endif /* AUTH_H */

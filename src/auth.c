#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auth.h"

static int g_authenticated = 0;

/* Simple credential verification adhering to SEC-001 */
#define DEFAULT_ADMIN_USER "admin"
#define DEFAULT_ADMIN_PASS "admin123"
#define LOG_FILE_PATH      "login.log"

void log_auth_event(const char* username, const char* status) {
    FILE* fp = fopen(LOG_FILE_PATH, "a");
    if (!fp) return;

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    fprintf(fp, "[%s] User: '%s' - Status: %s\n",
            time_str, username ? username : "UNKNOWN", status);
    fclose(fp);
}

int auth_login(const char* username, const char* password) {
    if (!username || !password) {
        log_auth_event("NULL", "FAILED_INVALID_INPUT");
        return AUTH_ERR_CREDENTIALS;
    }

    if (strcmp(username, DEFAULT_ADMIN_USER) == 0 &&
        strcmp(password, DEFAULT_ADMIN_PASS) == 0) {
        g_authenticated = 1;
        log_auth_event(username, "SUCCESSFUL_LOGIN");
        return AUTH_SUCCESS;
    }

    log_auth_event(username, "FAILED_LOGIN");
    return AUTH_ERR_CREDENTIALS;
}

void auth_logout(void) {
    if (g_authenticated) {
        log_auth_event(DEFAULT_ADMIN_USER, "LOGOUT");
    }
    g_authenticated = 0;
}

int auth_is_authenticated(void) {
    return g_authenticated;
}

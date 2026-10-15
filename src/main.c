#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "student.h"
#include "student_mgmt.h"
#include "search_list.h"
#include "cgpa.h"

#define MAX_SYSTEM_RECORDS 1000

static Student g_students[MAX_SYSTEM_RECORDS];
static int g_count = 0;

static void seed_initial_records(void) {
    Student team_records[] = {
        {"PES1UG24CS414", "Samiksha Jayanth", "CSE", 5, {88, 92, 90, 89, 94, 91}, 0, 0},
        {"PES1UG24CS381", "Rohan M",          "CSE", 5, {95, 96, 94, 98, 92, 97}, 0, 0},
        {"PES1UG24CS404", "Saksham Bajpayi",  "CSE", 5, {82, 85, 80, 84, 86, 83}, 0, 0},
        {"PES1UG24CS372", "Riddhi Mundada",   "CSE", 5, {91, 93, 89, 92, 90, 94}, 0, 0},
        {"PES1UG24CS101", "Aarav Sharma",     "ECE", 5, {75, 78, 82, 79, 81, 74}, 0, 0},
        {"PES1UG24CS102", "Ananya Verma",     "AIML", 5, {89, 91, 90, 92, 88, 90}, 0, 0}
    };
    int n = sizeof(team_records) / sizeof(team_records[0]);
    for (int i = 0; i < n; i++) {
        add_student_record(g_students, &g_count, MAX_SYSTEM_RECORDS, &team_records[i]);
    }
}

static void ui_add_student(void) {
    if (!auth_is_authenticated()) {
        printf("\n[SECURITY ALERT] Unauthenticated access blocked (SEC-002).\n");
        return;
    }

    Student s;
    memset(&s, 0, sizeof(s));

    printf("\n--- Add New Student Record (FR-002, UC-02) ---\n");
    printf("Enter Roll Number (e.g. PES1UG24CS200): ");
    if (scanf("%15s", s.roll_no) != 1) return;

    if (find_student_by_roll(g_students, g_count, s.roll_no) != -1) {
        printf("[ERROR] Roll number '%s' already exists! Duplicate records prohibited (FR-003).\n", s.roll_no);
        return;
    }

    printf("Enter Full Name: ");
    getchar(); /* consume newline */
    if (!fgets(s.name, sizeof(s.name), stdin)) return;
    s.name[strcspn(s.name, "\r\n")] = 0;

    printf("Enter Department (e.g. CSE): ");
    if (scanf("%19s", s.department) != 1) return;

    printf("Enter Semester (1-8): ");
    if (scanf("%d", &s.semester) != 1 || s.semester < 1 || s.semester > 8) {
        printf("[ERROR] Semester must be between 1 and 8.\n");
        return;
    }

    printf("Enter marks for 6 subjects (0.0 to 100.0 each):\n");
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("  Subject %d: ", i + 1);
        if (scanf("%f", &s.subject_marks[i]) != 1 ||
            s.subject_marks[i] < 0.0f || s.subject_marks[i] > 100.0f) {
            printf("[ERROR] Invalid marks! Each mark must be between 0.0 and 100.0 (FR-012).\n");
            return;
        }
    }

    int res = add_student_record(g_students, &g_count, MAX_SYSTEM_RECORDS, &s);
    if (res == MGMT_SUCCESS) {
        printf("\n[SUCCESS] Student record added successfully!\n");
        printf("Calculated Percentage : %.2f%%\n", g_students[g_count - 1].percentage);
        printf("Calculated CGPA       : %.2f\n", g_students[g_count - 1].cgpa);
    } else {
        printf("\n[ERROR] Failed to add record (Code: %d).\n", res);
    }
}

static void ui_search_roll(void) {
    char roll[MAX_ROLL_LEN];
    printf("\n--- Search Record by Roll Number (FR-004, UC-03) ---\n");
    printf("Enter Roll Number: ");
    if (scanf("%15s", roll) != 1) return;

    Student result;
    int status = search_by_roll_no(g_students, g_count, roll, &result);
    if (status == SEARCH_SUCCESS) {
        printf("\n[SUCCESS] Matching Record Found:\n");
        display_student_card(&result);
    } else {
        printf("\n[INFO] No student record matches roll number '%s'.\n", roll);
    }
}

static void ui_search_name(void) {
    char query[MAX_NAME_LEN];
    printf("\n--- Search Record by Name Substring (FR-004, UC-03) ---\n");
    printf("Enter name or partial substring: ");
    getchar();
    if (!fgets(query, sizeof(query), stdin)) return;
    query[strcspn(query, "\r\n")] = 0;

    Student results[50];
    int found = search_by_name(g_students, g_count, query, results, 50);
    if (found > 0) {
        printf("\n[SUCCESS] Found %d matching record(s):\n", found);
        display_student_table(results, found);
    } else {
        printf("\n[INFO] No records found matching query '%s'.\n", query);
    }
}

static void ui_sort_records(int choice) {
    SortOrder order;
    const char* label = "";
    switch (choice) {
        case 5: order = SORT_BY_CGPA_DESC; label = "CGPA Rank List (Highest First)"; break;
        case 6: order = SORT_BY_NAME_ASC; label = "Name Alphabetically"; break;
        case 7: order = SORT_BY_ROLL_ASC; label = "Roll Number (Ascending)"; break;
        default: return;
    }
    sort_students(g_students, g_count, order);
    printf("\n[SUCCESS] Records sorted by %s:\n", label);
    display_student_table(g_students, g_count);
}

static void ui_view_audit_log(void) {
    printf("\n--- Security Audit Log (login.log, SEC-005) ---\n");
    FILE* fp = fopen("login.log", "r");
    if (!fp) {
        printf("No login activity logged yet.\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

int main(void) {
    seed_initial_records();

    printf("============================================================\n");
    printf("    StudentRMS - Student Record Management System           \n");
    printf("    Team 4 | Software Engineering (UE24CS341A)              \n");
    printf("    Sprint 1 Working Product Release                        \n");
    printf("============================================================\n");

    /* Step 1: Authentication Gate (SEC-002, UC-01) */
    char username[64];
    char password[64];
    int attempts = 0;

    while (attempts < 3) {
        printf("\n[ADMINISTRATOR LOGIN REQUIRED]\n");
        printf("Username: ");
        if (scanf("%63s", username) != 1) return 1;
        printf("Password: ");
        if (scanf("%63s", password) != 1) return 1;

        if (auth_login(username, password) == AUTH_SUCCESS) {
            printf("\n>>> Authentication Successful! Welcome, Administrator. <<<\n");
            break;
        } else {
            attempts++;
            printf("\n[ERROR] Invalid credentials! Attempt %d of 3.\n", attempts);
        }
    }

    if (!auth_is_authenticated()) {
        printf("\n[ALERT] Maximum login attempts exceeded. Access locked out (SEC-002).\n");
        return 1;
    }

    /* Step 2: Main Operational Menu (NFR-003: Usability <= 3 clicks) */
    int choice = 0;
    while (1) {
        printf("\n============================================================\n");
        printf("              StudentRMS Main Menu (Sprint 1)               \n");
        printf("============================================================\n");
        printf("  1. View All Students (Table View)\n");
        printf("  2. Add New Student Record (FR-002, UC-02)\n");
        printf("  3. Search Record by Roll Number (FR-004, UC-03)\n");
        printf("  4. Search Record by Name (FR-004, UC-03)\n");
        printf("  5. Sort / Generate Rank List by CGPA (FR-007, FR-009)\n");
        printf("  6. Sort Alphabetically by Name (FR-007, UC-06)\n");
        printf("  7. Sort by Roll Number (FR-007, UC-06)\n");
        printf("  8. View Authentication Security Audit Log (SEC-005)\n");
        printf("  9. Logout & Exit (UC-01)\n");
        printf("============================================================\n");
        printf("Enter option [1-9]: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                display_student_table(g_students, g_count);
                break;
            case 2:
                ui_add_student();
                break;
            case 3:
                ui_search_roll();
                break;
            case 4:
                ui_search_name();
                break;
            case 5:
            case 6:
            case 7:
                ui_sort_records(choice);
                break;
            case 8:
                ui_view_audit_log();
                break;
            case 9:
                auth_logout();
                printf("\nLogged out safely. Exiting StudentRMS. Have a great day!\n");
                return 0;
            default:
                printf("\nInvalid selection! Please enter a choice from 1 to 9.\n");
        }
    }

    return 0;
}

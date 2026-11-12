#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#include <io.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include "auth.h"
#include "student.h"
#include "student_mgmt.h"
#include "search_list.h"
#include "cgpa.h"
#include "storage.h"
#include "report.h"

#define MAX_SYSTEM_RECORDS 1000
#define STORAGE_FILE_PATH "students.dat"
#define REPORT_FILE_PATH "reports.txt"

static Student g_students[MAX_SYSTEM_RECORDS];
static int g_count = 0;

static void discard_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

/* Read a complete bounded field; reject rather than silently truncate. */
static int read_text_field(const char* prompt, char* destination, size_t capacity) {
    size_t length;
    int ch;
    if (!prompt || !destination || capacity < 2) return 0;
    printf("%s", prompt);
    if (!fgets(destination, (int)capacity, stdin)) return 0;
    length = strcspn(destination, "\r\n");
    if (length == capacity - 1 && destination[length] == '\0') {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            discard_line();
            destination[0] = '\0';
            printf("[ERROR] Input is too long (maximum %zu characters).\n", capacity - 1);
            return 0;
        }
    } else {
        destination[length] = '\0';
    }
    if (length == 0) {
        printf("[ERROR] This field cannot be empty.\n");
        return 0;
    }
    return 1;
}

/* Hide the administrator password on interactive terminals. CI/piped input
   falls back to the same bounded line reader so automated smoke tests work. */
static int read_password_field(const char* prompt, char* destination, size_t capacity) {
    if (!prompt || !destination || capacity < 2) return 0;
#ifdef _WIN32
    if (!_isatty(_fileno(stdin))) return read_text_field(prompt, destination, capacity);
    printf("%s", prompt);
    fflush(stdout);
    size_t length = 0;
    int too_long = 0;
    int ch;
    while ((ch = _getch()) != '\r' && ch != '\n') {
        if (ch == 8) {
            if (length > 0) length--;
            continue;
        }
        if (ch == 0 || ch == 224) {
            (void)_getch();
            continue;
        }
        if (length + 1 < capacity && !too_long) destination[length++] = (char)ch;
        else too_long = 1;
    }
    destination[length] = '\0';
    putchar('\n');
    if (too_long) {
        destination[0] = '\0';
        printf("[ERROR] Input is too long (maximum %zu characters).\n", capacity - 1);
        return 0;
    }
    if (length == 0) {
        printf("[ERROR] This field cannot be empty.\n");
        return 0;
    }
    return 1;
#else
    if (!isatty(STDIN_FILENO)) return read_text_field(prompt, destination, capacity);
    struct termios original, hidden;
    if (tcgetattr(STDIN_FILENO, &original) != 0)
        return read_text_field(prompt, destination, capacity);
    hidden = original;
    hidden.c_lflag &= (tcflag_t)~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &hidden) != 0)
        return read_text_field(prompt, destination, capacity);
    int result = read_text_field(prompt, destination, capacity);
    (void)tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    putchar('\n');
    return result;
#endif
}

static void seed_initial_records(void) {
    Student demo_records[] = {
        {"DEMO2026CS001", "Aarav Mehta", "CSE", 5, {88, 82, 90, 89, 84, 91}, 0, 0},
        {"DEMO2026CS002", "Diya Kapoor", "ECE", 5, {75, 78, 82, 79, 81, 74}, 0, 0},
        {"DEMO2026CS003", "Kabir Shah", "CSE", 5, {95, 86, 94, 88, 92, 87}, 0, 0},
        {"DEMO2026CS004", "Mira Nair", "AIML", 5, {91, 83, 89, 92, 90, 84}, 0, 0},
        {"DEMO2026CS005", "Ishaan Rao", "EEE", 5, {78, 81, 76, 85, 80, 79}, 0, 0},
        {"DEMO2026CS006", "Anaya Iyer", "CSE", 5, {89, 91, 90, 82, 88, 86}, 0, 0}
    };
    int n = (int)(sizeof(demo_records) / sizeof(demo_records[0]));
    for (int i = 0; i < n; i++)
        (void)add_student_record(g_students, &g_count, MAX_SYSTEM_RECORDS, &demo_records[i]);
}

static int persist_current_state(void) {
    int result = save_students(STORAGE_FILE_PATH, g_students, g_count);
    if (result != STORAGE_SUCCESS) {
        printf("\n[ERROR] Could not save %s (storage code %d). Changes were rolled back where possible.\n",
               STORAGE_FILE_PATH, result);
        return 0;
    }
    return 1;
}

static int prompt_student_details(Student* s) {
    if (!s) return 0;
    memset(s, 0, sizeof(*s));
    if (!read_text_field("Roll Number: ", s->roll_no, sizeof(s->roll_no))) return 0;
    if (!read_text_field("Full Name: ", s->name, sizeof(s->name))) return 0;
    if (!read_text_field("Department: ", s->department, sizeof(s->department))) return 0;
    printf("Semester (1-8): ");
    if (scanf("%d", &s->semester) != 1) {
        discard_line();
        printf("[ERROR] Semester must be an integer from 1 to 8.\n");
        return 0;
    }
    if (s->semester < 1 || s->semester > 8) {
        discard_line();
        printf("[ERROR] Semester must be between 1 and 8.\n");
        return 0;
    }

    printf("Marks for 6 subjects (0.0 to 100.0):\n");
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("  Subject %d: ", i + 1);
        if (scanf("%f", &s->subject_marks[i]) != 1 ||
            !(s->subject_marks[i] >= 0.0f && s->subject_marks[i] <= 100.0f)) {
            discard_line();
            printf("[ERROR] Each mark must be a number between 0.0 and 100.0.\n");
            return 0;
        }
    }
    if (!validate_student_fields(s)) {
        printf("[ERROR] One or more student fields are invalid.\n");
        return 0;
    }
    update_student_academics(s);
    return 1;
}

static void ui_add_student(void) {
    if (!auth_is_authenticated()) {
        printf("\n[SECURITY ALERT] Unauthenticated access blocked.\n");
        return;
    }
    Student s;
    printf("\n--- Add Student Record ---\n");
    discard_line(); /* Consume the newline left by the menu selection. */
    if (!prompt_student_details(&s)) return;

    int result = add_student_record(g_students, &g_count, MAX_SYSTEM_RECORDS, &s);
    if (result != MGMT_SUCCESS) {
        printf("[ERROR] Add failed (management code %d).\n", result);
        return;
    }
    if (!persist_current_state()) {
        g_count--;
        memset(&g_students[g_count], 0, sizeof(g_students[g_count]));
        return;
    }
    printf("[SUCCESS] Student added. Percentage %.2f%%, CGPA %.2f.\n",
           g_students[g_count - 1].percentage, g_students[g_count - 1].cgpa);
}

static void ui_update_student(void) {
    char lookup_roll[MAX_ROLL_LEN];
    Student updated, previous;
    int index;
    if (!auth_is_authenticated()) {
        printf("\n[SECURITY ALERT] Unauthenticated access blocked.\n");
        return;
    }

    printf("\n--- Update Student Record (FR-005) ---\n");
    discard_line();
    if (!read_text_field("Current roll number: ", lookup_roll, sizeof(lookup_roll))) return;
    index = find_student_by_roll(g_students, g_count, lookup_roll);
    if (index < 0) {
        printf("[INFO] No student exists with roll number '%s'.\n", lookup_roll);
        return;
    }

    previous = g_students[index];
    printf("\nCurrent record:\n");
    display_student_card(&previous);
    printf("Enter the complete replacement details. Keep the same roll number to leave it unchanged.\n");
    if (!prompt_student_details(&updated)) return;

    int result = update_student_record(g_students, g_count, lookup_roll, &updated);
    if (result != MGMT_SUCCESS) {
        printf("[ERROR] Update rejected (management code %d); original record is unchanged.\n", result);
        return;
    }
    if (!persist_current_state()) {
        g_students[index] = previous;
        return;
    }
    printf("[SUCCESS] Record updated. Percentage %.2f%%, CGPA %.2f.\n",
           g_students[index].percentage, g_students[index].cgpa);
}

static void restore_deleted_student(int index, const Student* student) {
    if (!student || g_count >= MAX_SYSTEM_RECORDS || index < 0 || index > g_count) return;
    for (int i = g_count; i > index; i--) g_students[i] = g_students[i - 1];
    g_students[index] = *student;
    g_count++;
}

static void ui_delete_student(void) {
    char roll[MAX_ROLL_LEN], confirmation;
    Student removed;
    int index;
    if (!auth_is_authenticated()) {
        printf("\n[SECURITY ALERT] Unauthenticated access blocked.\n");
        return;
    }

    printf("\n--- Delete Student Record (FR-006) ---\n");
    discard_line();
    if (!read_text_field("Roll number: ", roll, sizeof(roll))) return;
    index = find_student_by_roll(g_students, g_count, roll);
    if (index < 0) {
        printf("[INFO] No student exists with roll number '%s'.\n", roll);
        return;
    }

    removed = g_students[index];
    printf("\nYou are about to delete this record:\n");
    display_student_card(&removed);
    printf("Confirm deletion? [y/N]: ");
    if (scanf(" %c", &confirmation) != 1) {
        discard_line();
        return;
    }
    discard_line();
    if (confirmation != 'y' && confirmation != 'Y') {
        printf("[CANCELLED] Record was not changed.\n");
        return;
    }

    int result = delete_student_record(g_students, &g_count, roll);
    if (result != MGMT_SUCCESS) {
        printf("[ERROR] Delete failed (management code %d).\n", result);
        return;
    }
    if (!persist_current_state()) {
        restore_deleted_student(index, &removed);
        return;
    }
    printf("[SUCCESS] Student record deleted.\n");
}

static void ui_search_roll(void) {
    char roll[MAX_ROLL_LEN];
    Student result;
    printf("\n--- Search by Roll Number ---\n");
    discard_line();
    if (!read_text_field("Roll Number: ", roll, sizeof(roll))) return;
    if (search_by_roll_no(g_students, g_count, roll, &result) == SEARCH_SUCCESS)
        display_student_card(&result);
    else
        printf("[INFO] No record matches '%s'.\n", roll);
}

static void ui_search_name(void) {
    char query[MAX_NAME_LEN];
    Student results[MAX_SYSTEM_RECORDS];
    printf("\n--- Search by Name ---\n");
    discard_line();
    if (!read_text_field("Enter a name or substring: ", query, sizeof(query))) return;
    int found = search_by_name(g_students, g_count, query, results, MAX_SYSTEM_RECORDS);
    if (found > 0) display_student_table(results, found);
    else printf("[INFO] No records found matching '%s'.\n", query);
}

static void ui_sort_records(int choice) {
    SortOrder order;
    const char* label;
    switch (choice) {
        case 7: order = SORT_BY_CGPA_DESC; label = "CGPA / Rank List"; break;
        case 8: order = SORT_BY_NAME_ASC; label = "Name"; break;
        case 9: order = SORT_BY_ROLL_ASC; label = "Roll Number"; break;
        default: return;
    }
    if (sort_students(g_students, g_count, order) != 0) {
        printf("[INFO] No records available to sort.\n");
        return;
    }
    printf("\n[SUCCESS] Sorted by %s.\n", label);
    display_student_table(g_students, g_count);
}

static void ui_export_reports(void) {
    int result = export_student_reports(REPORT_FILE_PATH, g_students, g_count);
    if (result == REPORT_SUCCESS)
        printf("[SUCCESS] Exported student and rank reports to %s.\n", REPORT_FILE_PATH);
    else
        printf("[ERROR] Could not export %s (report code %d). Check path and permissions.\n",
               REPORT_FILE_PATH, result);
}

static void ui_view_audit_log(void) {
    FILE* fp = fopen("login.log", "r");
    char line[256];
    printf("\n--- Security Audit Log (login.log) ---\n");
    if (!fp) {
        printf("No login activity logged yet.\n");
        return;
    }
    while (fgets(line, sizeof(line), fp)) printf("%s", line);
    fclose(fp);
}

int main(void) {
    int storage_result = load_students(STORAGE_FILE_PATH, g_students, &g_count, MAX_SYSTEM_RECORDS);
    if (storage_result == STORAGE_NOT_FOUND) {
        seed_initial_records();
        if (g_count == 0 || !persist_current_state()) {
            fprintf(stderr, "[FATAL] Could not initialize persistent student data.\n");
            return 1;
        }
        printf("[INFO] First launch: created %s with sample records.\n", STORAGE_FILE_PATH);
    } else if (storage_result != STORAGE_SUCCESS) {
        fprintf(stderr,
                "[FATAL] Could not safely load %s (storage code %d). Existing data was not overwritten.\n",
                STORAGE_FILE_PATH, storage_result);
        return 1;
    } else {
        printf("[INFO] Loaded %d student record(s) from %s.\n", g_count, STORAGE_FILE_PATH);
    }

    printf("============================================================\n");
    printf("    StudentRMS - Student Record Management System           \n");
    printf("    Team 4 | Software Engineering (UE24CS341A)              \n");
    printf("    Sprint 2 Working Product                                \n");
    printf("============================================================\n");

    char username[64], password[64];
    int attempts = 0;
    while (attempts < 3) {
        printf("\n[ADMINISTRATOR LOGIN REQUIRED]\n");
        if (!read_text_field("Username: ", username, sizeof(username))) {
            attempts++;
            printf("[ERROR] Invalid username input. Attempt %d of 3.\n", attempts);
            continue;
        }
        if (!read_password_field("Password: ", password, sizeof(password))) {
            attempts++;
            printf("[ERROR] Invalid password input. Attempt %d of 3.\n", attempts);
            continue;
        }
        if (auth_login(username, password) == AUTH_SUCCESS) {
            printf("\n>>> Authentication successful. Welcome, Administrator. <<<\n");
            break;
        }
        attempts++;
        printf("\n[ERROR] Invalid credentials! Attempt %d of 3.\n", attempts);
    }
    if (!auth_is_authenticated()) {
        printf("\n[ALERT] Maximum login attempts exceeded. Access locked out.\n");
        return 1;
    }

    while (1) {
        int choice;
        printf("\n============================================================\n");
        printf("                 StudentRMS Main Menu                       \n");
        printf("============================================================\n");
        printf("  1. View All Students\n");
        printf("  2. Add Student Record\n");
        printf("  3. Update Student Record (FR-005)\n");
        printf("  4. Delete Student Record (FR-006)\n");
        printf("  5. Search by Roll Number\n");
        printf("  6. Search by Name\n");
        printf("  7. Generate Rank List / Sort by CGPA\n");
        printf("  8. Sort Alphabetically by Name\n");
        printf("  9. Sort by Roll Number\n");
        printf(" 10. Export Student and Rank Reports (FR-011)\n");
        printf(" 11. View Authentication Audit Log\n");
        printf(" 12. Logout and Exit\n");
        printf("============================================================\nEnter option [1-12]: ");
        if (scanf("%d", &choice) != 1) {
            discard_line();
            printf("[ERROR] Enter a menu number from 1 to 12.\n");
            continue;
        }
        switch (choice) {
            case 1: display_student_table(g_students, g_count); break;
            case 2: ui_add_student(); break;
            case 3: ui_update_student(); break;
            case 4: ui_delete_student(); break;
            case 5: ui_search_roll(); break;
            case 6: ui_search_name(); break;
            case 7:
            case 8:
            case 9: ui_sort_records(choice); break;
            case 10: ui_export_reports(); break;
            case 11: ui_view_audit_log(); break;
            case 12:
                auth_logout();
                printf("\nLogged out safely. Exiting StudentRMS.\n");
                return 0;
            default: printf("[ERROR] Choose a valid option from 1 to 12.\n");
        }
    }
}

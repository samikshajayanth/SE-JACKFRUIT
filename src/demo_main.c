#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_list.h"

static Student records[10] = {
    {"PES1UG24CS414", "Samiksha Jayanth", "CSE", 5, {85, 90, 88, 92, 84, 89}, 88.0f, 9.2f},
    {"PES1UG24CS381", "Rohan M",          "CSE", 5, {92, 95, 90, 94, 91, 96}, 93.0f, 9.6f},
    {"PES1UG24CS404", "Saksham Bajpayi",  "CSE", 5, {78, 82, 80, 85, 79, 81}, 80.8f, 8.4f},
    {"PES1UG24CS372", "Riddhi Mundada",   "CSE", 5, {88, 89, 91, 87, 90, 92}, 89.5f, 9.3f},
    {"PES1UG24CS101", "Aarav Sharma",     "ECE", 5, {75, 80, 82, 79, 81, 78}, 79.1f, 8.1f},
    {"PES1UG24CS102", "Diya Patel",       "AIML", 5, {90, 91, 93, 89, 94, 92}, 91.5f, 9.5f},
    {"PES1UG24CS103", "Karan Rao",        "CSE", 5, {70, 72, 74, 71, 73, 75}, 72.5f, 7.5f}
};
static int record_count = 7;

static void handle_search_roll() {
    char roll[MAX_ROLL_LEN];
    printf("\nEnter Roll Number to search: ");
    if (scanf("%15s", roll) != 1) return;
    
    Student found;
    int status = search_by_roll_no(records, record_count, roll, &found);
    if (status == SEARCH_SUCCESS) {
        printf("\n[SUCCESS] Record found:\n");
        display_student_card(&found);
    } else {
        printf("\n[ERROR] No student record found for roll number '%s'.\n", roll);
    }
}

static void handle_search_name() {
    char query[MAX_NAME_LEN];
    printf("\nEnter Name (or partial query) to search: ");
    getchar(); /* consume newline */
    if (!fgets(query, sizeof(query), stdin)) return;
    query[strcspn(query, "\r\n")] = 0; /* strip newline */

    Student matches[10];
    int count = search_by_name(records, record_count, query, matches, 10);
    if (count > 0) {
        printf("\n[SUCCESS] Found %d matching student(s):\n", count);
        display_student_table(matches, count);
    } else {
        printf("\n[INFO] No students found matching '%s'.\n", query);
    }
}

static void handle_sort(int choice) {
    SortOrder order;
    const char* label = "";
    switch (choice) {
        case 4: order = SORT_BY_ROLL_ASC; label = "Roll Number (Ascending)"; break;
        case 5: order = SORT_BY_NAME_ASC; label = "Name (Alphabetical)"; break;
        case 6: order = SORT_BY_CGPA_DESC; label = "CGPA (Rank List / Descending)"; break;
        default: return;
    }
    sort_students(records, record_count, order);
    printf("\n[SUCCESS] Records sorted by %s:\n", label);
    display_student_table(records, record_count);
}

int main() {
    int choice = 0;
    while (1) {
        printf("\n============================================================\n");
        printf("    StudentRMS - Module WP4 (Record Search & Listing)       \n");
        printf("    Lead Developer: Rohan M (PES1UG24CS381) - Member 2     \n");
        printf("    Sprint 1 Working Product Demo                          \n");
        printf("============================================================\n");
        printf("  1. View All Current Records\n");
        printf("  2. Search Record by Roll Number (FR-004 / UC-03)\n");
        printf("  3. Search Record by Name (FR-004 / UC-03)\n");
        printf("  4. Sort by Roll Number (FR-007 / UC-06)\n");
        printf("  5. Sort by Name (FR-007 / UC-06)\n");
        printf("  6. Sort by CGPA / Rank Order (FR-007 / UC-06)\n");
        printf("  7. Exit Demo\n");
        printf("============================================================\n");
        printf("Enter your choice [1-7]: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                display_student_table(records, record_count);
                break;
            case 2:
                handle_search_roll();
                break;
            case 3:
                handle_search_name();
                break;
            case 4:
            case 5:
            case 6:
                handle_sort(choice);
                break;
            case 7:
                printf("\nExiting StudentRMS Sprint 1 Demo. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid option! Please enter a number from 1 to 7.\n");
        }
    }
    return 0;
}

#ifndef SEARCH_LIST_H
#define SEARCH_LIST_H

#include "student.h"

/*
 * Work Package 4 (WP4): Record Search, View & Listing Module
 * Assigned Owner: Rohan M (PES1UG24CS381) - Member 2
 * Requirements Traceability:
 *   - FR-004: Search record by roll number or name
 *   - FR-007: List records, sortable by roll number, name, or CGPA
 *   - NFR-001: Performance <= 2.0s for up to 1000 records
 *   - UC-03: Search / View Record
 *   - UC-06: List & Sort Records
 */

typedef enum {
    SORT_BY_ROLL_ASC = 1,
    SORT_BY_ROLL_DESC,
    SORT_BY_NAME_ASC,
    SORT_BY_NAME_DESC,
    SORT_BY_CGPA_ASC,
    SORT_BY_CGPA_DESC
} SortOrder;

/* Status return codes */
#define SEARCH_SUCCESS    1
#define SEARCH_NOT_FOUND  0
#define SEARCH_ERR_PARAM -1

/*
 * FR-004: Search by Roll Number
 * Searches for an exact match (case-insensitive) of roll_no in the students array.
 * If found, copies the record to *result and returns SEARCH_SUCCESS (1).
 * If not found, returns SEARCH_NOT_FOUND (0).
 * If invalid parameters, returns SEARCH_ERR_PARAM (-1).
 */
int search_by_roll_no(const Student* students, int count, const char* roll_no, Student* result);

/*
 * FR-004: Search by Name
 * Searches for students whose name contains query as a substring (case-insensitive).
 * Stores matches into results[] up to max_results.
 * Returns the count of matching records found, or -1 on error.
 */
int search_by_name(const Student* students, int count, const char* query, Student* results, int max_results);

/*
 * FR-007: Sort Students
 * In-place sorts an array of students according to the specified SortOrder.
 * Returns 0 on success, -1 on invalid parameter.
 */
int sort_students(Student* students, int count, SortOrder order);

/*
 * Display Helpers (Console Formatting)
 */
void display_student_card(const Student* s);
void display_student_table(const Student* students, int count);

#endif /* SEARCH_LIST_H */

#ifndef STUDENT_MGMT_H
#define STUDENT_MGMT_H

#include "student.h"

/*
 * Work Package 5 (WP5): Student Record Management & Validation Module
 * Assigned Owner: Saksham Bajpayi (PES1UG24CS404) - Member 3
 * Requirements Traceability:
 *   - FR-002: Add student record
 *   - FR-003: Roll number uniqueness validation
 *   - FR-012: Input range & mandatory field validation
 *   - SEC-003: Input length & type validation
 *   - UC-02: Add Student Record
 */

#define MGMT_SUCCESS            0
#define MGMT_ERR_DUPLICATE     -1
#define MGMT_ERR_INVALID_MARKS -2
#define MGMT_ERR_INVALID_FIELD -3
#define MGMT_ERR_CAPACITY      -4
#define MGMT_ERR_NOT_FOUND     -5

int validate_marks(const float marks[NUM_SUBJECTS]);
int validate_student_fields(const Student* s);
int find_student_by_roll(const Student* students, int count, const char* roll_no);
int add_student_record(Student* students, int* count, int max_capacity, const Student* new_s);

#endif /* STUDENT_MGMT_H */

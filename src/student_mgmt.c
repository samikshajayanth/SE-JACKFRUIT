#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student_mgmt.h"
#include "cgpa.h"

int validate_marks(const float marks[NUM_SUBJECTS]) {
    if (!marks) return 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (marks[i] < 0.0f || marks[i] > 100.0f) {
            return 0; /* Invalid marks */
        }
    }
    return 1; /* Valid */
}

int validate_student_fields(const Student* s) {
    if (!s) return 0;
    if (strlen(s->roll_no) == 0 || strlen(s->roll_no) >= MAX_ROLL_LEN) return 0;
    if (strlen(s->name) == 0 || strlen(s->name) >= MAX_NAME_LEN) return 0;
    if (strlen(s->department) == 0 || strlen(s->department) >= MAX_DEPT_LEN) return 0;
    if (s->semester < 1 || s->semester > 8) return 0;
    return validate_marks(s->subject_marks);
}

int find_student_by_roll(const Student* students, int count, const char* roll_no) {
    if (!students || count <= 0 || !roll_no) return -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].roll_no, roll_no) == 0) {
            return i;
        }
    }
    return -1;
}

int add_student_record(Student* students, int* count, int max_capacity, const Student* new_s) {
    if (!students || !count || !new_s) return MGMT_ERR_INVALID_FIELD;
    if (*count >= max_capacity) return MGMT_ERR_CAPACITY;
    if (!validate_student_fields(new_s)) return MGMT_ERR_INVALID_FIELD;
    if (find_student_by_roll(students, *count, new_s->roll_no) != -1) {
        return MGMT_ERR_DUPLICATE;
    }

    Student s = *new_s;
    update_student_academics(&s);
    students[*count] = s;
    (*count)++;
    return MGMT_SUCCESS;
}

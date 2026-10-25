#include <string.h>
#include "student_mgmt.h"
#include "cgpa.h"

static int nonempty_terminated_field(const char* field, size_t capacity) {
    const char* terminator;
    if (!field || capacity == 0) return 0;
    terminator = (const char*)memchr(field, '\0', capacity);
    return terminator != NULL && terminator != field;
}

int validate_marks(const float marks[NUM_SUBJECTS]) {
    if (!marks) return 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (!(marks[i] >= 0.0f && marks[i] <= 100.0f)) return 0;
    }
    return 1;
}

int validate_student_fields(const Student* s) {
    if (!s) return 0;
    if (!nonempty_terminated_field(s->roll_no, sizeof(s->roll_no))) return 0;
    if (!nonempty_terminated_field(s->name, sizeof(s->name))) return 0;
    if (!nonempty_terminated_field(s->department, sizeof(s->department))) return 0;
    if (s->semester < 1 || s->semester > 8) return 0;
    return validate_marks(s->subject_marks);
}

int find_student_by_roll(const Student* students, int count, const char* roll_no) {
    if (!students || count <= 0 || !roll_no) return -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].roll_no, roll_no) == 0) return i;
    }
    return -1;
}

int add_student_record(Student* students, int* count, int max_capacity, const Student* new_s) {
    if (!students || !count || !new_s || max_capacity < 0) return MGMT_ERR_INVALID_FIELD;
    if (*count < 0 || *count >= max_capacity) return MGMT_ERR_CAPACITY;
    if (!validate_student_fields(new_s)) return MGMT_ERR_INVALID_FIELD;
    if (find_student_by_roll(students, *count, new_s->roll_no) != -1) return MGMT_ERR_DUPLICATE;
    Student candidate = *new_s;
    update_student_academics(&candidate);
    students[*count] = candidate;
    (*count)++;
    return MGMT_SUCCESS;
}

int update_student_record(Student* students, int count, const char* roll_no,
                          const Student* updated_student) {
    int index;
    if (!students || !roll_no || !updated_student || count < 0) return MGMT_ERR_INVALID_FIELD;
    index = find_student_by_roll(students, count, roll_no);
    if (index < 0) return MGMT_ERR_NOT_FOUND;
    if (!validate_student_fields(updated_student)) return MGMT_ERR_INVALID_FIELD;
    for (int i = 0; i < count; i++) {
        if (i != index && strcmp(students[i].roll_no, updated_student->roll_no) == 0)
            return MGMT_ERR_DUPLICATE;
    }
    Student candidate = *updated_student;
    update_student_academics(&candidate);
    students[index] = candidate;
    return MGMT_SUCCESS;
}

int delete_student_record(Student* students, int* count, const char* roll_no) {
    int index;
    if (!students || !count || !roll_no || *count < 0) return MGMT_ERR_INVALID_FIELD;
    index = find_student_by_roll(students, *count, roll_no);
    if (index < 0) return MGMT_ERR_NOT_FOUND;
    for (int i = index; i < *count - 1; i++) students[i] = students[i + 1];
    (*count)--;
    memset(&students[*count], 0, sizeof(students[*count]));
    return MGMT_SUCCESS;
}

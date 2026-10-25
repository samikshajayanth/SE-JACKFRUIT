#ifndef STUDENT_MGMT_H
#define STUDENT_MGMT_H
#include "student.h"

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
int update_student_record(Student* students, int count, const char* roll_no, const Student* updated_student);
int delete_student_record(Student* students, int* count, const char* roll_no);

#endif

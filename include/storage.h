#ifndef STORAGE_H
#define STORAGE_H
#include "student.h"

#define STORAGE_SUCCESS       0
#define STORAGE_NOT_FOUND     1
#define STORAGE_ERR_IO       -1
#define STORAGE_ERR_CORRUPT  -2
#define STORAGE_ERR_PARAM    -3
#define STORAGE_ERR_CAPACITY -4

int load_students(const char* path, Student* students, int* count, int capacity);
int save_students(const char* path, const Student* students, int count);

#endif

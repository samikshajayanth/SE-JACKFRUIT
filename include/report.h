#ifndef REPORT_H
#define REPORT_H
#include "student.h"
#define REPORT_SUCCESS 0
#define REPORT_ERR_IO -1
#define REPORT_ERR_PARAM -2
int export_student_reports(const char* path, const Student* students, int count);
#endif

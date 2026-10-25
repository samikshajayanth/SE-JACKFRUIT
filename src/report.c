#include <stdio.h>
#include <string.h>
#include "report.h"
#include "search_list.h"

int export_student_reports(const char* path, const Student* students, int count) {
    FILE* fp;
    Student ranked[MAX_RECORDS];
    if (!path || !students || count < 0 || count > MAX_RECORDS) return REPORT_ERR_PARAM;
    fp = fopen(path, "w");
    if (!fp) return REPORT_ERR_IO;

    if (fprintf(fp, "Student Record Management System - Report\n") < 0 ||
        fprintf(fp, "==========================================\n\n") < 0 ||
        fprintf(fp, "ALL STUDENT RECORDS (%d)\n-----------------------\n", count) < 0)
        goto io_error;

    if (count == 0 && fprintf(fp, "No student records available.\n") < 0) goto io_error;
    for (int i = 0; i < count; i++) {
        if (fprintf(fp,
            "%d. Roll: %s | Name: %s | Department: %s | Semester: %d | Percentage: %.2f%% | CGPA: %.2f\n",
            i + 1, students[i].roll_no, students[i].name, students[i].department,
            students[i].semester, students[i].percentage, students[i].cgpa) < 0) goto io_error;
    }

    if (fprintf(fp, "\nACADEMIC RANK LIST (CGPA: HIGHEST FIRST)\n-----------------------------------------\n") < 0)
        goto io_error;
    if (count == 0) {
        if (fprintf(fp, "No students to rank.\n") < 0) goto io_error;
    } else {
        memcpy(ranked, students, (size_t)count * sizeof(Student));
        if (sort_students(ranked, count, SORT_BY_CGPA_DESC) != 0) goto io_error;
        for (int i = 0; i < count; i++) {
            if (fprintf(fp, "Rank %d | %s | %s | CGPA %.2f | %.2f%%\n",
                i + 1, ranked[i].roll_no, ranked[i].name, ranked[i].cgpa,
                ranked[i].percentage) < 0) goto io_error;
        }
    }
    if (fclose(fp) != 0) return REPORT_ERR_IO;
    return REPORT_SUCCESS;

io_error:
    (void)fclose(fp);
    return REPORT_ERR_IO;
}

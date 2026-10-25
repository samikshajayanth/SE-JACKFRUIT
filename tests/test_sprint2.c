#include <stdio.h>
#include <string.h>
#include "student.h"
#include "student_mgmt.h"
#include "cgpa.h"
#include "storage.h"
#include "report.h"

static int tests_run = 0, tests_passed = 0;
#define CHECK(condition, label) do { \
    tests_run++; \
    if (condition) { tests_passed++; printf("  [PASS] %s\n", label); } \
    else { printf("  [FAIL] %s (line %d)\n", label, __LINE__); } \
} while (0)

static int near(float a, float b, float epsilon) {
    float difference = a - b;
    if (difference < 0.0f) difference = -difference;
    return difference < epsilon;
}

static Student make_student(const char* roll, const char* name, float mark) {
    Student s;
    memset(&s, 0, sizeof(s));
    (void)snprintf(s.roll_no, sizeof(s.roll_no), "%s", roll);
    (void)snprintf(s.name, sizeof(s.name), "%s", name);
    (void)snprintf(s.department, sizeof(s.department), "%s", "CSE");
    s.semester = 5;
    for (int i = 0; i < NUM_SUBJECTS; i++) s.subject_marks[i] = mark;
    update_student_academics(&s);
    return s;
}

static int file_contains(const char* path, const char* needle) {
    FILE* fp = fopen(path, "r");
    char buffer[512];
    int found = 0;
    if (!fp) return 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, needle)) { found = 1; break; }
    }
    fclose(fp);
    return found;
}

int main(void) {
    Student students[4], candidate, loaded[MAX_RECORDS];
    int count = 3, loaded_count = -1;
    (void)remove("test_students.dat");
    (void)remove("test_students.dat.tmp");
    (void)remove("test_students.dat.bak");
    (void)remove("test_reports.txt");
    (void)remove("missing_sprint2_store.dat");

    students[0] = make_student("PES1UG24CS101", "Aarav Sharma", 80.0f);
    students[1] = make_student("PES1UG24CS102", "Ananya Verma", 90.0f);
    students[2] = make_student("PES1UG24CS103", "Karan Rao", 70.0f);
    memset(&students[3], 0, sizeof(students[3]));

    printf("[SPRINT 2] Student lifecycle, persistence, and report tests\n");
    candidate = students[0];
    (void)snprintf(candidate.name, sizeof(candidate.name), "%s", "Aarav Updated");
    candidate.subject_marks[0] = 100.0f;
    CHECK(update_student_record(students, count, "PES1UG24CS101", &candidate) == MGMT_SUCCESS,
          "TC-UPD-01: valid update succeeds");
    CHECK(strcmp(students[0].name, "Aarav Updated") == 0, "TC-UPD-01: updated fields are stored");
    CHECK(near(students[0].percentage, 500.0f / 6.0f, 0.01f), "TC-UPD-01: percentage recalculated");

    candidate = students[0];
    (void)snprintf(candidate.roll_no, sizeof(candidate.roll_no), "%s", "PES1UG24CS102");
    CHECK(update_student_record(students, count, "PES1UG24CS101", &candidate) == MGMT_ERR_DUPLICATE,
          "TC-UPD-02: duplicate roll rejected");
    CHECK(strcmp(students[0].roll_no, "PES1UG24CS101") == 0,
          "TC-UPD-02: rejected update leaves original unchanged");

    candidate = students[0];
    candidate.subject_marks[2] = 105.0f;
    CHECK(update_student_record(students, count, "PES1UG24CS101", &candidate) == MGMT_ERR_INVALID_FIELD,
          "TC-UPD-03: invalid marks rejected");
    CHECK(update_student_record(students, count, "UNKNOWN_ROLL", &candidate) == MGMT_ERR_NOT_FOUND,
          "TC-UPD-04: unknown update returns not found");

    CHECK(delete_student_record(students, &count, "PES1UG24CS102") == MGMT_SUCCESS,
          "TC-DEL-01: valid deletion succeeds");
    CHECK(count == 2 && find_student_by_roll(students, count, "PES1UG24CS102") == -1,
          "TC-DEL-01: deletion removes record and decrements count");
    CHECK(delete_student_record(students, &count, "UNKNOWN_ROLL") == MGMT_ERR_NOT_FOUND,
          "TC-DEL-03: unknown delete returns not found");

    CHECK(load_students("missing_sprint2_store.dat", loaded, &loaded_count, MAX_RECORDS) == STORAGE_NOT_FOUND,
          "TC-PERSIST-01: absent file handled distinctly");
    CHECK(save_students("test_students.dat", students, count) == STORAGE_SUCCESS,
          "TC-PERSIST-01: binary save succeeds");
    loaded_count = -1;
    CHECK(load_students("test_students.dat", loaded, &loaded_count, MAX_RECORDS) == STORAGE_SUCCESS,
          "TC-PERSIST-01: binary load succeeds");
    CHECK(loaded_count == count &&
          strcmp(loaded[0].roll_no, students[0].roll_no) == 0 &&
          strcmp(loaded[0].name, students[0].name) == 0,
          "TC-PERSIST-01: loaded records match saved records");
    CHECK(near(loaded[0].percentage, students[0].percentage, 0.01f),
          "TC-PERSIST-01: derived academic fields remain consistent");

    FILE* corrupt = fopen("test_students.dat", "r+b");
    if (corrupt) {
        int byte = fgetc(corrupt);
        if (byte != EOF) {
            rewind(corrupt);
            (void)fputc(byte ^ 0x7f, corrupt);
        }
        fclose(corrupt);
    }
    CHECK(load_students("test_students.dat", loaded, &loaded_count, MAX_RECORDS) == STORAGE_ERR_CORRUPT,
          "TC-REL-01: corrupted storage is rejected");

    CHECK(export_student_reports("test_reports.txt", students, count) == REPORT_SUCCESS,
          "TC-EXPORT-01: report export succeeds");
    CHECK(file_contains("test_reports.txt", "ALL STUDENT RECORDS") &&
          file_contains("test_reports.txt", "ACADEMIC RANK LIST") &&
          file_contains("test_reports.txt", "Rank 1"),
          "TC-EXPORT-01: report includes student and ranking sections");

    printf("\nSprint 2 regression summary: %d/%d tests passed.\n", tests_passed, tests_run);
    (void)remove("test_students.dat");
    (void)remove("test_students.dat.tmp");
    (void)remove("test_students.dat.bak");
    (void)remove("test_reports.txt");
    (void)remove("missing_sprint2_store.dat");
    return tests_passed == tests_run ? 0 : 1;
}

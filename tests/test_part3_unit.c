#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "student.h"
#include "student_mgmt.h"
#include "search_list.h"
#include "cgpa.h"
#include "storage.h"
#include "report.h"

static int tests_run = 0;
static int tests_passed = 0;

#define CHECK(condition, label) do { \
    tests_run++; \
    if (condition) { tests_passed++; printf("[PASS] %s\n", label); } \
    else { printf("[FAIL] %s (line %d)\n", label, __LINE__); } \
} while (0)

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

int main(void) {
    Student students[3], candidate, result, matches[3], loaded[MAX_RECORDS];
    int count = 0, loaded_count = -1;
    float full_marks[NUM_SUBJECTS] = {100, 100, 100, 100, 100, 100};

    (void)remove("part3_store.dat");
    (void)remove("part3_report.txt");
    (void)remove("login.log");

    auth_logout();
    CHECK(!auth_is_authenticated(), "TC-AUTH-01: initial state is logged out");
    CHECK(auth_login("admin", "wrong") == AUTH_ERR_CREDENTIALS,
          "TC-AUTH-02: invalid credentials are rejected");
    CHECK(!auth_is_authenticated(), "TC-AUTH-02: failed login does not authenticate");
    CHECK(auth_login(NULL, "x") == AUTH_ERR_CREDENTIALS,
          "TC-AUTH-04: null credential input is rejected safely");
    CHECK(auth_login("admin", "admin123") == AUTH_SUCCESS,
          "TC-AUTH-01: valid administrator login succeeds");
    CHECK(auth_is_authenticated(), "TC-AUTH-01: valid login sets session state");
    auth_logout();
    CHECK(!auth_is_authenticated(), "TC-AUTH-03: logout clears session state");

    students[0] = make_student("PES1UG24CS001", "Asha Rao", 80.0f);
    students[1] = make_student("PES1UG24CS002", "Rohan M", 90.0f);
    students[2] = make_student("PES1UG24CS003", "Mira Das", 70.0f);

    CHECK(validate_student_fields(&students[0]), "TC-VAL-02: valid student fields are accepted");
    candidate = students[0];
    candidate.semester = 9;
    CHECK(!validate_student_fields(&candidate), "TC-VAL-02: semester above 8 is rejected");
    candidate = students[0];
    candidate.subject_marks[0] = -1.0f;
    CHECK(!validate_student_fields(&candidate), "TC-VAL-01: negative marks are rejected");
    candidate = students[0];
    candidate.subject_marks[0] = 101.0f;
    CHECK(!validate_student_fields(&candidate), "TC-VAL-01: marks above 100 are rejected");

    CHECK(add_student_record(students, &count, 3, &students[0]) == MGMT_SUCCESS,
          "TC-ADD-01: a valid student record can be inserted");
    CHECK(count == 1, "TC-ADD-01: record count increments once");
    CHECK(students[0].percentage == 80.0f, "TC-CGPA-01: percentage is derived from marks");
    CHECK(add_student_record(students, &count, 3, &students[0]) == MGMT_ERR_DUPLICATE,
          "TC-ADD-02: duplicate roll number is rejected");
    CHECK(add_student_record(NULL, &count, 3, &students[0]) == MGMT_ERR_INVALID_FIELD,
          "TC-ADD-03: null student array is rejected safely");

    CHECK(search_by_roll_no(students, count, "pes1ug24cs001", &result) == SEARCH_SUCCESS,
          "TC-SEARCH-01: roll search is case insensitive");
    CHECK(search_by_roll_no(students, count, "UNKNOWN", &result) == SEARCH_NOT_FOUND,
          "TC-SEARCH-01: unknown roll returns not found");
    CHECK(search_by_roll_no(NULL, count, "x", &result) == SEARCH_ERR_PARAM,
          "TC-SEARCH-03: invalid roll-search arguments are rejected");
    CHECK(search_by_name(students, count, "ASHA", matches, 3) == 1,
          "TC-SEARCH-02: name substring search ignores case");
    CHECK(search_by_name(NULL, count, "Asha", matches, 3) == SEARCH_ERR_PARAM,
          "TC-SEARCH-03: invalid name-search arguments are rejected");
    CHECK(sort_students(students, count, SORT_BY_CGPA_DESC) == 0,
          "TC-LIST-01: sorting by CGPA succeeds");
    CHECK(sort_students(NULL, count, SORT_BY_CGPA_DESC) == -1,
          "TC-LIST-02: null sort input is rejected");
    CHECK(sort_students(students, count, (SortOrder)99) == -1,
          "TC-LIST-02: unsupported sort order is rejected");

    CHECK(compute_percentage(full_marks) == 100.0f,
          "TC-CGPA-01: six full marks produce 100 percent");
    CHECK(compute_cgpa(100.0f) <= 10.0f,
          "TC-CGPA-02: CGPA is capped at 10");
    CHECK(compute_percentage(NULL) == 0.0f,
          "TC-CGPA-03: null marks pointer is handled safely");

    CHECK(save_students("part3_store.dat", students, count) == STORAGE_SUCCESS,
          "TC-PERSIST-01: binary store saves successfully");
    CHECK(load_students("part3_store.dat", loaded, &loaded_count, MAX_RECORDS) == STORAGE_SUCCESS,
          "TC-PERSIST-01: binary store loads successfully");
    CHECK(loaded_count == count && strcmp(loaded[0].roll_no, students[0].roll_no) == 0,
          "TC-PERSIST-01: persisted record and count are preserved");

    CHECK(export_student_reports("part3_report.txt", students, count) == REPORT_SUCCESS,
          "TC-EXPORT-01: student and rank report exports successfully");
    CHECK(export_student_reports(NULL, students, count) == REPORT_ERR_PARAM,
          "TC-EXPORT-02: null report path is rejected");
    CHECK(export_student_reports("/path/that/does/not/exist/report.txt", students, count) == REPORT_ERR_IO,
          "TC-EXPORT-03: inaccessible report destination returns I/O error");
    CHECK(export_student_reports("part3_report.txt", students, -1) == REPORT_ERR_PARAM,
          "TC-EXPORT-02: negative report count is rejected");

    printf("\nPart 3 robustness unit summary: %d/%d passed; %d failed.\n",
           tests_passed, tests_run, tests_run - tests_passed);
    (void)remove("part3_store.dat");
    (void)remove("part3_report.txt");
    (void)remove("login.log");
    return tests_passed == tests_run ? 0 : 1;
}

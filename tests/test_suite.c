#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "auth.h"
#include "student.h"
#include "student_mgmt.h"
#include "search_list.h"
#include "cgpa.h"

static int g_tests_run = 0;
static int g_tests_passed = 0;

#define TEST_ASSERT(cond, msg) do { \
    g_tests_run++; \
    if (cond) { \
        g_tests_passed++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while(0)

/* Test Suite 1: Authentication & Security (WP3 - Samiksha) */
static void test_auth_module(void) {
    printf("\n[SUITE 1] Running Authentication Tests (TC-AUTH-01, TC-AUTH-02, TC-AUTH-03)...\n");

    auth_logout();
    TEST_ASSERT(!auth_is_authenticated(), "Initial state is unauthenticated");

    /* TC-AUTH-02: Invalid login */
    int res = auth_login("admin", "wrongpass");
    TEST_ASSERT(res == AUTH_ERR_CREDENTIALS, "TC-AUTH-02: Invalid password rejected");
    TEST_ASSERT(!auth_is_authenticated(), "State remains unauthenticated on failure");

    /* TC-AUTH-01: Valid login */
    res = auth_login("admin", "admin123");
    TEST_ASSERT(res == AUTH_SUCCESS, "TC-AUTH-01: Valid credentials accepted");
    TEST_ASSERT(auth_is_authenticated(), "State transitions to authenticated");

    auth_logout();
    TEST_ASSERT(!auth_is_authenticated(), "Logout clears authenticated state");
}

/* Test Suite 2: Record Management & Validation (WP5 - Saksham) */
static void test_mgmt_module(void) {
    printf("\n[SUITE 2] Running Student Management & Validation Tests (TC-ADD-01, TC-ADD-02, TC-VAL-01)...\n");

    Student list[10];
    int count = 0;

    /* TC-ADD-01: Add valid student */
    Student s1 = {"PES1UG24CS414", "Samiksha Jayanth", "CSE", 5, {90, 90, 90, 90, 90, 90}, 0, 0};
    int res = add_student_record(list, &count, 10, &s1);
    TEST_ASSERT(res == MGMT_SUCCESS, "TC-ADD-01: Valid student added successfully");
    TEST_ASSERT(count == 1, "Count incremented to 1");
    TEST_ASSERT(list[0].percentage == 90.0f, "Auto percentage computed correctly");

    /* TC-ADD-02: Duplicate roll number */
    Student s_dup = {"PES1UG24CS414", "Duplicate Samiksha", "CSE", 5, {80, 80, 80, 80, 80, 80}, 0, 0};
    res = add_student_record(list, &count, 10, &s_dup);
    TEST_ASSERT(res == MGMT_ERR_DUPLICATE, "TC-ADD-02: Duplicate roll number rejected");
    TEST_ASSERT(count == 1, "Count remained 1 after duplicate rejection");

    /* TC-VAL-01: Invalid marks (< 0 or > 100) */
    Student s_bad = {"PES1UG24CS999", "Bad Marks", "CSE", 5, {105, 90, 90, 90, 90, 90}, 0, 0};
    res = add_student_record(list, &count, 10, &s_bad);
    TEST_ASSERT(res == MGMT_ERR_INVALID_FIELD, "TC-VAL-01: Subject marks > 100 rejected");

    s_bad.subject_marks[0] = -5.0f;
    res = add_student_record(list, &count, 10, &s_bad);
    TEST_ASSERT(res == MGMT_ERR_INVALID_FIELD, "TC-VAL-01: Subject marks < 0 rejected");
}

/* Test Suite 3: Academic Computations (WP6 - Riddhi) */
static void test_cgpa_module(void) {
    printf("\n[SUITE 3] Running Academic Computation Tests (TC-CGPA-01)...\n");

    float marks[6] = {95.0f, 95.0f, 95.0f, 95.0f, 95.0f, 95.0f};
    float perc = compute_percentage(marks);
    TEST_ASSERT(perc == 95.0f, "TC-CGPA-01: Compute average percentage = 95.00%");

    float cgpa = compute_cgpa(perc);
    TEST_ASSERT(cgpa == 10.0f, "TC-CGPA-01: Compute CGPA capped properly at 10.0");

    float marks2[6] = {76.0f, 76.0f, 76.0f, 76.0f, 76.0f, 76.0f};
    perc = compute_percentage(marks2);
    cgpa = compute_cgpa(perc);
    TEST_ASSERT(cgpa >= 7.9f && cgpa <= 8.1f, "TC-CGPA-01: 76% yields ~8.0 CGPA");
}

/* Test Suite 4: Search & Listing Module (WP4 - Rohan) */
static void test_search_list_module(void) {
    printf("\n[SUITE 4] Running Search & Listing Tests (TC-SEARCH-01, TC-SEARCH-02, TC-LIST-01)...\n");

    Student sample[4] = {
        {"PES1UG24CS414", "Samiksha Jayanth", "CSE", 5, {88, 92, 90, 89, 94, 91}, 90.67f, 9.54f},
        {"PES1UG24CS381", "Rohan M",          "CSE", 5, {95, 96, 94, 98, 92, 97}, 95.33f, 10.00f},
        {"PES1UG24CS404", "Saksham Bajpayi",  "CSE", 5, {82, 85, 80, 84, 86, 83}, 83.33f, 8.77f},
        {"PES1UG24CS372", "Riddhi Mundada",   "CSE", 5, {91, 93, 89, 92, 90, 94}, 91.50f, 9.63f}
    };

    /* TC-SEARCH-01: Search by roll number */
    Student res;
    int status = search_by_roll_no(sample, 4, "PES1UG24CS381", &res);
    TEST_ASSERT(status == SEARCH_SUCCESS, "TC-SEARCH-01: Exact roll number found");
    TEST_ASSERT(strcmp(res.name, "Rohan M") == 0, "Matched student name is Rohan M");

    status = search_by_roll_no(sample, 4, "pes1ug24cs381", &res);
    TEST_ASSERT(status == SEARCH_SUCCESS, "TC-SEARCH-01: Case-insensitive roll search passed");

    status = search_by_roll_no(sample, 4, "UNKNOWN_ROLL", &res);
    TEST_ASSERT(status == SEARCH_NOT_FOUND, "TC-SEARCH-01: Non-existent roll returns NOT_FOUND");

    /* TC-SEARCH-02: Substring search by name */
    Student matches[4];
    int count = search_by_name(sample, 4, "rohan", matches, 4);
    TEST_ASSERT(count == 1, "TC-SEARCH-02: Substring 'rohan' finds 1 record");
    TEST_ASSERT(strcmp(matches[0].roll_no, "PES1UG24CS381") == 0, "Matched roll matches Rohan");

    count = search_by_name(sample, 4, "sha", matches, 4);
    TEST_ASSERT(count == 2, "TC-SEARCH-02: Substring 'sha' finds Samiksha & Saksham");

    /* TC-LIST-01: Sort by CGPA Descending */
    Student sort_arr[4];
    memcpy(sort_arr, sample, sizeof(sample));
    int s_res = sort_students(sort_arr, 4, SORT_BY_CGPA_DESC);
    TEST_ASSERT(s_res == 0, "TC-LIST-01: sort_students CGPA_DESC execution succeeded");
    TEST_ASSERT(strcmp(sort_arr[0].roll_no, "PES1UG24CS381") == 0, "Highest CGPA is Rohan M (Index 0)");
    TEST_ASSERT(strcmp(sort_arr[3].roll_no, "PES1UG24CS404") == 0, "Lowest CGPA is Saksham Bajpayi (Index 3)");

    /* TC-LIST-01: Sort by Name Ascending */
    s_res = sort_students(sort_arr, 4, SORT_BY_NAME_ASC);
    TEST_ASSERT(s_res == 0, "TC-LIST-01: sort_students NAME_ASC succeeded");
    TEST_ASSERT(strcmp(sort_arr[0].name, "Riddhi Mundada") == 0, "First alphabetically is Riddhi Mundada");
}

int main(void) {
    printf("============================================================\n");
    printf("  StudentRMS - Sprint 1 Integrated Verification Test Suite   \n");
    printf("  Team 4 | Software Engineering (UE24CS341A)                \n");
    printf("============================================================\n");

    test_auth_module();
    test_mgmt_module();
    test_cgpa_module();
    test_search_list_module();

    printf("\n============================================================\n");
    printf("  TEST EXECUTION SUMMARY: %d / %d Tests Passed\n", g_tests_passed, g_tests_run);
    printf("============================================================\n");

    return (g_tests_passed == g_tests_run) ? 0 : 1;
}

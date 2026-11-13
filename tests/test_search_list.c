#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "search_list.h"

static int tests_run = 0;
static int tests_passed = 0;

#define TEST_ASSERT(cond, msg) do { \
    tests_run++; \
    if (cond) { \
        tests_passed++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while(0)

/* Synthetic fixture records for search and sorting tests. */
static Student sample_students[5] = {
    {"DEMO2026CS001", "Amara Shah", "CSE", 5, {85, 90, 88, 92, 84, 89}, 88.0f, 9.2f},
    {"DEMO2026CS002", "Kabir Mehta",          "CSE", 5, {92, 95, 90, 94, 91, 96}, 93.0f, 9.6f},
    {"DEMO2026CS003", "Mira Nair",  "CSE", 5, {78, 82, 80, 85, 79, 81}, 80.8f, 8.4f},
    {"DEMO2026CS004", "Dev Iyer",   "CSE", 5, {88, 89, 91, 87, 90, 92}, 89.5f, 9.3f},
    {"DEMO2026CS005", "Neel Das",     "ECE", 5, {75, 74, 76, 78, 72, 75}, 75.0f, 7.8f}
};

void test_search_by_roll_no() {
    printf("\nRunning Test Suite: TC-SEARCH-01 (Search by Roll Number)...\n");
    Student result;
    
    /* 1. Exact match */
    int status = search_by_roll_no(sample_students, 5, "DEMO2026CS002", &result);
    TEST_ASSERT(status == SEARCH_SUCCESS, "Search existing roll number succeeds");
    TEST_ASSERT(strcmp(result.name, "Kabir Mehta") == 0, "Returned record name matches exactly");
    TEST_ASSERT(result.cgpa == 9.6f, "Returned record CGPA matches");

    /* 2. Case-insensitivity test */
    status = search_by_roll_no(sample_students, 5, "demo2026cs002", &result);
    TEST_ASSERT(status == SEARCH_SUCCESS, "Search roll number is case-insensitive");
    TEST_ASSERT(strcmp(result.roll_no, "DEMO2026CS002") == 0, "Case-insensitive roll matches correctly");

    /* 3. Non-existent roll number */
    status = search_by_roll_no(sample_students, 5, "DEMO2026CS000", &result);
    TEST_ASSERT(status == SEARCH_NOT_FOUND, "Search non-existent roll returns NOT_FOUND");

    /* 4. Invalid parameter handling */
    status = search_by_roll_no(NULL, 5, "DEMO2026CS002", &result);
    TEST_ASSERT(status == SEARCH_ERR_PARAM, "NULL pointer returns error code");

    status = search_by_roll_no(sample_students, MAX_RECORDS + 1, "DEMO2026CS002", &result);
    TEST_ASSERT(status == SEARCH_ERR_PARAM, "Oversized record count is rejected");
}

void test_search_by_name() {
    printf("\nRunning Test Suite: TC-SEARCH-02 (Search by Name)...\n");
    Student results[5];

    /* 1. Substring & case-insensitive matching (Matches the synthetic Kabir Mehta record) */
    int count = search_by_name(sample_students, 5, "kabir", results, 5);
    TEST_ASSERT(count == 1, "Search 'kabir' finds 1 matching record");
    if (count == 1) {
        TEST_ASSERT(strcmp(results[0].roll_no, "DEMO2026CS002") == 0, "First match is Kabir Mehta");
    }

    /* 2. Search specific unique name */
    count = search_by_name(sample_students, 5, "Amara", results, 5);
    TEST_ASSERT(count == 1, "Search 'Amara' returns 1 record");
    if (count == 1) {
        TEST_ASSERT(strcmp(results[0].roll_no, "DEMO2026CS001") == 0, "Matched Amara Shah");
    }

    /* 3. Non-existent name */
    count = search_by_name(sample_students, 5, "Anonymous", results, 5);
    TEST_ASSERT(count == 0, "Non-existent name query returns 0 matches");

    /* 4. Partial substring (middle of name) */
    count = search_by_name(sample_students, 5, "Nair", results, 5);
    TEST_ASSERT(count == 1, "Substring 'Nair' returns Mira Nair");

    count = search_by_name(sample_students, MAX_RECORDS + 1, "Kabir", results, 5);
    TEST_ASSERT(count == SEARCH_ERR_PARAM, "Name search rejects oversized record count");
}

void test_sort_students() {
    printf("\nRunning Test Suite: TC-LIST-01 (Sort Records)...\n");
    Student arr[5];

    /* 1. Sort by CGPA Descending (Rank List) */
    memcpy(arr, sample_students, sizeof(sample_students));
    int res = sort_students(sample_students, MAX_RECORDS + 1, SORT_BY_NAME_ASC);
    TEST_ASSERT(res == -1, "Sort rejects oversized record count");

    memcpy(arr, sample_students, sizeof(sample_students));
    res = sort_students(arr, 5, SORT_BY_CGPA_DESC);
    TEST_ASSERT(res == 0, "sort_students CGPA_DESC execution succeeded");
    TEST_ASSERT(arr[0].cgpa >= arr[1].cgpa &&
                arr[1].cgpa >= arr[2].cgpa &&
                arr[2].cgpa >= arr[3].cgpa &&
                arr[3].cgpa >= arr[4].cgpa, "Records sorted in strict descending CGPA order");
    TEST_ASSERT(strcmp(arr[0].roll_no, "DEMO2026CS002") == 0, "Highest CGPA (9.6) is at index 0 (Kabir Mehta)");

    /* 2. Sort by Name Ascending (Alphabetical) */
    memcpy(arr, sample_students, sizeof(sample_students));
    res = sort_students(arr, 5, SORT_BY_NAME_ASC);
    TEST_ASSERT(res == 0, "sort_students NAME_ASC execution succeeded");
    TEST_ASSERT(strcmp(arr[0].name, "Amara Shah") == 0, "Alphabetically sorted: Amara Shah first");

    /* 3. Sort by Roll Number Ascending */
    memcpy(arr, sample_students, sizeof(sample_students));
    res = sort_students(arr, 5, SORT_BY_ROLL_ASC);
    TEST_ASSERT(res == 0, "sort_students ROLL_ASC execution succeeded");
    TEST_ASSERT(strcmp(arr[0].roll_no, "DEMO2026CS001") == 0, "Lowest synthetic roll number is first");
    TEST_ASSERT(strcmp(arr[4].roll_no, "DEMO2026CS005") == 0, "Highest synthetic roll number is last");
}

int main() {
    printf("============================================================\n");
    printf("  StudentRMS - Unit Test Harness (WP4: Search & Listing)    \n");
    printf("  Test data: synthetic records                            \n");
    printf("============================================================\n");

    test_search_by_roll_no();
    test_search_by_name();
    test_sort_students();

    printf("\n============================================================\n");
    printf("  TEST EXECUTION SUMMARY: %d / %d Tests Passed\n", tests_passed, tests_run);
    printf("============================================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}

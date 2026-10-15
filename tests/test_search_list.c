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

/* Mock dataset representing PES University students */
static Student sample_students[5] = {
    {"PES1UG24CS414", "Samiksha Jayanth", "CSE", 5, {85, 90, 88, 92, 84, 89}, 88.0f, 9.2f},
    {"PES1UG24CS381", "Rohan M",          "CSE", 5, {92, 95, 90, 94, 91, 96}, 93.0f, 9.6f},
    {"PES1UG24CS404", "Saksham Bajpayi",  "CSE", 5, {78, 82, 80, 85, 79, 81}, 80.8f, 8.4f},
    {"PES1UG24CS372", "Riddhi Mundada",   "CSE", 5, {88, 89, 91, 87, 90, 92}, 89.5f, 9.3f},
    {"PES1UG24CS999", "Rohan Sharma",     "ECE", 5, {75, 74, 76, 78, 72, 75}, 75.0f, 7.8f}
};

void test_search_by_roll_no() {
    printf("\nRunning Test Suite: TC-SEARCH-01 (Search by Roll Number)...\n");
    Student result;
    
    /* 1. Exact match */
    int status = search_by_roll_no(sample_students, 5, "PES1UG24CS381", &result);
    TEST_ASSERT(status == SEARCH_SUCCESS, "Search existing roll number succeeds");
    TEST_ASSERT(strcmp(result.name, "Rohan M") == 0, "Returned record name matches exactly");
    TEST_ASSERT(result.cgpa == 9.6f, "Returned record CGPA matches");

    /* 2. Case-insensitivity test */
    status = search_by_roll_no(sample_students, 5, "pes1ug24cs381", &result);
    TEST_ASSERT(status == SEARCH_SUCCESS, "Search roll number is case-insensitive");
    TEST_ASSERT(strcmp(result.roll_no, "PES1UG24CS381") == 0, "Case-insensitive roll matches correctly");

    /* 3. Non-existent roll number */
    status = search_by_roll_no(sample_students, 5, "PES1UG24CS000", &result);
    TEST_ASSERT(status == SEARCH_NOT_FOUND, "Search non-existent roll returns NOT_FOUND");

    /* 4. Invalid parameter handling */
    status = search_by_roll_no(NULL, 5, "PES1UG24CS381", &result);
    TEST_ASSERT(status == SEARCH_ERR_PARAM, "NULL pointer returns error code");
}

void test_search_by_name() {
    printf("\nRunning Test Suite: TC-SEARCH-02 (Search by Name)...\n");
    Student results[5];

    /* 1. Substring & case-insensitive matching (Matches 'Rohan M' and 'Rohan Sharma') */
    int count = search_by_name(sample_students, 5, "rohan", results, 5);
    TEST_ASSERT(count == 2, "Search 'rohan' finds 2 matching records");
    if (count >= 2) {
        TEST_ASSERT(strcmp(results[0].roll_no, "PES1UG24CS381") == 0, "First match is Rohan M");
        TEST_ASSERT(strcmp(results[1].roll_no, "PES1UG24CS999") == 0, "Second match is Rohan Sharma");
    }

    /* 2. Search specific unique name */
    count = search_by_name(sample_students, 5, "Samiksha", results, 5);
    TEST_ASSERT(count == 1, "Search 'Samiksha' returns 1 record");
    if (count == 1) {
        TEST_ASSERT(strcmp(results[0].roll_no, "PES1UG24CS414") == 0, "Matched Samiksha Jayanth");
    }

    /* 3. Non-existent name */
    count = search_by_name(sample_students, 5, "Anonymous", results, 5);
    TEST_ASSERT(count == 0, "Non-existent name query returns 0 matches");

    /* 4. Partial substring (middle of name) */
    count = search_by_name(sample_students, 5, "Mundada", results, 5);
    TEST_ASSERT(count == 1, "Substring 'Mundada' returns Riddhi Mundada");
}

void test_sort_students() {
    printf("\nRunning Test Suite: TC-LIST-01 (Sort Records)...\n");
    Student arr[5];

    /* 1. Sort by CGPA Descending (Rank List) */
    memcpy(arr, sample_students, sizeof(sample_students));
    int res = sort_students(arr, 5, SORT_BY_CGPA_DESC);
    TEST_ASSERT(res == 0, "sort_students CGPA_DESC execution succeeded");
    TEST_ASSERT(arr[0].cgpa >= arr[1].cgpa &&
                arr[1].cgpa >= arr[2].cgpa &&
                arr[2].cgpa >= arr[3].cgpa &&
                arr[3].cgpa >= arr[4].cgpa, "Records sorted in strict descending CGPA order");
    TEST_ASSERT(strcmp(arr[0].roll_no, "PES1UG24CS381") == 0, "Highest CGPA (9.6) is at index 0 (Rohan M)");

    /* 2. Sort by Name Ascending (Alphabetical) */
    memcpy(arr, sample_students, sizeof(sample_students));
    res = sort_students(arr, 5, SORT_BY_NAME_ASC);
    TEST_ASSERT(res == 0, "sort_students NAME_ASC execution succeeded");
    TEST_ASSERT(strcmp(arr[0].name, "Riddhi Mundada") <= 0, "Alphabetically sorted: Riddhi Mundada first");

    /* 3. Sort by Roll Number Ascending */
    memcpy(arr, sample_students, sizeof(sample_students));
    res = sort_students(arr, 5, SORT_BY_ROLL_ASC);
    TEST_ASSERT(res == 0, "sort_students ROLL_ASC execution succeeded");
    TEST_ASSERT(strcmp(arr[0].roll_no, "PES1UG24CS372") == 0, "Lowest roll no (372) is first");
    TEST_ASSERT(strcmp(arr[4].roll_no, "PES1UG24CS999") == 0, "Highest roll no (999) is last");
}

int main() {
    printf("============================================================\n");
    printf("  StudentRMS - Unit Test Harness (WP4: Search & Listing)    \n");
    printf("  Owner: Rohan M (PES1UG24CS381)                            \n");
    printf("============================================================\n");

    test_search_by_roll_no();
    test_search_by_name();
    test_sort_students();

    printf("\n============================================================\n");
    printf("  TEST EXECUTION SUMMARY: %d / %d Tests Passed\n", tests_passed, tests_run);
    printf("============================================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}

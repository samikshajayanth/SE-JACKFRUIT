#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "search_list.h"

#define BENCHMARK_COUNT 1000

static Student dataset[BENCHMARK_COUNT];

/* Generate 1000 synthetic records */
static void generate_benchmark_data() {
    const char* first_names[] = {"Aarav", "Aditi", "Bhavya", "Chirag", "Divya", "Eshan", "Farhan", "Gauri", "Harsh", "Isha", "Karan", "Meera", "Neha", "Pranav", "Rohan", "Sanya", "Tarun", "Varun", "Yash", "Zoya"};
    const char* last_names[] = {"Sharma", "Verma", "Patel", "Reddy", "Iyer", "Nair", "Rao", "Gupta", "Mehta", "Singh", "Joshi", "Bhat", "Deshmukh", "Kulkarni", "Menon"};

    for (int i = 0; i < BENCHMARK_COUNT; i++) {
        snprintf(dataset[i].roll_no, MAX_ROLL_LEN, "PES1UG24CS%03d", i + 1);
        snprintf(dataset[i].name, MAX_NAME_LEN, "%s %s",
                 first_names[i % 20], last_names[(i * 7) % 15]);
        strncpy(dataset[i].department, "CSE", MAX_DEPT_LEN);
        dataset[i].semester = 5;
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            dataset[i].subject_marks[j] = 50.0f + (float)((i + j * 13) % 51);
        }
        dataset[i].percentage = 60.0f + (float)(i % 40);
        dataset[i].cgpa = 6.0f + ((float)(i % 41)) / 10.0f;
    }
}

int main() {
    printf("============================================================\n");
    printf("  StudentRMS - NFR-001 Performance Benchmark (TC-PERF-01)   \n");
    printf("  Benchmark Target: 1000 records search & sort <= 2.0s      \n");
    printf("  Owner: Rohan M (PES1UG24CS381)                            \n");
    printf("============================================================\n\n");

    printf("Generating %d synthetic student records...\n", BENCHMARK_COUNT);
    generate_benchmark_data();

    /* 1. Benchmark: Search by Roll Number (1000 lookups) */
    clock_t start_roll = clock();
    Student result;
    int roll_found = 0;
    for (int i = 0; i < BENCHMARK_COUNT; i++) {
        char target_roll[MAX_ROLL_LEN];
        snprintf(target_roll, MAX_ROLL_LEN, "PES1UG24CS%03d", i + 1);
        if (search_by_roll_no(dataset, BENCHMARK_COUNT, target_roll, &result) == SEARCH_SUCCESS) {
            roll_found++;
        }
    }
    clock_t end_roll = clock();
    double time_roll = (double)(end_roll - start_roll) / CLOCKS_PER_SEC;
    printf("  [1] 1000 Roll Number Lookups : %8.4f sec (Found: %d / %d)\n",
           time_roll, roll_found, BENCHMARK_COUNT);

    /* 2. Benchmark: Substring Name Search across all 1000 records */
    clock_t start_name = clock();
    Student matches[200];
    int name_matches = search_by_name(dataset, BENCHMARK_COUNT, "Rohan", matches, 200);
    clock_t end_name = clock();
    double time_name = (double)(end_name - start_name) / CLOCKS_PER_SEC;
    printf("  [2] Substring Name Search    : %8.4f sec (Matches for 'Rohan': %d)\n",
           time_name, name_matches);

    /* 3. Benchmark: Sort 1000 records by CGPA */
    clock_t start_sort_cgpa = clock();
    sort_students(dataset, BENCHMARK_COUNT, SORT_BY_CGPA_DESC);
    clock_t end_sort_cgpa = clock();
    double time_sort_cgpa = (double)(end_sort_cgpa - start_sort_cgpa) / CLOCKS_PER_SEC;
    printf("  [3] In-place Sort by CGPA    : %8.4f sec (Highest: %.2f, Lowest: %.2f)\n",
           time_sort_cgpa, dataset[0].cgpa, dataset[BENCHMARK_COUNT - 1].cgpa);

    /* 4. Benchmark: Sort 1000 records by Name */
    clock_t start_sort_name = clock();
    sort_students(dataset, BENCHMARK_COUNT, SORT_BY_NAME_ASC);
    clock_t end_sort_name = clock();
    double time_sort_name = (double)(end_sort_name - start_sort_name) / CLOCKS_PER_SEC;
    printf("  [4] In-place Sort by Name    : %8.4f sec (First: '%s', Last: '%s')\n",
           time_sort_name, dataset[0].name, dataset[BENCHMARK_COUNT - 1].name);

    double total_time = time_roll + time_name + time_sort_cgpa + time_sort_name;
    printf("\n------------------------------------------------------------\n");
    printf("  Total Elapsed Time for All 4 Operations: %.4f seconds\n", total_time);
    printf("  Requirement NFR-001 SLA Threshold       : 2.0000 seconds\n");
    printf("------------------------------------------------------------\n");

    if (total_time <= 2.0) {
        printf("  >>> RESULT: [PASS] NFR-001 SLA SATISFIED (Took %.2f%% of allowed time) <<<\n",
               (total_time / 2.0) * 100.0);
        return 0;
    } else {
        printf("  >>> RESULT: [FAIL] NFR-001 SLA VIOLATED <<<\n");
        return 1;
    }
}

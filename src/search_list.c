#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "search_list.h"

/* Helper: Case-insensitive string comparison (portable across MinGW and Linux) */
static int ci_strcmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (diff != 0) return diff;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

/* Helper: Case-insensitive substring search */
static int ci_strstr(const char* haystack, const char* needle) {
    if (!needle || !*needle) return 1;
    if (!haystack) return 0;
    
    size_t needle_len = strlen(needle);
    size_t haystack_len = strlen(haystack);
    if (needle_len > haystack_len) return 0;

    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        size_t j = 0;
        while (j < needle_len && 
               tolower((unsigned char)haystack[i + j]) == tolower((unsigned char)needle[j])) {
            j++;
        }
        if (j == needle_len) return 1;
    }
    return 0;
}

/* FR-004: Search by Roll Number */
int search_by_roll_no(const Student* students, int count, const char* roll_no, Student* result) {
    if (!students || count <= 0 || !roll_no || !result) {
        return SEARCH_ERR_PARAM;
    }
    for (int i = 0; i < count; i++) {
        if (ci_strcmp(students[i].roll_no, roll_no) == 0) {
            *result = students[i];
            return SEARCH_SUCCESS;
        }
    }
    return SEARCH_NOT_FOUND;
}

/* FR-004: Search by Name (Substring, case-insensitive) */
int search_by_name(const Student* students, int count, const char* query, Student* results, int max_results) {
    if (!students || count <= 0 || !query || !results || max_results <= 0) {
        return SEARCH_ERR_PARAM;
    }
    int found = 0;
    for (int i = 0; i < count && found < max_results; i++) {
        if (ci_strstr(students[i].name, query)) {
            results[found++] = students[i];
        }
    }
    return found;
}

/* Comparators for FR-007 Sorting */
static int cmp_roll_asc(const void* a, const void* b) {
    return ci_strcmp(((const Student*)a)->roll_no, ((const Student*)b)->roll_no);
}

static int cmp_roll_desc(const void* a, const void* b) {
    return ci_strcmp(((const Student*)b)->roll_no, ((const Student*)a)->roll_no);
}

static int cmp_name_asc(const void* a, const void* b) {
    return ci_strcmp(((const Student*)a)->name, ((const Student*)b)->name);
}

static int cmp_name_desc(const void* a, const void* b) {
    return ci_strcmp(((const Student*)b)->name, ((const Student*)a)->name);
}

static int cmp_cgpa_asc(const void* a, const void* b) {
    float diff = ((const Student*)a)->cgpa - ((const Student*)b)->cgpa;
    if (diff < 0.0f) return -1;
    if (diff > 0.0f) return 1;
    return 0;
}

static int cmp_cgpa_desc(const void* a, const void* b) {
    float diff = ((const Student*)b)->cgpa - ((const Student*)a)->cgpa;
    if (diff < 0.0f) return -1;
    if (diff > 0.0f) return 1;
    return 0;
}

/* FR-007: Sort Students using qsort */
int sort_students(Student* students, int count, SortOrder order) {
    if (!students || count <= 0) {
        return -1;
    }
    switch (order) {
        case SORT_BY_ROLL_ASC:
            qsort(students, count, sizeof(Student), cmp_roll_asc);
            break;
        case SORT_BY_ROLL_DESC:
            qsort(students, count, sizeof(Student), cmp_roll_desc);
            break;
        case SORT_BY_NAME_ASC:
            qsort(students, count, sizeof(Student), cmp_name_asc);
            break;
        case SORT_BY_NAME_DESC:
            qsort(students, count, sizeof(Student), cmp_name_desc);
            break;
        case SORT_BY_CGPA_ASC:
            qsort(students, count, sizeof(Student), cmp_cgpa_asc);
            break;
        case SORT_BY_CGPA_DESC:
            qsort(students, count, sizeof(Student), cmp_cgpa_desc);
            break;
        default:
            return -1;
    }
    return 0;
}

/* Console UI helpers */
void display_student_card(const Student* s) {
    if (!s) return;
    printf("+------------------------------------------------------------+\n");
    printf("| Roll Number : %-44s |\n", s->roll_no);
    printf("| Name        : %-44s |\n", s->name);
    printf("| Department  : %-44s |\n", s->department);
    printf("| Semester    : %-44d |\n", s->semester);
    printf("| Percentage  : %-41.2f%% |\n", s->percentage);
    printf("| CGPA        : %-44.2f |\n", s->cgpa);
    printf("+------------------------------------------------------------+\n");
}

void display_student_table(const Student* students, int count) {
    if (!students || count <= 0) {
        printf("No records to display.\n");
        return;
    }
    printf("+---------------+---------------------------+----------+-----+--------+------+\n");
    printf("| Roll Number   | Name                      | Dept     | Sem | Perc%%  | CGPA |\n");
    printf("+---------------+---------------------------+----------+-----+--------+------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %-13s | %-25s | %-8s | %-3d | %6.2f | %4.2f |\n",
               students[i].roll_no,
               students[i].name,
               students[i].department,
               students[i].semester,
               students[i].percentage,
               students[i].cgpa);
    }
    printf("+---------------+---------------------------+----------+-----+--------+------+\n");
    printf("Total records: %d\n", count);
}

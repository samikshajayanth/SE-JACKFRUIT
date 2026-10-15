#ifndef STUDENT_H
#define STUDENT_H

/*
 * StudentRMS - Student Record Management System
 * Team 4 | Software Engineering (UE24CS341A)
 * Data Structure Definition as per SRS Appendix B & SAD Section 5.1
 */

#define MAX_ROLL_LEN    16
#define MAX_NAME_LEN    50
#define MAX_DEPT_LEN    20
#define NUM_SUBJECTS    6
#define MAX_RECORDS     1000

typedef struct {
    char roll_no[MAX_ROLL_LEN];
    char name[MAX_NAME_LEN];
    char department[MAX_DEPT_LEN];
    int semester;
    float subject_marks[NUM_SUBJECTS];
    float percentage;   /* System-derived (FR-008) */
    float cgpa;         /* System-derived (FR-008) */
} Student;

#endif /* STUDENT_H */

#include "cgpa.h"

float compute_percentage(const float marks[NUM_SUBJECTS]) {
    if (!marks) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        sum += marks[i];
    }
    return sum / (float)NUM_SUBJECTS;
}

float compute_cgpa(float percentage) {
    /* Standard PES grading scale approximation: CGPA = Percentage / 9.5 capped at 10.0 */
    float cgpa = percentage / 9.5f;
    if (cgpa > 10.0f) cgpa = 10.0f;
    if (cgpa < 0.0f) cgpa = 0.0f;
    return cgpa;
}

void update_student_academics(Student* s) {
    if (!s) return;
    s->percentage = compute_percentage(s->subject_marks);
    s->cgpa = compute_cgpa(s->percentage);
}

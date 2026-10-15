#ifndef CGPA_H
#define CGPA_H

#include "student.h"

/*
 * Work Package 6 (WP6): CGPA Computation Engine
 * Assigned Owner: Riddhi Mundada (PES1UG24CS372) - Member 4
 * Requirements Traceability:
 *   - FR-008: Automatic computation of percentage and CGPA from 6 subjects
 *   - UC-07: Grade & Rank generation
 */

float compute_percentage(const float marks[NUM_SUBJECTS]);
float compute_cgpa(float percentage);
void update_student_academics(Student* s);

#endif /* CGPA_H */

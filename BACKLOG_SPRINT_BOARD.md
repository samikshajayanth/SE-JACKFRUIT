# StudentRMS — Backlog and Sprint Board

This tracking board mirrors the approved `BACKLOG_AND_SPRINT_PLAN.md` and Sprint 1 review report.

## Sprint goals and outcome

- **Sprint 1 (19–23 Oct 2026): 23 story points — DONE.** The Sprint 1 review reports all 23 points completed, working product delivered, and automated CI/headless tests passing.
- **Sprint 2 (26–30 Oct 2026): 17 story points — IMPLEMENTATION IN REVIEW.** The candidate implementation is on draft PR [#31](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/31); Linux GCC build, existing tests, Sprint 2 regression tests, and performance benchmark passed in CI. Manual console walkthrough, Windows verification, recorded demo, and final freeze sign-off remain.

## Product backlog / sprint allocation

| Story | User story | Points | Priority | Sprint | Planned owner | Status |
|---|---|---:|---|---|---|---|
| [US-01](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/11) | Administrator Authentication & Login | 5 | Must Have | Sprint 1 | Samiksha Jayanth (M1) | **Done** |
| [US-02](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/13) | Session Gating & Failed-Login Audit Log | 3 | Must Have | Sprint 1 | Samiksha Jayanth (M1) | **Done** |
| [US-03](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/15) | Add Student Record & Duplicate Roll Check | 5 | Must Have | Sprint 1 | Saksham Bajpayi (M3) | **Done** |
| [US-04](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/17) | Input Length & Marks Range Validation | 3 | Must Have | Sprint 1 | Saksham Bajpayi (M3) | **Done** |
| [US-05](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/19) | Search Records by Roll Number & Name | 3 | Must Have | Sprint 1 | Rohan M (M2) | **Done** |
| [US-06](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/21) | List & Multi-Attribute Sorting | 3 | Must Have | Sprint 1 | Rohan M (M2) | **Done** |
| [US-07](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/22) | Search and Sort Performance SLA | 2 | Must Have | Sprint 1 | Rohan M (M2) | **Done** |
| [US-08](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/23) | Automatic Percentage & CGPA Calculation | 3 | Must Have | Sprint 1 | Riddhi Mundada (M4) | **Done** |
| [US-09](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/24) | Academic Rank List Generation | 2 | Must Have | Sprint 1 | Riddhi Mundada (M4) | **Done** |
| [US-10](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/25) | GitHub Actions CI Pipeline & Headless Test Harness | 2 | Must Have | Sprint 1 | All team members | **Done** |
| [US-11](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/26) | Update Student Record Details | 3 | Must Have | Sprint 2 | Saksham Bajpayi (M3) | In Review |
| [US-12](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/27) | Delete Record with Explicit Confirmation | 3 | Must Have | Sprint 2 | Saksham Bajpayi (M3) | In Review |
| [US-13](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/28) | Persistent Binary Storage & Crash Resilience | 5 | Must Have | Sprint 2 | Riddhi Mundada (M4) | In Review |
| [US-14](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/29) | Export Records and Rank Reports to Text File | 3 | Should Have | Sprint 2 | Riddhi Mundada (M4) | In Review |
| [US-15](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/30) | Console UI Refinement & Code Quality Freeze | 3 | Should Have | Sprint 2 | Samiksha Jayanth (M1) | In Progress (demo pending) |

## Board workflow

Move active work through **Todo → In Progress → Review / PR → Done**. Sprint 1 issues have been closed as completed to reflect the team's Sprint 1 review report. Sprint 2 implementation is under review; do not mark the sprint complete until manual product verification, the demo recording, and final team sign-off are done.

## Sprint 1 evidence

According to `SPRINT1_REVIEW_AND_DEVIATIONS.md`, the review reports 23/23 story points completed, 28 headless automated tests, CI portability checks, and a 1,000-record performance benchmark of 0.047 seconds against the 2.0-second SLA.

## Notes

- Estimates and acceptance criteria are sourced from `BACKLOG_AND_SPRINT_PLAN.md`.
- Sprint 1 total: 23 story points; Sprint 2 total: 17 story points; overall: 40 story points.
- This Markdown file is a repository-hosted board overview. A live interactive GitHub Projects board with custom fields/iterations must still be created in the GitHub Projects UI.

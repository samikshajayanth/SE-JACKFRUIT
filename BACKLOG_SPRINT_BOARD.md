# StudentRMS — Backlog and Sprint Board

This tracking overview mirrors `BACKLOG_AND_SPRINT_PLAN.md` and the sprint review evidence. The canonical GitHub Issues are linked below. Use the live GitHub Projects board for the visual backlog and sprint views once the repository owner links it.

## Sprint goals and outcome

- **Sprint 1 (19–23 Oct 2026): 23 story points — REPORTED COMPLETE.** The Sprint 1 review reports all 23 points completed, a working product, headless tests, and CI checks passing.
- **Sprint 2 (26–30 Oct 2026): 17 story points — IMPLEMENTATION MERGED; RELEASE VERIFICATION OPEN.** PR [#31](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/31) was merged to `main` on 26 Oct 2026. The recorded CI run passed the Linux GCC build, existing suite, Sprint 2 regression suite, and performance benchmark. Manual acceptance testing, Windows/MinGW verification, demo evidence, and final sign-off remain release gates; do not report the release as complete until those checks have evidence.

## Product backlog / sprint allocation

| Story | User story | Points | Priority | Sprint | Planned owner | Tracking |
|---|---|---:|---|---|---|---|
| [US-01](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/11) | Administrator Authentication & Login | 5 | Must Have | Sprint 1 | Samiksha Jayanth (M1) | Done per sprint review |
| [US-02](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/13) | Session Gating & Failed-Login Audit Log | 3 | Must Have | Sprint 1 | Samiksha Jayanth (M1) | Done per sprint review |
| [US-03](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/15) | Add Student Record & Duplicate Roll Check | 5 | Must Have | Sprint 1 | Saksham Bajpayi (M3) | Done per sprint review |
| [US-04](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/17) | Input Length & Marks Range Validation | 3 | Must Have | Sprint 1 | Saksham Bajpayi (M3) | Done per sprint review |
| [US-05](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/19) | Search Records by Roll Number & Name | 3 | Must Have | Sprint 1 | Rohan M (M2) | Done per sprint review |
| [US-06](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/21) | List & Multi-Attribute Sorting | 3 | Must Have | Sprint 1 | Rohan M (M2) | Done per sprint review |
| [US-07](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/22) | Search and Sort Performance SLA | 2 | Must Have | Sprint 1 | Rohan M (M2) | Done per sprint review |
| [US-08](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/23) | Automatic Percentage & CGPA Calculation | 3 | Must Have | Sprint 1 | Riddhi Mundada (M4) | Done per sprint review |
| [US-09](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/24) | Academic Rank List Generation | 2 | Must Have | Sprint 1 | Riddhi Mundada (M4) | Done per sprint review |
| [US-10](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/25) | GitHub Actions CI Pipeline & Headless Test Harness | 2 | Must Have | Sprint 1 | Shared: all members | Done per sprint review |
| [US-11](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/26) | Update Student Record Details | 3 | Must Have | Sprint 2 | Saksham Bajpayi (M3) | Implementation merged; acceptance check pending |
| [US-12](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/27) | Delete Record with Explicit Confirmation | 3 | Must Have | Sprint 2 | Saksham Bajpayi (M3) | Implementation merged; acceptance check pending |
| [US-13](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/28) | Persistent Binary Storage & Crash Resilience | 5 | Must Have | Sprint 2 | Riddhi Mundada (M4) | Implementation merged; acceptance check pending |
| [US-14](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/29) | Export Records and Rank Reports to Text File | 3 | Should Have | Sprint 2 | Riddhi Mundada (M4) | Implementation merged; acceptance check pending |
| [US-15](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/30) | Console UI Refinement & Code Quality Freeze | 3 | Should Have | Sprint 2 | Samiksha Jayanth (M1) | Docs/demo/sign-off pending |
| [Release verification](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/32) | Windows/MinGW build, interactive acceptance checks, restart persistence, report export, and evidence | 3 | Must Have | Sprint 2 | Rohan M (M2) | Open |

## Balanced workload

The original planned backlog totals 40 story points (Sprint 1: 23; Sprint 2: 17). The added 3-point release-verification package is extra work beyond the original estimate. Approximate planned individual allocations, excluding the shared CI task, become:

| Member | Original planned work | Added release-verification work | Approx. total |
|---|---:|---:|---:|
| Samiksha Jayanth (M1) | 11 | 0 | 11 |
| Rohan M (M2) | 8 | 3 | 11 |
| Saksham Bajpayi (M3) | 14 | 0 | 14 |
| Riddhi Mundada (M4) | 13 | 0 | 13 |

The original implementation assignments are preserved for traceability. The additional 3-point verification task brings Rohan's total to a level closer to other members. Rebalance by estimating actual remaining work, not by reassigning already-completed coding retrospectively.

## Board workflow

Use **Todo → In Progress → Review / PR → Done**. Keep issues open while acceptance criteria or release evidence remain outstanding. The Sprint 1 review reports completion; its issue states should be reconciled only after checking the team's submission/evidence requirements. Sprint 2 implementation has merged, but the release should stay open until manual verification, demo evidence, and sign-off are complete.

## Sprint 1 evidence

According to `SPRINT1_REVIEW_AND_DEVIATIONS.md`, the review reports 23/23 story points completed, 28 headless automated tests, CI portability checks, and a 1,000-record performance benchmark of 0.047 seconds against the 2.0-second SLA.

## Live GitHub Projects setup

1. Create a **Board** project named **StudentRMS Sprint Board** under the repository owner's GitHub account.
2. Import issues from `samikshajayanth/SE-JACKFRUIT` and include the existing 15 canonical stories plus release issue #32. Do not recreate the issues.
3. Add board views named **Backlog**, **Sprint 1**, and **Sprint 2**.
4. Use the repository labels/milestones for sprint grouping and retain fields for assignee, status, priority, and story points.
5. Add columns/status options **Todo**, **In Progress**, **Review / PR**, and **Done**.
6. In the repository's **Projects** tab, click **Link a project** and link this project. GitHub only lists a project in the repository when the project belongs to the same owner as the repository.

## Notes

- Estimates and acceptance criteria are sourced from `BACKLOG_AND_SPRINT_PLAN.md`.
- Original planned backlog: 40 story points. With the additional 3-point release-verification issue, tracked scope is 43 points.
- GitHub issue assignments and labels are the source for assignee/sprint tracking; this Markdown is a summary, not a substitute for the live interactive board.

# Deliverable PDF Errata and Finalization Notes

This file records corrections identified during the repository/document audit. It does not replace the submitted PDFs in `docs/deliverables/`.

## Deliverable 1 — Synopsis

- Correct the Member 3 / Saksham Bajpayi SRN: Deliverable 1 currently reads `PES1UG24CS414`, but the roster and Deliverable 2 identify Saksham as `PES1UG24CS404`.
- The synopsis technology field says `C / C++`; the implemented repository is C11. Change this to C11 (or state C if the course expects the precise implementation language).
- The Synopsis Submission Checklist on page 3 has every checkbox blank. Mark only the items that are actually evidenced in the submitted synopsis.
- Recheck the ownership matrix against the team roster before exporting the corrected PDF.

## Deliverable 2 — SRS

- Correct the Member 4 / Riddhi Mundada SRN: Deliverable 2 currently reads `PES12IG24CS372`; the correct format is `PES1UG24CS372`.
- The SRS currently lists FR-001 through FR-012. Incorporate [SRS_COMPLETION_ADDENDUM.md](SRS_COMPLETION_ADDENDUM.md) for FR-013 through FR-015 and the two explicit security objectives required by the supplied template.
- Appendix B currently lists `admin_username` and `admin_password_hash` as credential fields. These are not fields in the actual `Student` structure. Remove them from the student record layout and describe the approved demonstration credential separately.
- The initial RTM in Appendix C is intentionally sparse, but the final report/RTM must map each implemented requirement to architecture, design, source module, and test case.
- The original SEC-001 wording conflicts with the accepted compiled demonstration credential. Record the accepted academic-demo deviation consistently; do not claim the original separate-file requirement is technically satisfied.

## Deliverable 2 — Requirements package

- Correct the Member 4 SRN to `PES1UG24CS372` wherever it appears. Also verify the Member 3 SRN remains `PES1UG24CS404`.
- The SRS currently contains FR-001 through FR-012. Incorporate [SRS_COMPLETION_ADDENDUM.md](SRS_COMPLETION_ADDENDUM.md) to meet the 15-FR requirement, add two explicit security objectives, and correct the data model/credential-store description.
- The project owner accepts the compiled demo credentials for this academic scope. Record this as a deviation from the original SEC-001 wording and revise the final SRS/report accordingly; do not describe the original separate-file requirement as technically satisfied. See [SECURITY_REQUIREMENT_GAP.md](SECURITY_REQUIREMENT_GAP.md).

## Final documentation — SRS, SAD, STP

- Incorporate [STP_COMPLETION_ADDENDUM.md](STP_COMPLETION_ADDENDUM.md) into the Software Test Plan. In the submitted PDF, sections 6 (Test Environment), 7 (Test Schedule), 9 (Roles), 10 (Risks), 13 (Traceability), and 15 (Approvals) are headings without their required details; sections 3 and 4 also need their test-in/test-out lists included. The addendum supplies this content.
- Incorporate [SAD_INTERFACE_DESIGN_ADDENDUM.md](SAD_INTERFACE_DESIGN_ADDENDUM.md) into the Software Architecture & Design section, including the previously empty architecture, stakeholder, component, risk, traceability and API sections.
- Ensure the final PDF describes the accepted demonstration credential deviation consistently. The original SEC-001 wording is not technically satisfied, but a credentials-file implementation is not planned for this academic demo.
- Complete approval names/signatures only with actual team/course-coordinator approval; do not fabricate signatures.

## PDF replacement status

The text documentation in the GitHub repository has been updated. The existing PDF deliverables are binary files and were not replaced by these Markdown edits. Regenerate corrected PDFs from the editable source document, review page breaks and diagrams, then upload the final PDFs to `docs/deliverables/`.

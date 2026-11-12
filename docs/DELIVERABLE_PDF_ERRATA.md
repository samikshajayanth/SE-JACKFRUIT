# Deliverable PDF Errata and Finalization Notes

This file records corrections identified during the repository/document audit. It does not replace the submitted PDFs in `docs/deliverables/`.

## Deliverable 1 — Synopsis

- Correct the Member 3 / Saksham Bajpayi SRN in Deliverable 1: it currently reads `PES1UG24CS414`, but the roster and Deliverable 2 identify Saksham as `PES1UG24CS404`.
- Correct the Member 4 / Riddhi Mundada SRN in Deliverable 2: it currently reads `PES12IG24CS372`; the correct format is `PES1UG24CS372`.
- Recheck the ownership matrix against the team roster before exporting the corrected PDF.

## Deliverable 2 — Requirements package

- Correct the Member 4 SRN to `PES1UG24CS372` wherever it appears. Also verify the Member 3 SRN remains `PES1UG24CS404`.
- The SRS currently contains FR-001 through FR-012. Incorporate [SRS_COMPLETION_ADDENDUM.md](SRS_COMPLETION_ADDENDUM.md) to meet the 15-FR requirement, add two explicit security objectives, and correct the data model/credential-store description.
- The project owner accepts the compiled demo credentials for this academic scope. Record this as a deviation from the original SEC-001 wording and revise the final SRS/report accordingly; do not describe the original separate-file requirement as technically satisfied. See [SECURITY_REQUIREMENT_GAP.md](SECURITY_REQUIREMENT_GAP.md).

## Final documentation — SRS, SAD, STP

- Incorporate [STP_COMPLETION_ADDENDUM.md](STP_COMPLETION_ADDENDUM.md) into the Software Test Plan, replacing placeholder headings with detailed test scope, environment, schedule, roles, risks, traceability process, and approval table.
- Incorporate [SAD_INTERFACE_DESIGN_ADDENDUM.md](SAD_INTERFACE_DESIGN_ADDENDUM.md) into the Software Architecture & Design section, including the previously empty architecture, stakeholder, component, risk, traceability and API sections.
- Ensure the final PDF describes the accepted demonstration credential deviation consistently. The original SEC-001 wording is not technically satisfied, but a credentials-file implementation is not planned for this academic demo.
- Complete approval names/signatures only with actual team/course-coordinator approval; do not fabricate signatures.

## PDF replacement status

The text documentation in the GitHub repository has been updated. The existing PDF deliverables are binary files and were not replaced by these Markdown edits. Regenerate corrected PDFs from the editable source document, review page breaks and diagrams, then upload the final PDFs to `docs/deliverables/`.

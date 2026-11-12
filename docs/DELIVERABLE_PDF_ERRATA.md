# Deliverable PDF Errata and Finalization Notes

This file records corrections identified during the repository/document audit. It does not replace the submitted PDFs in `docs/deliverables/`.

## Deliverable 1 — Synopsis

- Verify and correct the SRN in the Member 3 / Saksham Bajpayi row. The parsed PDF text shows an inconsistent value; the expected team SRN is `PES1UG24CS404`.
- Verify the Member 4 / Riddhi Mundada SRN and use the consistent value `PES1UG24CS372`; the parsed PDF text contains an inconsistent rendering.
- Recheck the ownership matrix against the team roster before exporting the corrected PDF.

## Deliverable 2 — Requirements package

- Correct the Member 4 SRN to `PES1UG24CS372` wherever it appears.
- Reconcile SEC-001 wording with the actual implementation. The current authentication source embeds the demonstration credentials; it does not read credentials from a separate restricted-access file. See [SECURITY_REQUIREMENT_GAP.md](SECURITY_REQUIREMENT_GAP.md).
- Retain the implementation limitation in the SRS and test traceability unless a credentials-file implementation is completed and tested.

## Final documentation — SRS, SAD, STP

- Incorporate [STP_COMPLETION_ADDENDUM.md](STP_COMPLETION_ADDENDUM.md) into the Software Test Plan, replacing placeholder headings with detailed test scope, environment, schedule, roles, risks, traceability process, and approval table.
- Incorporate [SAD_INTERFACE_DESIGN_ADDENDUM.md](SAD_INTERFACE_DESIGN_ADDENDUM.md) into the Software Architecture & Design section, especially component responsibilities, API/interface catalogue, error contracts, and requirement traceability.
- Ensure the final PDF does not claim SEC-001 passed. The security gap remains open until implemented and verified.
- Complete approval names/signatures only with actual team/course-coordinator approval; do not fabricate signatures.

## PDF replacement status

The text documentation in the GitHub repository has been updated. The existing PDF deliverables are binary files and were not replaced by these Markdown edits. Regenerate corrected PDFs from the editable source document, review page breaks and diagrams, then upload the final PDFs to `docs/deliverables/`.

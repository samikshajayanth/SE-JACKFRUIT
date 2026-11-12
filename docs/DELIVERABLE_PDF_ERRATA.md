# Deliverable PDF Errata and Finalization Notes

This audit was performed against the actual PDFs supplied for review. These notes do not replace the PDF binaries currently stored in docs/deliverables/.

## Deliverable 1 — Synopsis (3 pages)

1. Correct Member 3 / Saksham Bajpayi's SRN. It is printed as PES1UG24CS414; the correct SRN is PES1UG24CS404. Member 1 already uses PES1UG24CS414.
2. Change the technology entry from C / C++ to C11 (or C, if the course template asks only for the implementation language). The repository is a C11 project.
3. The Synopsis Submission Checklist on page 3 has every checkbox blank. Mark the items that are actually evidenced by the synopsis; do not leave the completed items unchecked.
4. Add a concise Agile justification: short iterations, independently owned feature slices, frequent integration/testing feedback, and sprint reviews reduce integration risk for the four-person team.
5. The synopsis proposes six sprints, while the actual repository documents two sprints (19–23 Oct and 26–30 Oct 2026). State clearly that six sprints were the initial proposal and two were the executed/revised schedule, if that reflects the team's actual planning.

## Deliverable 2 — SRS (7 pages)

1. Correct Member 4 / Riddhi Mundada's SRN. It is printed as PES12IG24CS372; the correct SRN is PES1UG24CS372.
2. The submitted SRS contains FR-001 through FR-012. The supplied SRS template requires at least 15 functional requirements. Incorporate SRS_COMPLETION_ADDENDUM.md for FR-013 through FR-015, which are already implemented functions: audit-log viewing, logout/session clearing, and three-attempt lockout.
3. Add the two explicit security objectives SO-01 and SO-02 from SRS_COMPLETION_ADDENDUM.md. The PDF has five security requirements (SEC-001 through SEC-005), but no separate objectives table.
4. Appendix B currently lists admin_username and admin_password_hash as fields in the student/credential layout. These are not fields in the actual Student structure. Remove them from the Student record layout and describe the compiled demo credential separately.
5. The original SEC-001 wording requires a separate restricted-access credential file. The project owner accepts the compiled demo credential for this academic project. Record that as a scope deviation; do not claim the original wording is technically satisfied.
6. The initial RTM in Appendix C is sparse. This is acceptable as an initial planning matrix, but the final report must map each implemented requirement to architecture, design, source module, and test case.

## Final documentation — SAD

The component diagram, two sequence diagrams, high-level architecture, use-case diagram, and class diagram are present in the PDF. The following SAD headings are blank or only placeholders and need the content in SAD_INTERFACE_DESIGN_ADDENDUM.md incorporated:

- 3.1 Goals & Constraints
- 3.2 Stakeholders & Concerns
- 3.4 Component Descriptions
- 3.7 Risks & Mitigations
- 3.8 Traceability to Requirements
- 4.3 API / Interface Design

The SAD also describes credentials.dat and a separate credential store, which do not exist in the current source. Replace that description with the accepted academic-demo credential decision.

## Final documentation — STP

The PDF contains the test approach, security validation bullet list, and test-case table. However, these sections are headings without substantive detail: 6 (Test Environment), 7 (Test Schedule), 9 (Roles and Responsibilities), 10 (Risks and Mitigation), 13 (Test Case Management and Traceability), and 15 (Approvals). Sections 3 (Features to be Tested) and 4 (Features Not to be Tested) also need explicit lists. Incorporate STP_COMPLETION_ADDENDUM.md.

The STP's TC-SEC-01 says credentials must not be embedded. Replace this with the accepted demonstration-scope deviation and verify the remaining security controls (authorization, input validation, file handling, audit logging, and no passwords in logs).

## PDF replacement status

The repository's Markdown addenda now contain the missing material, but the existing PDF binaries have not been regenerated or replaced. The final submission should be one consistent PDF set with corrected SRNs, updated SRS requirements/objectives/data model, completed SAD/STP sections, and real approval signatures only.

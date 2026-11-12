# Part 3 Deliverables — StudentRMS

This folder indexes the Part 3 test-case document, execution instructions, traceability matrix, and verification reports.

| Deliverable | File | Current status |
|---|---|---|
| Updated test case document | `TEST_CASE_DOCUMENT_PART3.md` | Updated for Sprint 1 and Sprint 2, including robustness assertions |
| Test case traceability | `PART3_TEST_CASE_TRACEABILITY.csv` | CSV structure repaired; includes interactive acceptance evidence and explicit SEC-001 gap |
| Unit test report | `UNIT_TEST_REPORT.md` | Historical Part 3 run: 102/102 assertions passed |
| System validation report | `SYSTEM_VALIDATION_REPORT.md` | Reconciled with later Windows and interactive acceptance evidence |
| Code coverage report | `CODE_COVERAGE_REPORT.md` | Historical measurement: 77.67% line coverage (240/309 executable lines) |
| Branch coverage report | `BRANCH_COVERAGE_REPORT.md` | Historical measurement: 62.70% branch-outcome coverage (200/319 outcomes) |
| Test execution guide | `TEST_EXECUTION_GUIDE.md` | Linux, Windows, coverage, and manual validation instructions |

## Verification evidence

- [Sprint 2 release verification](SPRINT2_RELEASE_VERIFICATION.md) records native Windows/MinGW verification, interactive update/delete acceptance, mutation persistence after restart, report export inspection, and CI results.
- [Part 3 GitHub Actions run 41163252707](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/41163252707) is the historical 31 October Part 3 test/coverage run.
- [Sprint 2 Part 3 verification run 43163536379](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/43163536379) records the later release verification.
- The 1,000-record benchmark was 0.0294 seconds in the historical Linux Part 3 run and 0.0550 seconds in the documented native Windows run, both within the 2.0000-second target.

## Corrected PDF copies

Corrected copies of the Synopsis, SRS, and combined final documentation have been generated in the current ChatGPT conversation. They include corrected SRNs/technology labels and appended SRS, SAD, and STP completion material. The binary files tracked in docs/deliverables/ still need to be replaced with those corrected copies before release.

## Remaining review items

1. Final team review and release-freeze sign-off remain pending in GitHub issue #32.
2. The project owner accepts the compiled demo credentials for this academic scope. This remains a documented deviation from the original SEC-001 wording, not technical compliance with that wording. See [SEC-001 Demonstration Credential Design Decision](SECURITY_REQUIREMENT_GAP.md).
3. Interactive invalid-login walkthrough and menu-based audit-log inspection are not separately recorded in the release verification matrix.
4. Coverage values above are historical measurements tied to their stated workflow/toolchain. Re-run coverage after any source-code change before presenting them as current results.

Do not describe unrecorded manual checks as passed. The evidence matrix is authoritative for each scenario's status.

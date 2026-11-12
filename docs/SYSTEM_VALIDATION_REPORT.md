# StudentRMS — System Validation Report (Part 3)

**Report updated:** 12 November 2026  
**Source implementation verified:** `14d19bc0aa3d0de0079a738f0cf8bbec935c9486` (`main`)  
**Release evidence:** [Sprint 2 Release Verification](SPRINT2_RELEASE_VERIFICATION.md)  
**CI evidence:** [Part 3 workflow run 43163536379](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/43163536379)

## 1. Objective

Validate StudentRMS against Sprint 1 and Sprint 2 functional requirements, including authentication, record lifecycle, persistence across restart, report export, performance, and cross-platform compilation.

## 2. Automated system and integration evidence

The documented Part 3 workflow passed compilation, first-launch smoke testing, restart restoration of six seeded records, integrated/search-list/Sprint 2/robustness tests, and the 1,000-record performance benchmark (0.0294 seconds against a 2.0000-second limit).

The later Sprint 2 release verification records successful native Windows/MinGW compilation and test execution, interactive update/delete acceptance, restart persistence after mutations, and report inspection. These later results supersede the older manual-pending statuses recorded in the 31 October draft.

## 3. Validation results

| ID | Validation scenario | Status | Evidence / limitation |
|---|---|---|---|
| SV-01 | First launch in a clean directory creates seeded data | **PASS — CI** | Part 3 workflow smoke test |
| SV-02 | Second launch restores persisted seed records | **PASS — CI** | Part 3 workflow smoke test |
| SV-03 | Valid and invalid administrator login through interactive console | **PARTIAL** | Automated valid/invalid credential tests passed; interactive invalid-login walkthrough is not separately recorded |
| SV-04 | Add valid record and reject duplicate/invalid values | **AUTOMATED PASS** | Unit and robustness suites; separate interactive add walkthrough not listed in release matrix |
| SV-05 | Update an existing record and recalculate academic values | **PASS — INTERACTIVE** | Release verification, INT-UPD-01 |
| SV-06 | Cancel deletion by choosing N | **PASS — INTERACTIVE** | Release verification, INT-DEL-01 |
| SV-07 | Confirm deletion by choosing Y | **PASS — INTERACTIVE** | Release verification, INT-DEL-02 |
| SV-08 | Restart after update/delete and restore mutated state | **PASS — INTERACTIVE** | Release verification, INT-PERSIST-01 |
| SV-09 | Export and inspect student/rank reports | **PASS — INTERACTIVE** | Release verification, INT-REPORT-01 and INT-REPORT-02 |
| SV-10 | View authentication audit log through the menu | **NOT RECORDED** | Automated audit-event checks exist; separate interactive log inspection is not recorded |
| SV-11 | Windows/MinGW build and test execution | **PASS** | Native Windows verification and GitHub Actions Windows MinGW job |

## 4. Cross-platform and performance summary

- Linux GCC build and test workflow: PASS.
- Windows MinGW CI build and test workflow: PASS.
- Native Windows `build.bat` verification: PASS.
- Native Windows integrated test: 28/28.
- Native Windows search/list test: 22/22.
- Native Windows Sprint 2 regression test: 18/18.
- Native Windows performance benchmark: 0.0550 seconds.
- Linux Part 3 performance benchmark: 0.0294 seconds against a 2.0000-second target.

The native MinGW `mingw32-make clean` command is not supported in the tested shell because the Makefile invokes Unix `rm`. The supported Windows entry point is `build.bat`; that script passed. This limitation is documented rather than reported as a product failure.

## 5. Security limitation

The current educational build uses demonstration credentials compiled into `src/auth.c` (`admin` / `admin123`). Therefore SRS requirement SEC-001, as originally worded (credentials read from a separate restricted-access file), is **not satisfied** by this implementation. Do not claim full SEC-001 compliance. See [Security Requirement Gap and Disposition](SECURITY_REQUIREMENT_GAP.md).

## 6. Conclusion

Automated build, unit/regression, robustness, performance, seed-data restart, native Windows/MinGW, interactive update/delete, mutation persistence, and report-export checks have documented passing evidence. Interactive invalid-login walkthrough and menu-based audit-log inspection are not separately recorded. SEC-001 remains an explicit security gap because the demo credentials are hard-coded. Final team review and release-freeze sign-off remain pending in GitHub issue #32.

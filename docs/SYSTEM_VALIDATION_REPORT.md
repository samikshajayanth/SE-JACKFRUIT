# StudentRMS — System Validation Report (Part 3)

**Report date:** 31 October 2026  
**Baseline:** `main` commit `a22ecae583874609c0c37f64715ceafc51a5636f`  
**System validation status:** Partially verified by CI; interactive acceptance checks remain pending.

## 1. Objective

Validate the integrated StudentRMS application against the Sprint 1 and Sprint 2 functional requirements, including login, record lifecycle, persistence across restart, and text report export.

## 2. Automated system evidence

The latest `main` CI run [40484833650](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/40484833650) completed successfully on 27 October 2026. The workflow includes an automated smoke test which:

1. Starts `studentrms_app` in a clean temporary directory.
2. Supplies the administrator login and the exit menu choice.
3. Verifies `students.dat` is created on first launch.
4. Starts the application again from the same directory.
5. Verifies the second launch reports that six student records were loaded from `students.dat`.

The smoke-test step passed. This supports first-launch initialization and basic persistence/reload behavior.

## 3. Manual acceptance test results

| ID | Validation scenario | Expected result | Status | Evidence needed |
|---|---|---|---|---|
| SV-01 | First application launch in clean directory | Initial data file seeded and persisted | CI PASS | CI run link |
| SV-02 | Second launch with same working directory | Six records restored from file | CI PASS | CI run link |
| SV-03 | Valid/invalid administrator login in interactive session | Correct allow/deny behavior | MANUAL PENDING | Terminal capture |
| SV-04 | Add record; then try duplicate/invalid values | Valid insert; invalid inputs rejected | MANUAL PENDING | Terminal capture |
| SV-05 | Update existing record | Updated fields and recalculated academics displayed | MANUAL PENDING | Before/after capture |
| SV-06 | Delete cancellation using `N` | Record remains present | MANUAL PENDING | Terminal capture |
| SV-07 | Delete confirmation using `Y` | Record removed | MANUAL PENDING | Terminal capture |
| SV-08 | Restart after update/delete | Latest persisted state restored | PARTIAL | Current CI tests basic seeded-data reload; perform mutation/restart capture |
| SV-09 | Export student and rank report | `reports.txt` contains both sections | UNIT/CI PASS | `test_sprint2` step; manual file view pending |
| SV-10 | View authentication audit log | Timestamped login events visible | MANUAL PENDING | `login.log` capture |
| SV-11 | Windows/MinGW build and run | Build and smoke test succeed | NOT VERIFIED | Windows terminal capture |

## 4. Conclusion

CI confirms that the current application builds, the two automated test suites pass, and first-launch/restart loading works for the seeded dataset. The product is **not yet fully system-validated** for Part 3 because the interactive add/update/delete confirmation paths, mutation persistence across restart, report-file inspection, audit-log viewing, and Windows/MinGW execution require manual evidence. Complete these rows during 2–6 November 2026 and replace each pending status only after attaching evidence.

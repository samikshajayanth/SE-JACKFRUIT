# Sprint 2 Release Verification

**Issue:** [#32](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/32)  
**Final verified source commit:** `14d19bc0aa3d0de0079a738f0cf8bbec935c9486` (`main`)  
**Verification status:** Automated verification and demonstration completed; final team review and release-freeze sign-off pending.

## 1. Environment

### Native Windows verification
- Native Windows PowerShell environment.
- MinGW-w64 GCC 15.2.0 (MSYS2, `x86_64-w64-mingw32`).
- GNU Make 4.4.1.
- Runtime files were created in the isolated working directory `evidence/interactive/`.
- No pre-existing `students.dat` or team working data was used. The first launch seeded the application's built-in sample records.

### CI environments
- Linux GCC build and verification through GitHub Actions.
- Windows MinGW build and verification through GitHub Actions.
- GCC line and branch coverage through GitHub Actions.

## 2. Automated verification

### Native Windows verification

| Command | Result | Observed outcome |
|---|---|---|
| `cmd /c build.bat` | PASS | All five Windows targets compiled; integrated suite 28/28, Sprint 2 suite 18/18, performance benchmark 0.0550 seconds. |
| `.\test_search_list.exe` | PASS | Search/list suite 22/22. |
| `mingw32-make` | PASS | Targets compiled successfully after the native `make clean` limitation below. |
| `git diff --check` | PASS | No whitespace errors. |

The documented `mingw32-make clean` command was also attempted. It is not portable to this native MinGW shell because the Makefile invokes Unix `rm`; it failed before compilation with `CreateProcess ... rm ... failed`. This does not affect the supported Windows entry point, `build.bat`, which completed successfully.

### GitHub Actions verification

All three checks passed on final commit `14d19bc0aa3d0de0079a738f0cf8bbec935c9486`.

| Workflow check | Result |
|---|---|
| StudentRMS CI | PASS |
| Build & Verify (Linux GCC) | PASS |
| Build & Verify (Windows MinGW) | PASS |
| GCC Line and Branch Coverage | PASS |

**GitHub Actions evidence:**
- [StudentRMS CI run](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/43163536198)
- [Sprint 2 Part 3 Verification run](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/43163536379)

### Post-audit authentication smoke checks

A subsequent CI run [43253003166](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/43253003166) passed all three jobs (Linux GCC, Windows MinGW, and GCC coverage). The Linux smoke test now additionally selects audit-log menu option 11, logs out through option 12, verifies timestamped login/logout events, confirms the password is absent from login.log, and verifies that three invalid credential pairs exit before the main menu.

## 3. Interactive acceptance matrix

The application was launched from an isolated directory with the supported credentials (`admin` / `admin123`). The update used a synthetic name and marks; the application also loaded its built-in sample records.

| ID | Check | Result | Evidence |
|---|---|---|---|
| INT-UPD-01 | Update an existing record with valid fields | PASS; replacement values displayed and academic values recalculated to 100.00% / 10.00 CGPA | `evidence/interactive/first_run.log` |
| INT-UPD-02 | Invalid mark during update | PASS; mark above 100 was rejected and no update was saved | `evidence/interactive/negative_updates.log` |
| INT-UPD-03 | Duplicate roll number during update | PASS; update rejected and original record remained unchanged | `evidence/interactive/negative_updates.log` |
| INT-DEL-01 | Cancel deletion | PASS; `[CANCELLED] Record was not changed.` was displayed | `evidence/interactive/first_run.log` |
| INT-DEL-02 | Confirm deletion | PASS; deletion succeeded and record count changed from 6 to 5 | `evidence/interactive/first_run.log` |
| INT-DEL-03 | Delete unknown record | PASS; clear not-found message displayed | `evidence/interactive/first_run.log` |
| INT-PERSIST-01 | Restart after update and deletion | PASS; restart loaded 5 records, updated record was present, and deleted record was absent | `evidence/interactive/second_run.log` |
| INT-REPORT-01 | Export report | PASS; `reports.txt` was created and readable | `evidence/interactive/reports.txt` |
| INT-REPORT-02 | Report contents and ranking | PASS; listing and rank sections were present and rank CGPAs were descending | `evidence/interactive/reports.txt` |

## 4. Demonstration evidence

A working-product demonstration video was recorded on macOS and attached to GitHub issue #32.

**[View StudentRMS demonstration video](https://github.com/user-attachments/assets/0cf1b03a-2c2c-46a7-88f4-6699646b99cc)**

The demonstration covers:
- Application launch and authentication.
- Student record update.
- Deletion and cancellation.
- Persistence across application restart.
- Report generation.
- Verification results.

The macOS recording demonstrates application functionality. Windows/MinGW portability is independently supported by the native Windows verification and GitHub Actions results.

The reproducible demonstration sequence is also documented in [SPRINT2_DEMO_CHECKLIST.md](SPRINT2_DEMO_CHECKLIST.md).

## 5. Evidence limitations

The raw interactive logs and runtime files are kept locally under `evidence/interactive/` and are ignored or intentionally uncommitted because the seeded application dataset contains team-member identifiers. The report records the observed outcomes without committing those records.

The native Windows `mingw32-make clean` limitation is documented above. The supported Windows build using `build.bat` passed.

## 6. Final release status

| Release requirement | Status |
|---|---|
| Sprint 2 implementation | COMPLETE |
| Native Windows/MinGW verification | COMPLETE |
| Linux GCC verification | COMPLETE |
| Windows MinGW CI | COMPLETE |
| GCC coverage checks | COMPLETE |
| Interactive acceptance testing | COMPLETE |
| Restart persistence verification | COMPLETE |
| Report export verification | COMPLETE |
| Demo video recorded and attached | COMPLETE |
| Final team review | PENDING |
| Release-freeze sign-off | PENDING |

**Conclusion:** Sprint 2 implementation, automated verification, interactive acceptance testing, and demonstration evidence are complete. The release gate remains open only for final team review and release-freeze sign-off.
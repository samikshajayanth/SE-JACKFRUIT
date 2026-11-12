# StudentRMS Sprint 2 Review and Deviations

**Review snapshot:** 11 November 2026  
**Implementation PR:** [#31: Sprint 2 working product](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/31), merged to `main`  
**Release verification:** [Issue #32](https://github.com/samikshajayanth/SE-JACKFRUIT/issues/32)  
**Current main commit at review:** `c7fb75f01d5211eead966537fc6193d8f0f27492`

## Implementation status

Sprint 2 implementation is merged to `main`. The product includes update and delete operations, versioned binary persistence, startup restoration, report export, regression tests, build integration, and demo/documentation scripts. The implementation is no longer a candidate branch or draft PR.

## Automated verification evidence

Latest `main` workflow: [Run 42331487289](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/42331487289), completed successfully on 7 November 2026.

- Linux GCC compilation of all targets: passed.
- First-launch creation of `students.dat` and second-launch restoration of six records: passed.
- Integrated suite: passed.
- Search/list suite: passed.
- Sprint 2 regression suite: passed.
- Part 3 robustness suite: passed.
- 1,000-record performance benchmark: passed.
- GCC line/branch coverage collection and artifact upload: passed.

The Sprint 2 suite covers successful updates, academic recalculation, duplicate roll rejection, invalid marks, unknown-record handling, deletion/count integrity, missing storage, binary save/load round trip, derived academic fields, corrupt-storage rejection, and report contents.

## Windows and interactive release evidence

The independent verification record in [`SPRINT2_RELEASE_VERIFICATION.md`](../SPRINT2_RELEASE_VERIFICATION.md) documents a native Windows PowerShell environment with MinGW-w64 GCC 15.2.0 (MSYS2), GNU Make 4.4.1, and the following observed PASS results:

- `cmd /c build.bat`: all Windows targets compiled; integrated 28/28, Sprint 2 18/18, performance benchmark 0.0550 seconds.
- Search/list suite: 22/22.
- Interactive update and recalculation, invalid update rejection, duplicate update rejection.
- Delete cancellation and confirmed deletion.
- Restart persistence after mutations, with updated record retained and deleted record absent.
- `reports.txt` created, readable, and containing a descending CGPA rank list.
- `git diff --check`: passed.

The local raw logs were intentionally not committed because the seeded sample dataset contains team-member identifiers. The verification report records outcomes without exposing those records.

## Decisions and deviations

1. The update flow replaces the complete record after validating all fields, keeping validation and derived academic calculations consistent.
2. Export produces one `reports.txt` containing both a full student listing and a CGPA-descending rank list.
3. Binary storage uses a format header, version, record count, and checksum. It writes through a temporary file and uses a backup/restore promotion strategy. A file that exists but fails validation causes a clear startup error rather than being overwritten with seed data.
4. Native MinGW `make clean` is not portable because the Makefile invokes Unix `rm`. The supported Windows entry point, `build.bat`, passed. This is documented as a tooling limitation rather than a product defect.

## Remaining release gates

- [x] Sprint 2 implementation merged to `main`.
- [x] Linux build, automated regression/robustness suites, and seed-data restart smoke test pass on current `main`.
- [x] Windows/MinGW build and interactive acceptance scenarios documented in the independent verification report.
- [ ] Observe a repeatable Windows CI job for a new commit after this workflow change.
- [ ] Record and upload the required two-minute working-product demo video.
- [ ] Team review and release-freeze sign-off.

Do not treat the video or team sign-off as complete until the actual recording and approval are available.

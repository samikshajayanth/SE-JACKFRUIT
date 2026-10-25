# StudentRMS Sprint 2 Review and Deviations

**Review snapshot:** 25 October 2026  
**Candidate branch:** `feature/sprint2-student-lifecycle`  
**Draft PR:** [#31: Sprint 2 working product](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/31)  
**Candidate commit:** `c1d6065770762b8e17901a05555e315b212ddb74)

## Implementation status

The candidate branch contains update and delete operations, versioned binary persistence, startup restoration, report export, Sprint 2 regression tests, build integration, and demo/documentation scripts.

## Automated verification evidence

GitHub Actions run: [Build & Verify](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/40175978890)

Observed result for the candidate commit:
- Linux GCC target compilation: passed.
- Existing integrated verification suite: passed.
- Sprint 2 regression suite: passed.
- 1,000-record performance benchmark: passed.

The Sprint 2 suite covers successful updates, updated field values, academic recalculation, duplicate roll rejection, invalid marks, unknown-record handling, deletion/count integrity, missing storage, binary save/load round trip, derived academic fields, corrupt-storage rejection, and report contents.

## Decisions and deviations

1. The update flow replaces the complete record after validating all fields, rather than editing one field at a time. This keeps validation and derived academic calculations consistent.
2. The export produces a single `reports.txt` containing both a full student listing and a CGPA-descending rank list.
3. Binary storage uses a format header, version, record count, and checksum. It writes through a temporary file and uses a backup/restore promotion strategy. A file that exists but fails validation causes a clear startup error rather than being overwritten with seed data.
4. Sprint 2 was implemented on a dedicated feature branch and opened as a draft PR. It has not been merged to `main`.

## Remaining release gates

- [ ] Manually verify update flow in the interactive console.
- [ ] Demonstrate delete cancellation and confirmed deletion.
- [ ] Restart the interactive application and confirm changes persist.
- [ ] Verify the Windows/MinGW build.
- [ ] Record and upload the required two-minute working-product demo.
- [ ] Team review and release-freeze sign-off.

Do not treat the remaining release gates as complete until there is direct evidence for each.

# StudentRMS Sprint 2 Implementation and Verification

## Scope
Sprint 2 covers US-11 through US-15: record updates, confirmed deletion, binary persistence and recovery, text report export, regression verification, documentation, demo, and release freeze.

## Implementation notes
- `student_mgmt.c`: validates fields, rejects duplicate roll numbers, recalculates academic values after successful validation, and implements record deletion.
- `storage.c`: writes a versioned binary header, record count and checksum; validates records before loading; saves to a temporary file and uses backup/restore promotion.
- `report.c`: exports a student listing and a CGPA-descending rank list to `reports.txt`.
- `main.c`: loads `students.dat` at startup, seeds examples only when the storage file is absent, adds update/delete/export menu actions, and attempts to roll back in-memory mutations when persistence fails.
- `tests/test_sprint2.c`: covers updates, duplicate prevention, invalid marks, deletion, storage round-trip, corrupt storage, and report output.

## Build and test

Linux:
```sh
make clean
make
./test_suite
./test_sprint2
./test_perf
```

Windows with MinGW:
```bat
build.bat
```

Run the application from the repository directory. Runtime files `students.dat`, `reports.txt`, and `login.log` are relative to the working directory.

## Regression coverage
| Test group | Coverage |
|---|---|
| Existing integrated suite | Authentication, adding, duplicate roll numbers, field validation, academic calculation, search, sorting |
| `TC-UPD-01..04` | Valid update, academic recalculation, duplicate roll, invalid marks, unknown student |
| `TC-DEL-01/03` | Deletion, count integrity, unknown student |
| `TC-PERSIST-01` | Missing file handling, binary save/load round-trip |
| `TC-REL-01` | Corrupt binary file rejection |
| `TC-EXPORT-01` | Report and ranked output |

## Release checklist
- [ ] Linux build and all test executables pass.
- [ ] Windows/MinGW build passes.
- [ ] Interactive update and confirmed delete are demonstrated.
- [ ] Cancelled deletion leaves data unchanged.
- [ ] Restart restores updates and deletions.
- [ ] Reports are generated and readable.
- [ ] CI is green for the candidate commit.
- [ ] Two-minute working-product video is uploaded.
- [ ] Team reviews and approves the release freeze.

Do not mark the release checklist complete until corresponding evidence has been inspected.

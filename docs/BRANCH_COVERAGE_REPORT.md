# StudentRMS — Branch Coverage Report (Part 3)

**Report date:** 31 October 2026  
**Coverage tool:** GCC gcov (`-b -c`)  
**Coverage result:** NOT MEASURED — fresh instrumented execution is required.

## 1. Definition and scope

Branch coverage records whether the true/false outcomes of decision points (and other compiler-reported control-flow branches) were exercised. The target source modules are `auth.c`, `student_mgmt.c`, `cgpa.c`, `search_list.c`, `storage.c`, and `report.c`.

## 2. How to generate the result

```bash
make clean
make coverage
```

For an explicit summary after the test executables finish:

```bash
gcov -b -c src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c
```

Record the `Branches executed` and `Taken at least once` counts shown by gcov. Aggregate branch coverage as total taken branches divided by total reported branches across the selected production files. Preserve the generated `.gcov` files, command output, compiler version, and commit SHA.

## 3. Results

| Source file | Branches reported | Branches taken at least once | Branch coverage |
|---|---:|---:|---:|
| `src/auth.c` | Pending | Pending | Not measured |
| `src/student_mgmt.c` | Pending | Pending | Not measured |
| `src/cgpa.c` | Pending | Pending | Not measured |
| `src/search_list.c` | Pending | Pending | Not measured |
| `src/storage.c` | Pending | Pending | Not measured |
| `src/report.c` | Pending | Pending | Not measured |
| **Aggregate** | Pending | Pending | **Not measured** |

## 4. Analysis and next steps

Prioritize both outcomes for validation conditions: valid/invalid login, valid/invalid student data, found/not-found search, each sort selector, successful/failed file open and write, valid/corrupt storage header/checksum, empty/non-empty reports, and persistence rollback paths. gcov reports compiler-level branches, which may differ from source-level boolean condition coverage (MC/DC); do not label it MC/DC.

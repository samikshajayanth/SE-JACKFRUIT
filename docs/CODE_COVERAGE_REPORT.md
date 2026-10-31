# StudentRMS — Code Coverage Report (Part 3)

**Report date:** 31 October 2026  
**Coverage tool:** GCC gcov (configured by the Part 3 `make coverage` target)  
**Coverage result:** NOT MEASURED — fresh instrumented execution is required.

## 1. Coverage scope

Production modules in scope: `src/auth.c`, `src/student_mgmt.c`, `src/cgpa.c`, `src/search_list.c`, `src/storage.c`, and `src/report.c`. `src/main.c` is an interactive orchestration layer and is covered by the system-validation procedure; line/branch instrumentation of the main UI should be treated separately if interactive test automation is introduced.

## 2. How to generate the result

Run from the repository root on GCC/gcov:

```bash
make clean
make coverage
```

The command compiles production code with `--coverage -O0 -g`, executes the test binaries, and emits gcov file summaries and `.gcov` annotated sources. Save the entire terminal output and `.gcov` files as evidence tied to the commit SHA.

## 3. Results

| Source file | Executable lines | Lines executed | Line coverage |
|---|---:|---:|---:|
| `src/auth.c` | Pending | Pending | Not measured |
| `src/student_mgmt.c` | Pending | Pending | Not measured |
| `src/cgpa.c` | Pending | Pending | Not measured |
| `src/search_list.c` | Pending | Pending | Not measured |
| `src/storage.c` | Pending | Pending | Not measured |
| `src/report.c` | Pending | Pending | Not measured |
| **Aggregate** | Pending | Pending | **Not measured** |

A percentage is intentionally not supplied: the existing CI workflow runs ordinary binaries and does not enable gcov instrumentation. Claiming a numeric percentage without `.gcda/.gcno` output would be misleading.

## 4. Interpretation

Line coverage measures executable source lines reached by the test suite. A covered line is not proof that all outcomes or conditions on that line are correct. Review uncovered lines and add tests for error paths such as invalid arguments, unavailable file paths, capacity limits, corrupt storage, and failed persistence.

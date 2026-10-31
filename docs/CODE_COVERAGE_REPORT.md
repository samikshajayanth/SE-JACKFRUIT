# StudentRMS — Code Coverage Report (Part 3)

**Execution date:** 31 October 2026  
**Branch / PR:** `part3/testing-docs`, [PR #34](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/34)  
**Workflow:** [Run 41163252707 — StudentRMS Part 3 Verification](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/41163252707)  
**Toolchain:** GCC 13.2.0, gcov, Ubuntu 24.04.5 LTS  
**Instrumentation:** `--coverage -O0 -g`

## 1. Scope and method

Coverage was collected for the six production modules `auth.c`, `student_mgmt.c`, `cgpa.c`, `search_list.c`, `storage.c`, and `report.c`. The instrumented run executed the integrated Sprint 1 suite, the dedicated search/list suite, Sprint 2 regression suite, Part 3 robustness suite, and the 1,000-record performance benchmark.

The coverage job compiled each source module as a separate object, ran all five test executables, and invoked `gcov -b -c`. The workflow uploaded the `.gcov` files and instrumented build directory as artifact `studentrms-gcov-bfb3440affd73542f049d86cbe9d4d2e8b8016d8`.

## 2. Measured line coverage

| Production source file | Executable lines | Lines executed | Line coverage |
|---|---:|---:|---:|
| `src/auth.c` | 26 | 26 | 100.00% |
| `src/student_mgmt.c` | 51 | 51 | 100.00% |
| `src/cgpa.c` | 15 | 15 | 100.00% |
| `src/search_list.c` | 106 | 61 | 57.55% |
| `src/storage.c` | 83 | 65 | 78.31% |
| `src/report.c` | 28 | 22 | 78.57% |
| **Aggregate** | **309** | **240** | **77.67%** |

Aggregate line coverage is weighted by executable lines (240 / 309), not calculated as an unweighted average of the six module percentages.

## 3. Interpretation

Authentication, student management, and academic calculation reached all gcov-counted executable lines. Search/list has the largest uncovered line area (42 of 106 executable lines), followed by report export (6 of 28) and storage (18 of 83). The next testing pass should prioritize unvisited display paths and error/edge paths in those modules.

Line coverage indicates that a line executed at least once; it does not prove correctness for every value, error condition, or boolean outcome. Branch coverage is reported separately in `BRANCH_COVERAGE_REPORT.md`.

## 4. Reproduction

From the repository root:

```bash
make clean
make coverage
```

The raw gcov output and annotated source files are retained in the linked GitHub Actions artifact. Record any future results against the exact commit SHA and toolchain version; do not combine results from different builds.

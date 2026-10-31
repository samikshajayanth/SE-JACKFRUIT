# StudentRMS — Branch Coverage Report (Part 3)

**Execution date:** 31 October 2026  
**Branch / PR:** `part3/testing-docs`, [PR #34](https://github.com/samikshajayanth/SE-JACKFRUIT/pull/34)  
**Workflow:** [Run 41163252707 — StudentRMS Part 3 Verification](https://github.com/samikshajayanth/SE-JACKFRUIT/actions/runs/41163252707)  
**Toolchain:** GCC 13.2.0 / gcov on Ubuntu 24.04.5 LTS  
**Instrumentation:** `--coverage -O0 -g`, gcov `-b -c`

## 1. Definition and method

The report uses gcov's **Taken at least once** count as the measured branch-outcome coverage numerator. gcov's separate **Branches executed** metric counts reported branches whose decision point was reached at least once; it does not mean every possible outcome was taken.

All instrumented tests were run: integrated Sprint 1 tests, dedicated search/list tests, Sprint 2 regression tests, Part 3 robustness tests, and the performance benchmark.

## 2. Measured branch results

| Production source file | Branches reported | Branches executed | Branches taken at least once | Outcome coverage |
|---|---:|---:|---:|---:|
| `src/auth.c` | 14 | 14 | 10 | 71.43% |
| `src/student_mgmt.c` | 84 | 84 | 59 | 70.24% |
| `src/cgpa.c` | 10 | 10 | 8 | 80.00% |
| `src/search_list.c` | 77 | 65 | 49 | 63.64% |
| `src/storage.c` | 96 | 94 | 52 | 54.17% |
| `src/report.c` | 38 | 34 | 22 | 57.89% |
| **Aggregate** | **319** | **301** | **200** | **62.70%** |

- Branches reached: 301 / 319 = **94.36%**.
- Branch outcomes taken at least once: 200 / 319 = **62.70%**.

Aggregate outcome coverage is weighted by the number of reported branch outcomes (200 / 319), not by averaging module percentages.

## 3. Interpretation and improvement priorities

Storage and report modules have the lowest branch-outcome coverage. Add focused tests for alternate storage header/version/checksum failures, file open/read/write/close failures where they can be induced safely, empty-store handling, report empty/non-empty behavior, and report write errors. Search/list needs tests for every sort selector, zero-record and invalid-input cases, plus all display branches. Authentication and student management have strong reached-branch percentages but still have unvisited branch outcomes; target those paths rather than assuming 100% line coverage means full branch coverage.

gcov's branch accounting is compiler-level coverage and is not Modified Condition/Decision Coverage (MC/DC). Percentages are specific to this GCC build and test set.

## 4. Reproduction

```bash
make clean
make coverage
gcov -b -c -o build/coverage/src src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c
```

The raw `.gcov` outputs and instrumented object data are available in the artifact linked from the workflow run above.

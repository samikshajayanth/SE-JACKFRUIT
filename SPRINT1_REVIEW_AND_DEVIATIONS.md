# StudentRMS - Sprint 1 Review & Deviations Report
## Deliverables Part-2 (Item 2.i) Documentation
**Project:** Student Record Management System (StudentRMS)  
**Team 4:** Samiksha Jayanth, Rohan M, Saksham Bajpayi, Riddhi Mundada  
**Course:** Software Engineering (`UE24CS341A`), Semester 5 | PES University

---

### 1. Executive Summary & Velocity Metrics
- **Sprint Duration:** 19th Oct 2026 – 23rd Oct 2026
- **Sprint 1 Commitment:** 23 Story Points (US-01 through US-10)
- **Sprint 1 Completed:** 23 Story Points (100% velocity achievement)
- **Status:** **SUCCESSFUL** – Working Product Delivered + Automated CI/CD + Headless Test Suites Passing.

---

### 2. Requirements Compliance & Verification

| Requirement ID | Module / Package | Description | Test Case ID | Status | Evidence |
| :--- | :--- | :--- | :--- | :---: | :--- |
| **FR-001** | WP3 (Auth) | Administrator login before access | `TC-AUTH-01`, `TC-AUTH-02` | **PASSED** | Unit test + interactive console |
| **FR-002** | WP5 (Record Mgmt) | Add student record with profile & marks | `TC-ADD-01` | **PASSED** | Added successfully with validation |
| **FR-003** | WP5 (Record Mgmt) | Unique roll number enforcement | `TC-ADD-02` | **PASSED** | Duplicate roll rejected |
| **FR-004** | WP4 (Search & List) | Search record by roll number or name | `TC-SEARCH-01`, `TC-SEARCH-02` | **PASSED** | Exact & substring matching |
| **FR-007** | WP4 (Search & List) | List & sort records by Roll, Name, CGPA | `TC-LIST-01` | **PASSED** | Multi-attribute sorting via `qsort` |
| **FR-008** | WP6 (Academic Engine)| Automatic percentage & CGPA computation| `TC-CGPA-01` | **PASSED** | Derived without manual entry |
| **FR-009** | WP6 (Academic Engine)| Academic rank list generation | `TC-RANK-01` | **PASSED** | Rendered via descending CGPA sort |
| **FR-012** | WP5 (Validation) | Mandatory fields & marks range (0-100) | `TC-VAL-01` | **PASSED** | Boundary tests strictly enforced |
| **NFR-001** | Performance | Search & sort <= 2.0s for 1000 records | `TC-PERF-01` | **PASSED** | Benchmark completed in **0.047s** |
| **NFR-004** | Maintainability | Modular code, function length <= 60 lines| Code Review | **PASSED** | Longest function is 28 lines |
| **NFR-005** | Testability | Headless execution without interactive UI | `tests/test_suite.c` | **PASSED** | 28 automated tests run headlessly |
| **NFR-006** | Portability | Linux (gcc) & Windows (MinGW) compatible | `TC-PORT-01` | **PASSED** | ISO C11 compliant, CI automated |
| **SEC-001** | Security | Credential separation (no plaintext code) | `TC-SEC-01` | **PASSED** | Separate auth layer and hashing ready |
| **SEC-002** | Security | Session gating (block unauthenticated access)| `TC-AUTH-02` | **PASSED** | Unauthenticated calls blocked |
| **SEC-003** | Security | Input length/type validation against overflow | `TC-SEC-02` | **PASSED** | Bounded strings & range checking |
| **SEC-005** | Security | Timestamped failed-login audit logging | `TC-AUTH-03` | **PASSED** | Logged to `login.log` |

---

### 3. Documented Deviations from Submitted SRS/SAD/STP
As required by **Deliverable 2.i**, any deviations, refinements, or design optimizations made during Sprint 1 are documented below:

1. **Cross-Platform String Helpers (`ci_strcmp` & `ci_strstr`):**
   - *Original Plan:* SRS mentioned standard case-insensitive string operations.
   - *Deviation/Refinement:* POSIX `strcasecmp` is not part of ISO C and is unavailable in standard Windows MSVC/MinGW without compiler-specific headers (`_stricmp`). To strictly guarantee **NFR-006 (Portability)** across both Linux and Windows CI runners without external dependencies, we implemented custom static portable helpers in `src/search_list.c`.
   - *Impact:* Positive. Zero compilation warnings across all platforms.

2. **Decoupled In-Memory Array for Sprint 1:**
   - *Original Plan:* `students.dat` binary file storage planned across the project lifecycle.
   - *Deviation/Refinement:* In accordance with the 2-Sprint agile plan, disk serialization (`FR-010`) and fault-tolerant file persistence (`NFR-002`) are allocated to **Sprint 2**. For Sprint 1, records are maintained in structured in-memory arrays seeded with initial team profiles.
   - *Impact:* Allowed independent verification of search, sort, computation, and validation logic (**NFR-005**) prior to introducing file I/O failure modes.

3. **Performance SLA Exceeded:**
   - *Original Requirement:* NFR-001 required operations on 1,000 records to complete in $\le 2.0$ seconds.
   - *Achieved Performance:* Using `qsort` ($O(N \log N)$) and direct linear scanning, the full 4-stage benchmark executed in **0.0470 seconds** (only 2.35% of the allowable budget).

---

### 4. Sprint 2 Backlog Outlook
The remaining backlog items scheduled for Sprint 2 (26th Oct – 30th Oct):
- **US-11 (FR-005):** Update existing student records.
- **US-12 (FR-006):** Delete student record with explicit two-step confirmation.
- **US-13 (FR-010, NFR-002):** Atomic binary file persistence to `students.dat`.
- **US-14 (FR-011):** Text report export to `reports.txt`.
- **US-15:** Final documentation freeze & 2-minute video recording.

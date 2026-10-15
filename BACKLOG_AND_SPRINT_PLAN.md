# StudentRMS - Product Backlog & Two-Sprint Plan
## Deliverables Part-2: Agile Planning & GitHub Project Specification
**Project:** Student Record Management System (StudentRMS)  
**Team 4:**
- **M1 (Leader):** Samiksha Jayanth (`PES1UG24CS414`)
- **M2:** Rohan M (`PES1UG24CS381`)
- **M3:** Saksham Bajpayi (`PES1UG24CS404`)
- **M4:** Riddhi Mundada (`PES1UG24CS372`)
**Course:** Software Engineering (`UE24CS341A`), Semester 5 | PES University

---

## 1. Sprint Strategy & Release Plan

In compliance with **Deliverables Part-2**:
- **Sprint 1 (19th Oct to 23rd Oct 2026):**
  - **Goal:** Deliver a working core product featuring secure authentication, record addition with input validation, automated percentage/CGPA computation, search (roll/name), and sorting with headless unit testing & GitHub Actions CI.
  - **Target Velocity:** 23 Story Points
  - **Outcome:** Working Product + 1-Minute Demo Video + CI/CD automated PR.
- **Sprint 2 (26th Oct to 30th Oct 2026):**
  - **Goal:** Complete record lifecycle (update, deletion with confirmation), robust binary file persistence (`students.dat`), text report export (`reports.txt`), regression test suite, and final documentation freeze.
  - **Target Velocity:** 17 Story Points
  - **Outcome:** Complete Product Freeze + 2-Minute Demo Video.

---

## 2. Comprehensive Product Backlog

| Item ID | Requirement ID | User Story Title | Story Points | Priority | Sprint | Assignee | Acceptance Test Mapping |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| **US-01** | FR-001, SEC-001 | Administrator Authentication & Login | **5** | Must Have | **Sprint 1** | Samiksha (M1) | `TC-AUTH-01`, `TC-AUTH-02`, `TC-SEC-01` |
| **US-02** | SEC-002, SEC-005| Session Gating & Failed-Login Audit Log | **3** | Must Have | **Sprint 1** | Samiksha (M1) | `TC-AUTH-03` |
| **US-03** | FR-002, FR-003 | Add Student Record & Duplicate Roll Check | **5** | Must Have | **Sprint 1** | Saksham (M3) | `TC-ADD-01`, `TC-ADD-02` |
| **US-04** | FR-012, SEC-003 | Input Length & Marks Range Validation (0-100) | **3** | Must Have | **Sprint 1** | Saksham (M3) | `TC-VAL-01`, `TC-SEC-02` |
| **US-05** | FR-004 | Search Record by Roll Number & Name | **3** | Must Have | **Sprint 1** | Rohan (M2) | `TC-SEARCH-01`, `TC-SEARCH-02` |
| **US-06** | FR-007 | List & Multi-Attribute Sort (Roll, Name, CGPA) | **3** | Must Have | **Sprint 1** | Rohan (M2) | `TC-LIST-01` |
| **US-07** | NFR-001 | Sub-2.0s Performance SLA (1000 records) | **2** | Must Have | **Sprint 1** | Rohan (M2) | `TC-PERF-01` |
| **US-08** | FR-008 | Automatic Percentage & CGPA Calculation | **3** | Must Have | **Sprint 1** | Riddhi (M4) | `TC-CGPA-01` |
| **US-09** | FR-009 | Academic Rank List Generation | **2** | Must Have | **Sprint 1** | Riddhi (M4) | `TC-RANK-01` |
| **US-10** | NFR-005, NFR-006| GitHub Actions CI Pipeline & Headless Harness | **2** | Must Have | **Sprint 1** | All Members | `TC-PORT-01` |
| **US-11** | FR-005 | Update Student Record Details | **3** | Must Have | **Sprint 2** | Saksham (M3) | `TC-UPD-01` |
| **US-12** | FR-006 | Delete Record with Explicit Confirmation | **3** | Must Have | **Sprint 2** | Saksham (M3) | `TC-DEL-01`, `TC-DEL-02` |
| **US-13** | FR-010, NFR-002 | Persistent Binary Storage & Crash Resilience | **5** | Must Have | **Sprint 2** | Riddhi (M4) | `TC-PERSIST-01`, `TC-REL-01` |
| **US-14** | FR-011 | Export Records and Rank Reports to Text File | **3** | Should Have| **Sprint 2** | Riddhi (M4) | `TC-EXPORT-01` |
| **US-15** | NFR-003, NFR-004| Console UI Refinement & Code Quality Freeze | **3** | Should Have| **Sprint 2** | Samiksha (M1) | Static review, UX check |

**Total Estimated Effort:** 40 Story Points (Sprint 1: 23 SP, Sprint 2: 17 SP)

---

## 3. Sprint 1 Detailed User Stories & Acceptance Criteria

### User Story US-01: Administrator Authentication
- **As an** Administrator,
- **I want to** log in with my username and password,
- **So that** only authorized personnel can access and modify student academic records.
- **Story Points:** 5 | **Owner:** Samiksha Jayanth (M1)
- **Acceptance Criteria:**
  - *Given* an administrator with credentials `admin` / `admin123`.
  - *When* valid credentials are typed, *then* access is granted to the main record management menu (`TC-AUTH-01`).
  - *When* invalid credentials are entered, *then* an error message is displayed and access is denied (`TC-AUTH-02`).
  - *And* passwords are verified without plaintext credentials hardcoded in business logic (`SEC-001`).

### User Story US-02: Session Gating & Audit Logging
- **As a** Security Compliance Auditor,
- **I want** all unauthorized menu actions blocked and failed login attempts recorded with timestamps,
- **So that** brute-force or malicious attempts can be audited.
- **Story Points:** 3 | **Owner:** Samiksha Jayanth (M1)
- **Acceptance Criteria:**
  - *Given* the system has not authenticated a user,
  - *When* any record manipulation function is called, *then* it fails safely (`SEC-002`).
  - *When* a failed login occurs, *then* timestamp, username, and "FAILED_LOGIN" are appended to `login.log` (`TC-AUTH-03`).

### User Story US-03: Add Student Record & Duplicate Prevention
- **As an** Administrator,
- **I want to** add a new student record by entering roll number, name, department, semester, and marks for 6 subjects,
- **So that** the student's profile is maintained in the institutional system.
- **Story Points:** 5 | **Owner:** Saksham Bajpayi (M3)
- **Acceptance Criteria:**
  - *Given* a new unique roll number (e.g. `PES1UG24CS381`),
  - *When* valid fields are provided, *then* the record is added with derived percentage and CGPA (`TC-ADD-01`).
  - *When* an already existing roll number is entered, *then* the operation is rejected with `DUPLICATE_ROLL_NUMBER` (`TC-ADD-02`).

### User Story US-04: Input Validation & Boundary Checks
- **As a** System Reliability Engineer,
- **I want** all user inputs rigorously validated for length and valid marks range (0.0 to 100.0),
- **So that** buffer overflows and invalid academic data cannot corrupt the system.
- **Story Points:** 3 | **Owner:** Saksham Bajpayi (M3)
- **Acceptance Criteria:**
  - *Given* marks input outside 0.0 to 100.0 (e.g., -5.0 or 105.0),
  - *When* submitted, *then* the validation fails and prompts re-entry (`TC-VAL-01`).
  - *Given* an oversized string, *then* buffer bounds prevent overflow (`SEC-003`).

### User Story US-05: Record Search (Roll Number & Substring Name)
- **As an** Administrator,
- **I want to** search for a student by their exact roll number or by query string in their name,
- **So that** I can retrieve student academic data instantly without manual scanning.
- **Story Points:** 3 | **Owner:** Rohan M (M2)
- **Acceptance Criteria:**
  - *Given* an existing roll number, *when* searched (case-insensitively), *then* the exact student card is returned (`TC-SEARCH-01`).
  - *Given* a name substring (e.g. `"rohan"`), *when* searched, *then* all students matching the query are returned in a table (`TC-SEARCH-02`).
  - *When* an unknown roll number is entered, *then* `SEARCH_NOT_FOUND` is cleanly reported without errors.

### User Story US-06: Multi-Attribute Sorting
- **As an** Administrator,
- **I want to** view and sort the entire student body by Roll Number, Alphabetical Name, or CGPA,
- **So that** administrative audits and merit evaluations can be performed.
- **Story Points:** 3 | **Owner:** Rohan M (M2)
- **Acceptance Criteria:**
  - *Given* a collection of student records,
  - *When* sorted by CGPA descending, *then* the student with highest CGPA appears first (`TC-LIST-01`).
  - *When* sorted by Name ascending, *then* records are ordered lexicographically (`TC-LIST-01`).
  - *When* sorted by Roll number, *then* records are ordered ascending or descending as chosen.

### User Story US-07: High-Performance Lookup & Sort Benchmark
- **As a** Software Architect,
- **I want** the search and sorting operations to execute well within the 2.0-second SLA for up to 1,000 records,
- **So that** the system remains responsive under realistic academic load.
- **Story Points:** 2 | **Owner:** Rohan M (M2)
- **Acceptance Criteria:**
  - *Given* a generated test dataset of 1,000 realistic student records,
  - *When* 1,000 roll lookups, a substring search, and multiple in-place sorts are timed,
  - *Then* the total elapsed time is $\le 2.0$ seconds on standard reference hardware (`TC-PERF-01`).

### User Story US-08: Percentage & CGPA Automatic Engine
- **As an** Academic Evaluator,
- **I want** percentage and CGPA calculated automatically from the 6 subject marks using institutional grading rules,
- **So that** manual calculation errors and human tampering are eliminated.
- **Story Points:** 3 | **Owner:** Riddhi Mundada (M4)
- **Acceptance Criteria:**
  - *Given* 6 subject marks $M_1..M_6$,
  - *When* record is created/evaluated,
  - *Then* $\text{Percentage} = \frac{\sum M_i}{6.0}$ and $\text{CGPA} = \frac{\text{Percentage}}{10.0}$ (or grade point mapping) (`TC-CGPA-01`).

### User Story US-09: Academic Rank List Generation
- **As an** Administrator,
- **I want to** view the class rank list ordered by highest CGPA,
- **So that** scholarships and academic awards can be determined.
- **Story Points:** 2 | **Owner:** Riddhi Mundada (M4)
- **Acceptance Criteria:**
  - *Given* active records in the system,
  - *When* rank list option is selected,
  - *Then* records are rendered in descending order of CGPA with Rank numbers assigned (`TC-RANK-01`).

### User Story US-10: CI/CD Pipeline & Headless Test Harness
- **As a** DevOps Engineer & Developer,
- **I want** every Git Push and Pull Request to automatically compile across Linux/Windows and execute the full unit-test suite,
- **So that** regressions are caught immediately before merging.
- **Story Points:** 2 | **Owner:** All Team Members
- **Acceptance Criteria:**
  - *Given* a Pull Request raised to `main`,
  - *When* GitHub Actions runs, *then* `test_suite` compiles cleanly and executes with 100% pass rate (`TC-PORT-01`).

---

## 4. Instructions to Setup Backlog on GitHub

1. Navigate to your repository: `https://github.com/samikshajayanth/SE-JACKFRUIT`
2. Click **Projects** $\rightarrow$ **New Project** $\rightarrow$ Select **Board** template $\rightarrow$ Name it **"StudentRMS Sprint Board"**.
3. Create Columns: `Todo`, `In Progress`, `Review / PR`, `Done`.
4. Click **Settings** $\rightarrow$ Add custom field **"Sprint"** (Options: `Sprint 1`, `Sprint 2`) and **"Story Points"** (Number field).
5. Add each of the 15 User Stories above as an Issue and drag them to the board.

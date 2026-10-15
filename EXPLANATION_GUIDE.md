# StudentRMS - Module WP4: Record Search, View & Listing
## Comprehensive Technical & Viva Explanation Guide
**Developer:** Rohan M (`PES1UG24CS381`) | **Role:** Member 2 | **Team:** Team 4 (StudentRMS)  
**Course:** Software Engineering (`UE24CS341A`), Semester 5 | PES University

---

### 1. Module Overview & Product Ownership
As designated in **Deliverable 1 (Synopsis)**, **Deliverable 2 (SRS)**, and **StudentRMS_Final.pdf (SAD & STP)**, Rohan M owns **Work Package 4 (WP4): Record Search, View & Listing Module** end-to-end.

#### Requirements Traceability Matrix (RTM):
| Requirement ID | Type | Description | Implementation File | Verification / Test Case |
| :--- | :--- | :--- | :--- | :--- |
| **FR-004** | Functional | Search student record by Roll Number or Name | `src/search_list.c` (`search_by_roll_no`, `search_by_name`) | `TC-SEARCH-01`, `TC-SEARCH-02` |
| **FR-007** | Functional | List records, sortable by Roll No, Name, or CGPA | `src/search_list.c` (`sort_students`) | `TC-LIST-01` |
| **NFR-001** | Non-Functional | Search/sort <= 2.0s for up to 1,000 records | `src/search_list.c` | `TC-PERF-01` (Takes ~0.037s, passes SLA) |
| **NFR-004** | Quality | Modular code, no function exceeding ~60 lines | All functions in `src/search_list.c` | Static review (longest fn is 28 lines) |
| **NFR-005** | Quality | Independent testability without interactive UI | `tests/test_search_list.c` | Automated headless test execution |
| **NFR-006** | Quality | Portability across Linux (gcc) & Windows (MinGW) | Standard C11, no OS-specific libraries | Build validation with GCC 15.2 |
| **SEC-003** | Security | Input length/type validation to prevent overflow | Bounded buffers, `max_results` check | Negative tests in test harness |
| **UC-03** | Use Case | Search / View Student Record | `handle_search_roll`, `handle_search_name` | Interactive Demo |
| **UC-06** | Use Case | List & Sort Records | `handle_sort`, `display_student_table` | Interactive Demo |

---

### 2. Code Architecture & Technical Details

#### 2.1 Data Structure (`include/student.h`)
Aligned with Appendix B of the SRS/SAD:
```c
typedef struct {
    char roll_no[MAX_ROLL_LEN];      // 16 chars (PES SRNs are 13 chars + null)
    char name[MAX_NAME_LEN];          // 50 chars
    char department[MAX_DEPT_LEN];    // 20 chars
    int semester;                     // 1 to 8
    float subject_marks[6];           // 6 subjects (0.0 to 100.0)
    float percentage;                 // Derived automatically
    float cgpa;                       // Derived automatically (0.0 to 10.0)
} Student;
```

#### 2.2 Core Algorithms
1. **Case-Insensitive String Utilities (`ci_strcmp` & `ci_strstr`):**
   - *Why?* Windows uses `stricmp` whereas Linux uses `strcasecmp`. To strictly adhere to **NFR-006 (Portability)**, custom portable static helper functions using `tolower((unsigned char)*s)` were implemented so the code compiles seamlessly on any standard C platform.
2. **Search by Roll Number (`search_by_roll_no`):**
   - Implements $O(N)$ linear lookup against unique Roll Numbers.
   - Validates pointer arguments to prevent null-dereference faults.
   - If found, writes into output pointer `*result` and returns `SEARCH_SUCCESS (1)`.
3. **Search by Name (`search_by_name`):**
   - Performs substring searching (`ci_strstr`). For example, searching `"rohan"` will match both `"Rohan M"` and `"Rohan Sharma"`.
   - Takes a `max_results` bound to prevent buffer overflows into the caller's array (**SEC-003**).
   - Returns the exact number of matching records found.
4. **Sorting Algorithm (`sort_students`):**
   - Uses the C Standard Library `qsort()` ($O(N \log N)$ average complexity).
   - *Why `qsort` instead of bubble sort?* Bubble sort is $O(N^2)$, which takes ~1,000,000 operations for 1,000 records. `qsort` performs only ~$1,000 \times \log_2(1,000) \approx 10,000$ operations. This ensures our benchmark runs in ~0.001 seconds, well below the 2.0s requirement of **NFR-001**.
   - Modular comparator functions: `cmp_roll_asc`, `cmp_roll_desc`, `cmp_name_asc`, `cmp_name_desc`, `cmp_cgpa_asc`, `cmp_cgpa_desc`.

---

### 3. Viva & Evaluation Q&A (Prepare for External / Evaluator Questions)

**Q1: How does your module satisfy the Deliverable 1 & 2 requirements?**
> *"I own WP4 (Record Search, View & Listing). In Deliverable 2, I was assigned FR-004 (search by roll number and name), FR-007 (list and sort records), and NFR-001 (performance under 2 seconds for 1,000 records). My module implements these in `src/search_list.c`, provides complete unit tests in `tests/test_search_list.c` covering TC-SEARCH-01, TC-SEARCH-02, and TC-LIST-01, and validates NFR-001 with a 1,000-record benchmark in `tests/test_perf.c`."*

**Q2: Why did you implement your own string comparison helpers instead of `strcasecmp`?**
> *"Requirement NFR-006 mandates portability across both Linux GCC and Windows MinGW without modification. `strcasecmp` is a POSIX function not part of the ISO C standard, while Windows uses `_stricmp`. By implementing `ci_strcmp` and `ci_strstr` using standard `tolower()`, the code is 100% ISO C11 portable."*

**Q3: How did you test your module if the database and login modules weren't ready?**
> *"In accordance with NFR-005 (Testability) and standard Agile practice, our architecture uses dependency inversion. The search and sort functions operate on an array of `Student` structs in memory. I wrote a unit-test harness (`test_search_list.c`) with a mock student dataset to verify all positive and negative test cases headlessly before integration."*

**Q4: How did you verify the 1,000-record performance requirement (NFR-001)?**
> *"I created a dedicated performance benchmark (`test_perf.c`, TC-PERF-01) that programmatically generates 1,000 realistic student records and benchmarks 1,000 roll number lookups, a substring search, and full array sorts. The entire suite executes in approximately 0.037 seconds on our test machine, which uses only 1.85% of our 2.0-second SLA limit."*

**Q5: How does your code adhere to the maintainability constraint (NFR-004)?**
> *"NFR-004 states that no function should exceed ~60 lines. In `src/search_list.c`, each comparator is 4–7 lines, string helpers are 10–18 lines, and our longest function is under 30 lines. All functions are single-responsibility."*

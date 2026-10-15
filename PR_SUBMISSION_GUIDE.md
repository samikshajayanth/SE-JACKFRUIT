# StudentRMS - Sprint 1 GitHub PR Submission Guide
## Step-by-Step Instructions for Rohan M (Member 2)
**Deliverable Traceability:** Deliverables Part-2, Item 2.b, 2.c, 2.d

---

### Step 1: Initialize / Update Git Branch

Open PowerShell and navigate to your team repository:
```powershell
cd "c:\Rohan\B.Tech\V SEM\Software Engineering\Jackfruit Project\SE-JACKFRUIT"

# 1. Fetch latest upstream changes
git checkout main
git pull upstream main

# 2. Create feature branch for Sprint 1
git checkout -b feature/sprint1-core-modules
```

---

### Step 2: Copy Sprint 1 Files into the Repository

Copy the verified files from `StudentRMS_Sprint1` into `SE-JACKFRUIT`:
```powershell
$src = "c:\Rohan\B.Tech\V SEM\Software Engineering\Jackfruit Project\StudentRMS_Sprint1"
$dst = "c:\Rohan\B.Tech\V SEM\Software Engineering\Jackfruit Project\SE-JACKFRUIT"

Copy-Item -Path "$src\include" -Destination "$dst" -Recurse -Force
Copy-Item -Path "$src\src" -Destination "$dst" -Recurse -Force
Copy-Item -Path "$src	ests" -Destination "$dst" -Recurse -Force
Copy-Item -Path "$src\.github" -Destination "$dst" -Recurse -Force
Copy-Item -Path "$srcuild.bat" -Destination "$dst" -Force
Copy-Item -Path "$src\Makefile" -Destination "$dst" -Force
Copy-Item -Path "$src\BACKLOG_AND_SPRINT_PLAN.md" -Destination "$dst" -Force
Copy-Item -Path "$src\SPRINT1_REVIEW_AND_DEVIATIONS.md" -Destination "$dst" -Force
Copy-Item -Path "$src\DEMO_SCRIPT_SPRINT1.md" -Destination "$dst" -Force
```

---

### Step 3: Commit and Push to Your Fork

```powershell
git status
git add .
git commit -m "feat(sprint1): deliver Sprint 1 working product, CI workflow, and test suites (FR-001, FR-002, FR-004, FR-007, FR-008, NFR-001)"
git push -u origin feature/sprint1-core-modules
```

---

### Step 4: Raise the Pull Request on GitHub

1. Go to: `https://github.com/samikshajayanth/SE-JACKFRUIT`
2. You will see a banner: **"feature/sprint1-core-modules had recent pushes"** $\rightarrow$ Click **"Compare & pull request"**.
3. **PR Title:**
   ```text
   Sprint 1 Deliverable: Core Working Product, WP4 Search/Listing, CI/CD Pipeline & Test Harness
   ```
4. **PR Description Body (Copy & Paste below):**

```markdown
## StudentRMS - Sprint 1 Pull Request
### Submitted by: Rohan M (PES1UG24CS381) - Member 2

### 1. Summary of Changes
This PR completes the deliverables for **Sprint 1 (19th Oct - 23rd Oct 2026)** per *Deliverables Part-2*:
- **WP4 (Rohan M):** Search by roll number & name (`FR-004`), multi-attribute sorting (`FR-007`), and 1,000-record benchmark (`NFR-001`).
- **WP3 (Auth):** Session-gated administrator login (`FR-001`, `SEC-002`) and failed-login audit log (`SEC-005`).
- **WP5 (Record Mgmt):** Add student record (`FR-002`), duplicate prevention (`FR-003`), marks validation (`FR-012`).
- **WP6 (Academic Engine):** Automatic percentage and CGPA derivation (`FR-008`).
- **CI/CD Automation:** GitHub Actions workflow (`.github/workflows/ci.yml`) compiling with GCC and executing automated tests on push/PR.

### 2. Verification Evidence
- **Automated Unit Tests:** 28 / 28 test cases passed (`TC-AUTH-*`, `TC-ADD-*`, `TC-SEARCH-*`, `TC-LIST-*`, `TC-CGPA-*`).
- **NFR-001 Performance Benchmark:** 1,000 records search and sort completed in **0.0470s** (SLA $\le 2.0s$).
- **Working Console Product:** Compiled executable `studentrms.exe` demonstrates end-to-end functionality.

### 3. Traceability
- Addresses Backlog items: **US-01 through US-10** (23 Story Points).
- Mapped to SRS v1.0, SAD v1.0, and STP v1.0.
```

---

### Step 5: Repo Owner Review & Merge (Samiksha Jayanth)
Per **Deliverables Part-2, Item 2.d**:
- The repository owner (`samikshajayanth`) opens the PR on GitHub.
- Verifies that GitHub Actions CI checks pass (green checkmark).
- Clicks **"Merge pull request"** and commits to `main`.

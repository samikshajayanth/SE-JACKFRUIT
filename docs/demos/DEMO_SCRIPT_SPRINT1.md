# StudentRMS - Sprint 1 Working Product Demo Script (60 Seconds)
## Deliverables Part-2 (Item 2.g): 1-Minute Video Demonstration
**Presenter:** Rohan M (`PES1UG24CS381`) | **Team 4** (StudentRMS)  
**Deliverable Requirement:** *"Record a minute video of the outcome of the first Sprint. [It should be a working product]. Upload it to the repo."*

---

### Pre-Recording Setup:
1. Open PowerShell in:
   `c:\Rohan\B.Tech\V SEM\Software Engineering\Jackfruit Project\StudentRMS_Sprint1`
2. Start screen recorder (**Win + G** or OBS Studio).
3. Set your microphone.

---

### 60-Second Video Walkthrough

| Timestamp | Screen Action | What to Say (Verbatim Voiceover) |
| :---: | :--- | :--- |
| **0:00 - 0:10** | Camera / Terminal with title visible | *"Hello! I am Rohan M, representing Team 4 for StudentRMS. Today I am presenting our working product outcome for Sprint 1, covering authentication, record management, search, and sorting."* |
| **0:10 - 0:22** | Run `.\test_suite.exe` | *"We begin with our automated verification suite. Notice that all 28 tests pass across authentication, validation, CGPA computation, roll search, name search, and sorting."* |
| **0:22 - 0:32** | Run `.\test_perf.exe` | *"Next, our NFR-001 performance test benchmarks 1,000 records. All search and sorting operations complete in just 0.047 seconds, easily passing our 2.0-second SLA."* |
| **0:32 - 0:45** | Run `.\studentrms.exe`<br>Login with `admin` / `admin123`<br>Option `1` (View All) | *"Now launching the interactive application. First, access is gated by administrator login. Once authenticated, we view our formatted student table with automatically derived percentages and CGPAs."* |
| **0:45 - 0:55** | Option `4` $\rightarrow$ search `rohan`<br>Option `5` $\rightarrow$ CGPA Rank List | *"We can perform fast substring search—finding 'Rohan' immediately—or generate an academic rank list sorted by CGPA in descending order."* |
| **0:55 - 1:00** | Option `9` (Logout) | *"Sprint 1 is fully integrated, tested, and CI-automated. Thank you!"* |

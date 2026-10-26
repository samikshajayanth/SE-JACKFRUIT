# StudentRMS - Sprint 2 Working Product Demo (2 Minutes)

**Target duration:** 1:55 to 2:00  
**Product:** Student Record Management System (C console application)

## Pre-recording checklist
1. Run `make clean && make` on Linux, or `build.bat` on Windows.
2. Run `./test_suite`, `./test_sprint2`, and `./test_perf` (Windows: corresponding `.exe` files).
3. Launch the application from the repository directory so `students.dat`, `reports.txt`, and `login.log` are easy to show.
4. Prepare a demo record for deletion. Do not delete a team member's real record.

## Recording storyboard

| Time | Screen action | Suggested narration |
|---|---|---|
| 0:00-0:12 | Show project title and actual test output. | "This is StudentRMS, our Sprint 2 working product. We added regression coverage for record lifecycle, persistence, and report generation." |
| 0:12-0:27 | Launch, log in, show the student table. | "Administrator access is required. The application restores student records from binary storage at startup." |
| 0:27-0:48 | Update a demo student's name or marks and show percentage/CGPA. | "Updating validates replacement data, prevents duplicate roll numbers, and recalculates academic values." |
| 0:48-1:06 | Start delete, choose No, show record remains; repeat and confirm on a demo record. | "Deletion requires confirmation. Cancelling preserves the record; confirming removes it." |
| 1:06-1:23 | Exit and restart; search the updated student. | "After restart, the saved state is restored, demonstrating persistence across sessions." |
| 1:23-1:40 | Export reports and open `reports.txt`. | "The export contains both the student listing and a CGPA-descending rank list." |
| 1:40-1:55 | Show actual regression output and CI. | "Sprint 2 adds lifecycle operations, persistence, report export, and regression verification." |
| 1:55-2:00 | Show repository and finish. | "Thank you." |

## Before upload
- Confirm the build and test output match the submitted branch.
- Upload the recording under `deliverables/sprint2_demo.mp4` or document a stable share link here.
- Do not claim a test passed unless its actual output shows a pass.

# Sprint 2 Demo Checklist

Run from the repository directory after `cmd /c build.bat`. Use the application's seeded records or a synthetic record created for the demonstration; do not delete team data.

1. Start `studentrms.exe` and log in with the credentials documented by the application.
2. Select **Update Student Record**, enter a test roll number, replace the name or marks, and show the recalculated percentage/CGPA.
3. Select **Delete Student Record**, answer `n`, and show the cancellation message and unchanged record.
4. Repeat deletion for the test record and answer `y`; show the success message.
5. Select **Export Student and Rank Reports** and show `reports.txt`.
6. Select **Logout and Exit**, start the application again from the same directory, and show that the update remains and the deleted record is absent.
7. Show the actual `build.bat` and regression-test output.

Observed during issue #32 verification: update, cancellation, confirmed deletion, restart persistence, report generation, and descending rank output all passed. Video recording remains a manual action.

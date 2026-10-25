@echo off
echo ==========================================================
echo   Building StudentRMS Sprint 2 Product and Test Suites
echo ==========================================================

echo [1/5] Compiling integrated test suite...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c tests/test_suite.c -o test_suite.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo [2/5] Compiling search/list unit tests...
gcc -Wall -Wextra -std=c11 -Iinclude src/search_list.c tests/test_search_list.c -o test_search_list.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo [3/5] Compiling Sprint 2 regression tests...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c tests/test_sprint2.c -o test_sprint2.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo [4/5] Compiling 1,000-record performance benchmark...
gcc -Wall -Wextra -std=c11 -Iinclude src/search_list.c tests/test_perf.c -o test_perf.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo [5/5] Compiling interactive product...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c src/main.c -o studentrms.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo.
echo ==========================================================
echo   BUILD SUCCESSFUL. Running test suites...
echo ==========================================================
test_suite.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
test_sprint2.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
test_perf.exe
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
echo.
echo Interactive app: studentrms.exe

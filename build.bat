@echo off
setlocal

echo ==========================================================
echo   Building StudentRMS Product and Test Suites (MinGW)
echo ==========================================================

echo [1/6] Compiling integrated test suite...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c tests/test_suite.c -o test_suite.exe
if errorlevel 1 exit /b 1

echo [2/6] Compiling search/list unit tests...
gcc -Wall -Wextra -std=c11 -Iinclude src/search_list.c tests/test_search_list.c -o test_search_list.exe
if errorlevel 1 exit /b 1

echo [3/6] Compiling Sprint 2 regression tests...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c tests/test_sprint2.c -o test_sprint2.exe
if errorlevel 1 exit /b 1

echo [4/6] Compiling Part 3 robustness tests...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c tests/test_part3_unit.c -o test_part3_unit.exe
if errorlevel 1 exit /b 1

echo [5/6] Compiling 1,000-record performance benchmark...
gcc -Wall -Wextra -std=c11 -Iinclude src/search_list.c tests/test_perf.c -o test_perf.exe
if errorlevel 1 exit /b 1

echo [6/6] Compiling interactive product...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c src/main.c -o studentrms.exe
if errorlevel 1 exit /b 1

echo.
echo ==========================================================
echo   BUILD SUCCESSFUL. Running all test suites...
echo ==========================================================

echo [TEST 1/5] Integrated suite
test_suite.exe
if errorlevel 1 exit /b 1

echo [TEST 2/5] Search/list suite
test_search_list.exe
if errorlevel 1 exit /b 1

echo [TEST 3/5] Sprint 2 regression suite
test_sprint2.exe
if errorlevel 1 exit /b 1

echo [TEST 4/5] Part 3 robustness suite
test_part3_unit.exe
if errorlevel 1 exit /b 1

echo [TEST 5/5] Performance benchmark
test_perf.exe
if errorlevel 1 exit /b 1

echo.
echo ALL FIVE TEST SUITES PASSED.
echo Interactive app: studentrms.exe
endlocal

@echo off
echo ==========================================================
echo   Compiling StudentRMS Sprint 1 Product and Test Suites
echo   Team 4 | Software Engineering (UE24CS341A)
echo ==========================================================

echo [1/4] Compiling Integrated Test Suite (test_suite.exe)...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c tests/test_suite.c -o test_suite.exe
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Failed to compile test_suite.exe
    exit /b %ERRORLEVEL%
)

echo [2/4] Compiling WP4 Unit Tests (test_search_list.exe)...
gcc -Wall -Wextra -std=c11 -Iinclude src/search_list.c tests/test_search_list.c -o test_search_list.exe
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Failed to compile test_search_list.exe
    exit /b %ERRORLEVEL%
)

echo [3/4] Compiling NFR-001 Performance Benchmark (test_perf.exe)...
gcc -Wall -Wextra -std=c11 -Iinclude src/search_list.c tests/test_perf.c -o test_perf.exe
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Failed to compile test_perf.exe
    exit /b %ERRORLEVEL%
)

echo [4/4] Compiling Interactive Console Product (studentrms.exe)...
gcc -Wall -Wextra -std=c11 -Iinclude src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/main.c -o studentrms.exe
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Failed to compile studentrms.exe
    exit /b %ERRORLEVEL%
)

echo.
echo ==========================================================
echo   BUILD SUCCESSFUL! Running Automated Verification Tests
echo ==========================================================
echo.
test_suite.exe
echo.
test_perf.exe
echo.
echo To launch interactive console application, run: studentrms.exe

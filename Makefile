CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
CORE_SRC = src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c

all: test_suite test_search_list test_perf studentrms

test_suite: $(CORE_SRC) tests/test_suite.c
	$(CC) $(CFLAGS) $^ -o $@

test_search_list: src/search_list.c tests/test_search_list.c
	$(CC) $(CFLAGS) $^ -o $@

test_perf: src/search_list.c tests/test_perf.c
	$(CC) $(CFLAGS) $^ -o $@

studentrms: $(CORE_SRC) src/main.c
	$(CC) $(CFLAGS) $^ -o $@

test: test_suite test_perf
	./test_suite
	./test_perf

clean:
	rm -f test_suite test_search_list test_perf studentrms *.exe *.log

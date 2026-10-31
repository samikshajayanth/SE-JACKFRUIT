CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
COVERAGE_FLAGS = --coverage -O0 -g
CORE_SRC = src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c
COVERAGE_DIR = build/coverage
COVERAGE_CORE_OBJECTS = $(patsubst %.c,$(COVERAGE_DIR)/%.o,$(CORE_SRC))
COVERAGE_BINS = $(COVERAGE_DIR)/test_suite $(COVERAGE_DIR)/test_search_list $(COVERAGE_DIR)/test_sprint2 $(COVERAGE_DIR)/test_part3_unit $(COVERAGE_DIR)/test_perf

all: test_suite test_search_list test_sprint2 test_part3_unit test_perf studentrms_app

test_suite: $(CORE_SRC) tests/test_suite.c
	$(CC) $(CFLAGS) $^ -o $@

test_search_list: src/search_list.c tests/test_search_list.c
	$(CC) $(CFLAGS) $^ -o $@

test_sprint2: $(CORE_SRC) tests/test_sprint2.c
	$(CC) $(CFLAGS) $^ -o $@

test_part3_unit: $(CORE_SRC) tests/test_part3_unit.c
	$(CC) $(CFLAGS) $^ -o $@

test_perf: src/search_list.c tests/test_perf.c
	$(CC) $(CFLAGS) $^ -o $@

studentrms_app: $(CORE_SRC) src/main.c
	$(CC) $(CFLAGS) $^ -o $@

test: test_suite test_search_list test_sprint2 test_part3_unit test_perf
	./test_suite
	./test_search_list
	./test_sprint2
	./test_part3_unit
	./test_perf

# Compile one object per source file so gcov can keep coverage data separate
# for each module and combine execution counts from the instrumented test binaries.
$(COVERAGE_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

$(COVERAGE_DIR)/test_suite: $(COVERAGE_CORE_OBJECTS) $(COVERAGE_DIR)/tests/test_suite.o
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@

$(COVERAGE_DIR)/test_search_list: $(COVERAGE_DIR)/src/search_list.o $(COVERAGE_DIR)/tests/test_search_list.o
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@

$(COVERAGE_DIR)/test_sprint2: $(COVERAGE_CORE_OBJECTS) $(COVERAGE_DIR)/tests/test_sprint2.o
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@

$(COVERAGE_DIR)/test_part3_unit: $(COVERAGE_CORE_OBJECTS) $(COVERAGE_DIR)/tests/test_part3_unit.o
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@

$(COVERAGE_DIR)/test_perf: $(COVERAGE_DIR)/src/search_list.o $(COVERAGE_DIR)/tests/test_perf.o
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@

coverage:
	rm -rf $(COVERAGE_DIR) *.gcov
	$(MAKE) $(COVERAGE_BINS)
	./$(COVERAGE_DIR)/test_suite
	./$(COVERAGE_DIR)/test_search_list
	./$(COVERAGE_DIR)/test_sprint2
	./$(COVERAGE_DIR)/test_part3_unit
	./$(COVERAGE_DIR)/test_perf
	gcov -b -c -o $(COVERAGE_DIR)/src src/auth.c src/student_mgmt.c src/cgpa.c src/search_list.c src/storage.c src/report.c

clean:
	rm -f test_suite test_search_list test_sprint2 test_part3_unit test_perf studentrms_app *.exe
	rm -rf build *.gcov

.PHONY: all test coverage clean

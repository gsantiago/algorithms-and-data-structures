#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "base.h"

typedef struct {
  char *label;
  callback_t callback;
} test_suite_t;

typedef struct {
  int index;
  int passed;
  int failed;
  int x;
  int y;
  double time;
  bool iterative;
  FILE *log;
  test_suite_t **tests;
  int count;
} test_t;

test_t test_obj;

clock_t start, end;
double cpu_time_used;

bool cli_contains(int argc, char **argv, char *command) {
  int i = 0;

  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], command) == 0) {
      return true;
    }
  }

  return false;
}

static void vprintf_log(char *format, va_list args) {
  if (test_obj.log != NULL) {
    vfprintf(test_obj.log, format, args);
  }
}

static void printf_log(char *format, ...) {
  va_list args;
  va_start(args, format);

  vprintf_log(format, args);

  va_end(args);
}

static void process_result(int result, char *format, ...) {
  va_list args;

  va_start(args, format);

  printf("  ");

  if (result) {
    textbackground(GREEN);
    textcolor(BLACK);
    cprintf("PASS");
    printf_log("[PASS]");
    test_obj.passed++;
  } else {
    textbackground(RED);
    textcolor(BLACK);
    cprintf("FAIL");
    printf_log("[FAIL]");
    test_obj.failed++;
  }

  textbackground(BLACK);
  textcolor(LIGHTGRAY);

  printf(" ");
  vprintf(format, args);
  printf("\r\n");

  printf_log(" ");
  vprintf_log(format, args);
  printf_log("\n");

  va_end(args);
}

static void print_help() {
  printf("-h Show help\n");
  printf("-i Iterative mode\n");
  printf("-l Outputs a log file\n");
  exit(0);
}

void tests_init(int argc, char **argv) {
  if (cli_contains(argc, argv, "-h")) {
    print_help();
  }

  clrscr();

  test_obj.index = 0;
  test_obj.passed = 0;
  test_obj.failed = 0;
  test_obj.count = 0;
  test_obj.tests = (test_suite_t**)malloc(0);
  test_obj.time = 0;
  test_obj.iterative = cli_contains(argc, argv, "-i");
  test_obj.log = cli_contains(argc, argv, "-l")
    ? fopen("tests.log", "w+")
    : NULL;
}

static int tests_end() {
  int total = test_obj.passed + test_obj.failed;

  printf("\n");

  textcolor(LIGHTGRAY);
  cprintf("Tests: ");
  textcolor(WHITE);
  cprintf("%d\r\n", total);

  textcolor(LIGHTGRAY);
  cprintf("Passed: ");
  textcolor(GREEN);
  cprintf("%d\r\n", test_obj.passed);

  textcolor(LIGHTGRAY);
  cprintf("Failed: ");
  textcolor(RED);
  cprintf("%d\r\n", test_obj.failed);

  textcolor(LIGHTGRAY);
  cprintf("Time: %fs\r\n", test_obj.time);

  printf_log(
    "---\nPassed: %d/%d\nFailed: %d/%d\nTime: %fs\n",
    test_obj.passed,
    total,
    test_obj.failed,
    total,
    test_obj.time
  );

  if (test_obj.log != NULL) {
    fclose(test_obj.log);
  }

  return test_obj.failed > 0;
}

static void test_start(char *message) {
  start = clock();
  cprintf("%d) %s ", ++test_obj.index, message);
  printf_log("%d) %s\n", test_obj.index, message);
  test_obj.x = wherex();
  test_obj.y = wherey();
  printf("\n");
}

static void test_finish() {
  int x, y;
  x = wherex();
  y = wherey();
  end = clock();
  cpu_time_used = ((double) (end - start) / CLOCKS_PER_SEC);
  test_obj.time += cpu_time_used;
  gotoxy(test_obj.x, test_obj.y);
  cprintf("(%.4fs)", cpu_time_used);
  printf_log("(%fs)\n\n", cpu_time_used);
  gotoxy(x, y);

  if (test_obj.iterative) {
    printf("Press any key\n");
    getch();
  }
}

void test(char *label, callback_t callback) {
  test_obj.tests = (test_suite_t**)realloc(test_obj.tests, sizeof(test_suite_t) * (test_obj.count + 1));
  test_obj.tests[test_obj.count] = (test_suite_t*)malloc(sizeof(test_suite_t));

  test_obj.tests[test_obj.count]->label = label;
  test_obj.tests[test_obj.count]->callback = callback;

  test_obj.count++;
}

int tests_run() {
  int i;

  for (i = 0; i < test_obj.count; i++) {
    test_start(test_obj.tests[i]->label);
    test_obj.tests[i]->callback();
    test_finish();
  }

  return tests_end();
}

void expect_str_eql(char *message, char *actual, char *expected) {
  bool result = strcmp(actual, expected) == 0;
  process_result(result, message, actual, expected);
}

void expect_int_eql(char *message, int actual, int expected) {
  process_result(actual == expected, message, actual, expected);
}

void expect_char_eql(char *message, char actual, char expected) {
  process_result(actual == expected, message, actual, expected);
}

void expect_eql(char *message, void *pointer1, void *pointer2) {
  process_result(pointer1 == pointer2, message);
}

void expect_not_eql(char *message, void *pointer1, void *pointer2) {
  process_result(pointer1 != pointer2, message);
}

void expect_bool(char *message, bool actual, bool expected) {
  process_result(actual == expected, message);
}

void expect_true(char *message, bool value) {
  process_result(value, message);
}

void expect_false(char *message, bool value) {
  process_result(!value, message);
}

void expect_null(char *message, void *pointer) {
  process_result(pointer == NULL, message);
}

void expect_not_null(char *message, void *pointer) {
  process_result(pointer != NULL, message);
}

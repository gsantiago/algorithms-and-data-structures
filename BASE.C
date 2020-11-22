#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "BASE.H"

typedef struct {
  int index;
  int passed;
  int failed;
  int x;
  int y;
  double time;
  bool iterative;
  FILE *log;
} test_t;

test_t test;

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

static void print_logf(char *format, ...) {
  va_list args;
  va_start(args, format);

  if (test.log != NULL) {
    vfprintf(test.log, format, args);
  }

  va_end(args);
}

static void print_result(int result, char *message) {
  printf("  ");

  if (result) {
    textbackground(GREEN);
    textcolor(BLACK);
    cprintf("PASS");
    print_logf("[PASS]");
    test.passed++;
  } else {
    textbackground(RED);
    textcolor(BLACK);
    cprintf("FAIL");
    print_logf("[FAIL]");
    test.failed++;
  }

  textbackground(BLACK);
  textcolor(LIGHTGRAY);
  cprintf(" %s\r\n", message);
  print_logf(" %s\n", message);
}

static void print_help() {
  printf("-h Show help\n");
  printf("-i Iterative mode\n");
  printf("-l Outputs a log file\n");
  exit(0);
}

void tests_begin(int argc, char **argv) {
  if (cli_contains(argc, argv, "-h")) {
    print_help();
  }

  clrscr();

  test.index = 0;
  test.passed = 0;
  test.failed = 0;
  test.time = 0;
  test.iterative = cli_contains(argc, argv, "-i");
  test.log = cli_contains(argc, argv, "-l")
    ? fopen("test.log", "w+")
    : NULL;
}

int tests_end() {
  int total = test.passed + test.failed;

  printf("\n");

  textcolor(LIGHTGRAY);
  cprintf("Tests: ");
  textcolor(WHITE);
  cprintf("%d\r\n", total);

  textcolor(LIGHTGRAY);
  cprintf("Passed: ");
  textcolor(GREEN);
  cprintf("%d\r\n", test.passed);

  textcolor(LIGHTGRAY);
  cprintf("Failed: ");
  textcolor(RED);
  cprintf("%d\r\n", test.failed);

  textcolor(LIGHTGRAY);
  cprintf("Time: %fs\r\n", test.time);

  print_logf(
    "---\nPassed: %d/%d\nFailed: %d/%d\nTime: %fs\n",
    test.passed,
    total,
    test.failed,
    total,
    test.time
  );

  if (test.log != NULL) {
    fclose(test.log);
  }

  return test.failed > 0;
}

void test_start(char *message) {
  start = clock();
  cprintf("%d) %s ", ++test.index, message);
  print_logf("%d) %s\n", test.index, message);
  test.x = wherex();
  test.y = wherey();
  printf("\n");
}

void test_finish() {
  int x, y;
  x = wherex();
  y = wherey();
  end = clock();
  cpu_time_used = ((double) (end - start) / CLOCKS_PER_SEC);
  test.time += cpu_time_used;
  gotoxy(test.x, test.y);
  cprintf("(%.4fs)", cpu_time_used);
  print_logf("(%fs)\n\n", cpu_time_used);
  gotoxy(x, y);

  if (test.iterative) {
    printf("Press any key\n");
    getch();
  }
}

void expect_str(char *message, char *actual, char *expected) {
  print_result(strcmp(actual, expected) == 0, message);
}

void expect_int(char *message, int actual, int expected) {
  print_result(actual == expected, message);
}

void expect_eql(char *message, int expression) {
  print_result(expression != 0, message);
}

void expect_bool(char *message, bool actual, bool expected) {
  print_result(actual == expected, message);
}

void expect_null(char *message, void *pointer) {
  print_result(pointer == NULL, message);
}

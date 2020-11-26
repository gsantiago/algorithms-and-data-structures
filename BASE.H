#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

/**
 * Defines a boolean type because C doesn't have a native boolean type
 * and TCC doesn't have the `stdbool.h` header available either
 */

#define false 0
#define true 1
typedef char bool;

#endif

/**
 * Utilities
 */

bool cli_contains(int argc, char **argv, char *command);

/**
 * Test utilities
 */

void tests_begin(int argc, char **argv);
int tests_end();
void test_start(char *message);
void test_finish();
void test(char *message, void (*test_fn)());

void expect_str(char *message, char *actual, char *expected);
void expect_int(char *message, int actual, int expected);
void expect_eql(char *message, int expression);
void expect_bool(char *message, bool actual, bool expected);
void expect_true(char *message, bool value);
void expect_false(char *message, bool value);
void expect_null(char *message, void *pointer);

#ifndef BASE_H
#define BASE_H

#include "bool.h"

typedef void (*callback_t)();

/**
 * Test utilities
 */

void tests_init(int argc, char **argv);
void test(char *label, callback_t callback);
int tests_run();

/**
 * Expect.
 */

void expect_str_eql(char *message, char *actual, char *expected);
void expect_int_eql(char *message, int actual, int expected);
void expect_char_eql(char *message, char actual, char expected);
void expect_eql(char *message, void *pointer1, void *pointer2);
void expect_not_eql(char *message, void *pointer1, void *pointer2);
void expect_bool(char *message, bool actual, bool expected);
void expect_true(char *message, bool value);
void expect_false(char *message, bool value);
void expect_null(char *message, void *pointer);
void expect_not_null(char *message, void *pointer);

#endif

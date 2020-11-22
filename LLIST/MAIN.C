#include <stdio.h>
#include <stdlib.h>
#include "LLIST.H"
#include "../BASE.H"

void cell() {
  cell_t* cell;

  test_start("creates a list cell with ll_cell() function");

  cell = ll_cell(25);
  expect_int("cell data should be 25", cell->data, 25);
  expect_eql("cell next should point to NULL", cell->next == NULL);

  test_finish();
}

void stringify() {
  cell_t *list = ll_list(5, 50, 55, 10, 41, 33);

  test_start("stringifies linked list with ll_stringify() function");

  expect_str(
    "should return \"50 55 10 41 33\"",
    ll_stringify(list),
    "50 55 10 41 33"
  );

  expect_str(
    "should stringiy a single cell: \"88\"",
    ll_stringify(ll_list(1, 88)),
    "88"
  );

  test_finish();
}

void list() {
  cell_t *list = ll_list(3, 1, 2, 3);

  test_start("create linked list with ll_list() function");

  expect_str(
    "should create a list with \"1, 2, 3\"",
    ll_stringify(list),
    "1 2 3"
  );

  test_finish();
}

void concat() {
  test_start("concat two lists with ll_concat() function");

  expect_str("should concat the given two lists", "a", "b");

  test_finish();
}

void is_equal() {
  cell_t *list1, *list2;

  test_start("check if two lists are equal with ll_is_equal() function");

  list1 = ll_list(3, 8, 9, 10);
  list2 = ll_list(3, 8, 9, 10);
  expect_bool("should return true", ll_is_equal(list1, list2), true);

  list1 = ll_list(4, 1, 2, 3, 4);
  list2 = ll_list(4, 4, 3, 2, 1);
  expect_bool("should return false", ll_is_equal(list1, list2), false);

  test_finish();
}

int main(int argc, char **argv) {
  tests_begin(argc, argv);

  cell();
  stringify();
  list();
  concat();
  is_equal();

  return tests_end();
}

#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "../base.h"

void cell_tests() {
  cell_t* cell;

  test_start("creates a list cell with ll_cell() function");

  cell = ll_cell(25);
  expect_int("cell->data should be 25", cell->data, 25);
  expect_null("cell->next should be NULL", cell->next);

  test_finish();
}

void stringify_tests() {
  cell_t *list;

  test_start("stringifies linked list with ll_stringify() function");

  list = ll_list(5, 50, 55, 10, 41, 33);

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

void list_tests() {
  cell_t *list;

  test_start("create linked list with ll_list() function");

  list = ll_list(3, 1, 2, 3);

  expect_str(
    "should create a list with \"1, 2, 3\"",
    ll_stringify(list),
    "1 2 3"
  );

  test_finish();
}

void concat_tests() {
  cell_t *list1, *list2, *cell;

  test_start("concat two lists with ll_concat() function");

  list1 = ll_list(3, 11, 12, 13);
  list2 = ll_list(4, 14, 15, 16, 17);
  cell = ll_tail(list1);

  ll_concat(list1, list2);

  expect_str(
    "should concat the lists",
    ll_stringify(list1),
    "11 12 13 14 15 16 17"
  );

  expect_eql(
    "last item from list1 should point to the first item of list2",
    cell->next == list2
  );

  test_finish();
}

void is_equal_tests() {
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

void tail_tests() {
  cell_t *list, *cell;

  test_start("return the last cell from a given list with ll_tail() function");

  list = ll_list(5, 44, 54, 33, 128, 99);
  cell = ll_tail(list);

  expect_int("cell->data should be 99", cell->data, 99);
  expect_null("cell->next should be NULL", cell->next);

  test_finish();
}

void count_tests() {
  cell_t *list;

  test_start("return how many cells the given list has with ll_count() function");

  list = ll_list(1, 999);
  expect_int("should return 1", ll_count(list), 1);

  list = ll_list(4, 1, 2, 3, 4);
  expect_int("should return 4", ll_count(list), 4);

  test_finish();
}

void insert_tests() {
  cell_t *cell;

  test_start("insert a new cell after the given cell with ll_insert() function");

  cell = ll_cell(11);
  ll_insert(cell, 88);

  expect_int(
    "cell->next->data should be 88",
    cell->next->data,
    88
  );

  ll_insert(cell, 33);

  expect_str(
    "should return \"11 33 88\"",
    ll_stringify(cell),
    "11 33 88"
  );

  test_finish();
}

int main(int argc, char **argv) {
  tests_begin(argc, argv);

  cell_tests();
  stringify_tests();
  list_tests();
  concat_tests();
  is_equal_tests();
  tail_tests();
  count_tests();
  insert_tests();

  return tests_end();
}

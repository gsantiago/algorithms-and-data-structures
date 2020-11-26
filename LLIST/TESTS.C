#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "../base.h"

void cell_tests() {
  cell_t* cell;

  cell = ll_cell(25);
  expect_int("cell->data should be 25", cell->data, 25);
  expect_null("cell->next should be NULL", cell->next);
}

void stringify_tests() {
  cell_t *list;

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
}

void list_tests() {
  cell_t *list;

  list = ll_list(3, 1, 2, 3);

  expect_str(
    "should create a list with \"1, 2, 3\"",
    ll_stringify(list),
    "1 2 3"
  );
}

void concat_tests() {
  cell_t *list1, *list2, *cell;

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
}

void is_equal_tests() {
  cell_t *list1, *list2;

  list1 = ll_list(3, 8, 9, 10);
  list2 = ll_list(3, 8, 9, 10);
  expect_bool("should return true", ll_is_equal(list1, list2), true);

  list1 = ll_list(4, 1, 2, 3, 4);
  list2 = ll_list(4, 4, 3, 2, 1);
  expect_bool("should return false", ll_is_equal(list1, list2), false);
}

void tail_tests() {
  cell_t *list, *cell;

  list = ll_list(5, 44, 54, 33, 128, 99);
  cell = ll_tail(list);

  expect_int("cell->data should be 99", cell->data, 99);
  expect_null("cell->next should be NULL", cell->next);
}

void count_tests() {
  cell_t *list;

  list = ll_list(1, 999);
  expect_int("should return 1", ll_count(list), 1);

  list = ll_list(4, 1, 2, 3, 4);
  expect_int("should return 4", ll_count(list), 4);
}

void insert_tests() {
  cell_t *cell;

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
}

void swap_tests() {
  cell_t *cell1, *cell2, *cell3, *cell4, *cell5;

  cell1 = ll_cell(1);
  cell2 = ll_insert(cell1, 2);
  cell3 = ll_insert(cell2, 3);
  cell4 = ll_insert(cell3, 4);
  cell5 = ll_insert(cell4, 5);

  ll_swap(cell3, cell5);
  expect_str(
    "swaps cell3 with cell5",
    ll_stringify(cell1),
    "1 2 5 4 3"
  );
}

void reverse_tests() {
  cell_t *list;

  list = ll_list(6, 1, 2, 3, 5, 8, 13);
  ll_reverse(list);

  expect_str(
    "should return the list in the reverse order",
    ll_stringify(list),
    "13 8 5 3 2 1"
  );
}

int main(int argc, char **argv) {
  tests_begin(argc, argv);

  test(
    "creates a list cell with ll_cell() function",
    cell_tests
  );

  test(
    "stringifies linked list with ll_stringify() function",
    stringify_tests
  );

  test(
    "create linked list with ll_list() function",
    list_tests
  );

  test(
    "concat two lists with ll_concat() function",
    concat_tests
  );

  test(
    "check if two lists are equal with ll_is_equal() function",
    is_equal_tests
  );

  test(
    "return the last cell from a given list with ll_tail() function",
    tail_tests
  );

  test(
    "return how many cells the given list has with ll_count() function",
    count_tests
  );

  test(
    "insert a new cell after the given cell with ll_insert() function",
    insert_tests
  );

  test(
    "swap two cells in the list with ll_swap() function",
    swap_tests
  );

  test(
    "reverse the given list with ll_reverse() function",
    reverse_tests
  );

  return tests_end();
}

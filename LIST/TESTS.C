#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../base.h"

#define get_int(value) *((int*)value)
#define get_char(value) *((char*)value)

void suite_init_list() {
  list_t list;

  list_init(&list);

  expect_int_eql(
    "list.size should be 0",
    list.size,
    0
  );

  expect_null(
    "list.head should be NULL",
    list.head
  );

  expect_null(
    "list.tail should be NULL",
    list.tail
  );
}

void suite_destroy_list() {
  list_t list;
  char value = 'A';

  list_init(&list);
  list_insert(&list, NULL, &value);

  expect_char_eql(
    "list.head->data should be 'A'",
    get_char(list.head->data),
    'A'
  );

  list_destroy(&list);
}

void suite_insert_element_into_empty_list() {
  int value;
  int return_value;

  list_t list;

  list_init(&list);

  value = 120;
  return_value = list_insert(&list, NULL, &value);

  expect_int_eql(
    "list_insert should return 0",
    return_value,
    0
  );

  expect_int_eql(
    "list.size should be 1",
    list.size,
    1
  );

  expect_int_eql(
    "list.head->data should be 120",
    get_int(list.head->data),
    120
  );

  expect_eql(
    "list.head should be equal to list.tail",
    list.head,
    list.tail
  );
}

void suite_insert_multiple_elements() {
  int values[5] = {10, 20, 30, 40, 50};
  int i;
  list_t list;
  list_cell_t *cell;

  list_init(&list);

  for (i = 0; i < 5; i++) {
    list_insert(&list, NULL, &values[i]);
  }

  for (i = 5, cell = list.head; i > 0; i--, cell = cell->next) {
    expect_int_eql(
      "cell->data should have the correct value",
      get_int(cell->data),
      values[i - 1]
    );
  }

  expect_int_eql(
    "list.size should be 5",
    list.size,
    5
  );
}

int main(int argc, char **argv) {
  tests_init(argc, argv);

  test("initialize a list", suite_init_list);
  test("destroys a list", suite_destroy_list);
  test("insert element to an empty list", suite_insert_element_into_empty_list);
  test("insert multiple elements", suite_insert_multiple_elements);

  return tests_run();
}

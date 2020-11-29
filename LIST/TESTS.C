#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../base.h"

#define GET_INT(value) *((int*)value)
#define GET_CHAR(value) *((char*)value)

void suite_init_list() {
  list_t list;
  int return_value;

  return_value = list_init(&list);

  expect_int_eql(
    "return value should be 0",
    return_value,
    0
  );

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

void suite_init_invalid_list() {
  int return_value = list_init(NULL);

  expect_int_eql(
    "should return -1",
    return_value,
    -1
  );
}

void suite_destroy_list() {
  list_t list;
  char *value = malloc(sizeof(char));
  *value = 'A';

  list_init(&list);
  list_insert(&list, NULL, value);

  expect_char_eql(
    "list.head->data should be 'A'",
    GET_CHAR(list.head->data),
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
    GET_INT(list.head->data),
    120
  );

  expect_eql(
    "list.head should be equal to list.tail",
    list.head,
    list.tail
  );
}

void suite_insert_elements() {
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
      "cell->data should be %d",
      values[i - 1],
      GET_INT(cell->data)
    );
  }

  expect_int_eql(
    "list.size should be 5",
    list.size,
    5
  );
}

void suite_insert_multiple_elements() {
  list_t list;
  list_cell_t *cell;
  int a, b, c, d;
  int i, return_value;

  a = 20;
  b = 30;
  c = 40;
  d = 50;

  list_init(&list);
  return_value = list_insert_values(
    &list,
    4,
    &a,
    &b,
    &c,
    &d
  );

  expect_int_eql(
    "return value should be 0",
    return_value,
    0
  );

  expect_int_eql(
    "list.size should be 4",
    list.size,
    4
  );

  for (i = 20, cell = list.head; i <= 50; i += 10, cell = cell->next) {
    expect_int_eql(
      "cell should be %d",
      i,
      GET_INT(cell->data)
    );
  }
}

int main(int argc, char **argv) {
  tests_init(argc, argv);

  test("initialize a list", suite_init_list);
  test("initialize an invalid list", suite_init_invalid_list);
  test("destroys a list", suite_destroy_list);
  test("insert element to an empty list", suite_insert_element_into_empty_list);
  test("insert elements", suite_insert_elements);
  test("insert multiple elements", suite_insert_multiple_elements);

  return tests_run();
}

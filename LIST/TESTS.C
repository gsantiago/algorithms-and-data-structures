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

void suite_concat_lists() {
  list_t list1, list2;
  list_cell_t *cell;
  int i;
  char array1[3] = {'A', 'B', 'C'};
  char array2[2] = {'D', 'E'};
  char string[6];

  list_init(&list1);
  list_init(&list2);

  list_insert_values(
    &list1,
    3,
    &array1[0], &array1[1], &array1[2]
  );

  list_insert_values(
    &list2,
    2,
    &array2[0], &array2[1]
  );

  expect_int_eql(
    "list1.size should be 3",
    list1.size,
    3
  );

  expect_int_eql(
    "list2.size should be 2",
    list2.size,
    2
  );

  list_concat(&list1, &list2);

  expect_int_eql(
    "list1.size should be 5",
    list1.size,
    5
  );

  for (i = 0, cell = list1.head; i < 5; i++, cell = cell->next) {
    string[i] = GET_CHAR(cell->data);
  }

  string[5] = '\0';

  expect_str_eql(
    "list1 elements should be %s",
    "ABCDE",
    string
  );

  expect_char_eql(
    "list1.head->data should be 'A'",
    GET_CHAR(list1.head->data),
    'A'
  );

  expect_char_eql(
    "list1.tail->data should be 'E'",
    GET_CHAR(list1.tail->data),
    'E'
  );
}

void suite_invert_list() {
  list_t list;
  list_cell_t *cell;
  int i;
  char string[5] = {'Z', 'X', 'T', 'Y', '\0'};
  char string_test[5];

  list_init(&list);

  list_insert_values(
    &list,
    4,
    &string[0],
    &string[1],
    &string[2],
    &string[3]
  );

  expect_char_eql(
    "list.head->data should be 'Z'",
    GET_CHAR(list.head->data),
    'Z'
  );

  list_invert(&list);

  expect_char_eql(
    "list.head->data should be 'Y'",
    GET_CHAR(list.head->data),
    'Y'
  );

  expect_char_eql(
    "list.tail->data should be 'Z'",
    GET_CHAR(list.tail->data),
    'Z'
  );

  expect_null(
    "list.tail->next should be NULL",
    list.tail->next
  );

  for (i = 0, cell = list.head; i < list.size; i++, cell = cell->next) {
    string_test[i] = GET_CHAR(cell->data);
  }
  string_test[4] = '\0';

  expect_str_eql(
    "list data should be %s",
    "YTXZ",
    string_test
  );
}

void suite_search_cell() {
  list_t list;
  list_cell_t *cell;
  char values[5] = {'G', 'U', 'I', 'L', 'H'};
  char ch = 'E';

  list_init(&list);

  list_insert_values(
    &list,
    5,
    &values[0],
    &values[1],
    &values[2],
    &values[3],
    &values[4]
  );

  cell = list_search(&list, &values[3]);

  expect_char_eql(
    "cell->data should be 'L'",
    GET_CHAR(cell->data),
    'L'
  );

  expect_char_eql(
    "cell->next->data should be 'H'",
    GET_CHAR(cell->next->data),
    'H'
  );

  cell = list_search(&list, &values[0]);

  expect_char_eql(
    "cell->data should be 'G'",
    GET_CHAR(cell->data),
    'G'
  );

  cell = list_search(&list, &ch);

  expect_null(
    "cell should be NULL",
    cell
  );
}

int main(int argc, char **argv) {
  tests_init(argc, argv);

  test("initialize a list", suite_init_list);
  test("initialize an invalid list", suite_init_invalid_list);
  test("destroys a list", suite_destroy_list);
  test("insert element to an empty list", suite_insert_element_into_empty_list);
  test("insert elements", suite_insert_elements);
  test("insert multiple elements", suite_insert_multiple_elements);
  test("concat two lists", suite_concat_lists);
  test("invert a list", suite_invert_list);
  test("search a cell in a list", suite_search_cell);

  return tests_run();
}

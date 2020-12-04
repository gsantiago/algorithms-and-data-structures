#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "tester.h"

#define GET_INT(value) *((int*)value)
#define GET_CHAR(value) *((char*)value)
#define GET_STR(value) (char*)value

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
  list_insert_after(&list, NULL, value);

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
  return_value = list_insert_after(&list, NULL, &value);

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
    list_insert_after(&list, NULL, &values[i]);
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

void suite_swap_cells() {
  list_t list;
  list_cell_t *cell1, *cell2, *ptr;
  char name[6] = {'M', 'o', 'n', 'i', 'c', 'a'};
  char string[7];
  int i;

  list_init(&list);
  list_insert_values(
    &list,
    6,
    &name[0],
    &name[1],
    &name[2],
    &name[3],
    &name[4],
    &name[5]
  );

  cell1 = list_search(&list, &name[1]);
  cell2 = list_search(&list, &name[5]);

  list_swap(cell1, cell2);

  for (i = 0, ptr = list.head; i < list.size; i++, ptr = ptr->next) {
    string[i] = GET_CHAR(ptr->data);
  }
  string[6] = '\0';

  expect_str_eql(
    "list should contain %s",
    "Manico",
    string
  );
}

void suite_remove_first_cell() {
  list_t list;
  char *a, *b, *c;

  a = malloc(sizeof(char));
  b = malloc(sizeof(char));
  c = malloc(sizeof(char));

  *a = 'A';
  *b = 'B';
  *c = 'C';

  list_init(&list);
  list_insert_values(
    &list,
    3,
    a, b, c
  );

  expect_int_eql(
    "list.size should be 3",
    list.size,
    3
  );

  list_remove_after(
    &list,
    NULL
  );

  expect_int_eql(
    "list.size should be 2",
    list.size,
    2
  );

  expect_char_eql(
    "list.head->data should be 'B'",
    GET_CHAR(list.head->data),
    'B'
  );

  expect_eql(
    "list.head->next should be cell 'C'",
    list.head->next,
    list_search(&list, c)
  );

  list_destroy(&list);
}

void suite_remove_cell_from_list() {
  list_t list;
  list_cell_t *tmp;
  int *a, *b, *c;

  a = malloc(sizeof(int));
  b = malloc(sizeof(int));
  c = malloc(sizeof(int));

  *a = 5;
  *b = 8;
  *c = 10;

  list_init(&list);

  list_insert_values(
    &list,
    3,
    a, b, c
  );

  list_remove_after(&list, list.head);

  expect_int_eql(
    "list.size should be 2",
    list.size,
    2
  );

  expect_int_eql(
    "list.head->data should be 5",
    GET_INT(list.head->data),
    5
  );

  expect_int_eql(
    "list.tail->data should be 10",
    GET_INT(list.tail->data),
    10
  );

  expect_eql(
    "list.head->next should point to the tail",
    list.head->next,
    list.tail
  );

  list_destroy(&list);
}

void suite_remove_last_cell() {
  list_t list;
  char *f, *b, *i;

  f = malloc(sizeof(char));
  b = malloc(sizeof(char));
  i = malloc(sizeof(char));

  *f = 'F';
  *b = 'B';
  *i = 'I';

  list_init(&list);

  list_insert_values(
    &list,
    3,
    f, b, i
  );

  list_remove_after(
    &list,
    list_search(&list, b)
  );

  expect_int_eql(
    "list.size should be 2",
    list.size,
    2
  );

  expect_char_eql(
    "list.head->data should be 'F'",
    GET_CHAR(list.head->data),
    'F'
  );

  expect_char_eql(
    "list.tail->data should be 'B'",
    GET_CHAR(list.tail->data),
    'B'
  );

  expect_eql(
    "list.head->next should point to tail",
    list.head->next,
    list.tail
  );

  list_destroy(&list);
}

typedef struct {
  char *name;
  char *email;
} user_t;

user_t *user_create(char *name, char *email) {
  user_t *user = malloc(sizeof(list_t));

  user->name = name;
  user->email = email;

  return user;
}

void user_destroy(void *data) {
  user_t *user = (user_t*)data;
  free(user->name);
  free(user->email);
  free(user);
}

bool user_match(const void *data1, const void *data2) {
  user_t *user1, *user2;

  user1 = (user_t*)data1;
  user2 = (user_t*)data2;

  return strcmp(user1->name, user2->name) == 0;
}

void suite_custom_destroy_function() {
  user_t *user1, *user2;
  char *name1, *email1, *name2, *email2;
  list_t list;

  name1 = malloc(sizeof(char) * 100);
  name2 = malloc(sizeof(char) * 100);
  email1 = malloc(sizeof(char) * 200);
  email2 = malloc(sizeof(char) * 200);

  user1 = user_create(name1, email1);
  user2 = user_create(name2, email2);

  strcpy(user1->name, "John Doe");
  strcpy(user1->email, "john.doe@example.com");

  strcpy(user2->name, "Mary Doe");
  strcpy(user2->email, "mary.doe@example.com");

  list_init_with_destroy(&list, user_destroy);

  list_insert_after(
    &list,
    NULL,
    user1
  );

  list_insert_after(
    &list,
    list_search(&list, user1),
    user2
  );

  expect_int_eql(
    "list.size should be 2",
    list.size,
    2
  );

  list_destroy(&list);
}

void suite_find_cell() {
  list_t list;
  list_cell_t *cell;
  user_t *user1, *user2, *data;

  user1 = user_create("Guilherme", "");
  user2 = user_create("Guilherme", "");

  list_init(&list);

  list_insert_after(
    &list,
    NULL,
    user1
  );

  cell = list_find(&list, user_match, user2);
  data = (user_t*)cell->data;

  expect_not_null(
    "cell should not be NULL",
    cell
  );

  expect_not_eql(
    "cell->data and user2 should not be the same pointers",
    cell->data,
    user2
  );

  expect_str_eql(
    "cell->data should be equal to %s",
    user1->name,
    GET_STR(data->name)
  );

  user2->name = "Santiago";

  cell = list_find(&list, user_match, user2);

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
  test("swap two cells", suite_swap_cells);
  test("remove the first cell", suite_remove_first_cell);
  test("remove a cell from the list", suite_remove_cell_from_list);
  test("remove the last cell", suite_remove_last_cell);
  test("custom destroy function", suite_custom_destroy_function);
  test("find a cell with a custom matcher as callback", suite_find_cell);

  return tests_run();
}

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "LLIST.H"

cell_t* ll_cell(int data) {
  cell_t *cell = malloc(sizeof(cell_t));

  cell->data = data;
  cell->next = NULL;

  return cell;
}

cell_t* ll_list(int count, ...) {
  int i, value;
  va_list args;
  cell_t *head, *cell;

  va_start(args, count);

  for (i = 0; i < count; i++) {
    value = va_arg(args, int);

    if (i == 0) {
      head = cell = ll_cell(value);
    } else {
      cell = ll_insert(cell, value);
    }
  }

  return head;
}

void ll_print(cell_t *list) {
  if (list != NULL) {
    printf("%d\n", list->data);
    ll_print(list->next);
  }
}

int ll_count(cell_t *list) {
  int count = 0;
  cell_t *cell = list;

  while (cell != NULL) {
    count++;
    cell = cell->next;
  }

  return count;
}

int ll_height(cell_t *cell) {
  return ll_count(cell->next);
}

int ll_depth(cell_t *head, cell_t *cell) {
  cell_t *p = head;
  int count = 0;

  while (p != cell) {
    count++;
    p = p->next;
  }

  return count;
}

int ll_count_r(cell_t *list, int count) {
  if (list->next != NULL) {
    return ll_count_r(list->next, count + 1);
  }

  return count + 1;
}

cell_t* ll_search(cell_t *head, int data) {
  cell_t *p = head;

  while (p != NULL && p->data != data) {
    p = p->next;
  }

  return p;
}

cell_t* ll_search_r(cell_t *cell, int data) {
  if (cell == NULL || cell->data == data) return cell;
  return ll_search_r(cell->next, data);
}

bool ll_is_asc_order(cell_t *head) {
  cell_t *cell = head;

  while (cell->next != NULL) {
    if (cell->next->data < cell->data) {
      return false;
    }

    cell = cell->next;
  }

  return true;
}

cell_t* ll_insert(cell_t *cell, int data) {
  cell_t* new_cell = malloc(sizeof(cell_t));

  new_cell->data = data;
  new_cell->next = cell->next;
  cell->next = new_cell;

  return new_cell;
}

cell_t* ll_copy(cell_t *cell) {
  cell_t* p = cell->next;
  cell_t* next;
  cell_t* head = malloc(sizeof(cell_t));

  head->data = cell->data;
  next = head;

  while (p != NULL) {
    next = ll_insert(next, p->data);
    p = p->next;
  }

  return head;
}

void ll_concat(cell_t *first, cell_t *second) {
  // ll_tail(first)->next = second;
}

static int count_digits(int number) {
  int count = 0;

  do {
    count++;
    number = number / 10;
  } while (number != 0);

  return count;
}

char* ll_stringify(cell_t *cell) {
  int digits;
  int last = 0;
  char* list = malloc(0);
  char* string = malloc(0);

  while (cell != NULL) {
    digits = count_digits(cell->data) + 1;
    string = malloc(sizeof(char) * digits);

    sprintf(string, cell->next == NULL ? "%d" : "%d ", cell->data);

    list = realloc(list, sizeof(list) + sizeof(string));
    strncpy(&list[last], string, digits);

    free(string);
    last += digits;
    cell = cell->next;
  }

  return list;
}

bool ll_is_equal(cell_t *list1, cell_t *list2) {
  do {
    if (list1->data != list2->data) {
      return false;
    }

    list1 = list1->next;
    list2 = list2->next;
  } while (list1 != NULL);

  return true;
}

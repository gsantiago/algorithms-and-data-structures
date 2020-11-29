#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "list.h"

int list_init(list_t *list) {
  if (list != NULL) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return 0;
  }

  return -1;
}

void list_destroy(list_t *list) {
  list_cell_t *cell, *next;

  cell = list->head;

  while (cell != NULL) {
    next = cell->next;
    free(cell->data);
    free(cell);
    cell = next;
  }
}

int list_insert(list_t *list, list_cell_t *element, void *data) {
  list_cell_t *cell = malloc(sizeof(list_cell_t));

  /* Could not allocate memory for the new cell */
  if (cell == NULL) {
    return -1;
  }

  cell->data = data;

  if (element == NULL) {
    if (list->head != NULL) {
      cell->next = list->head;
    } else {
      cell->next = NULL;
    }

    list->head = cell;
  } else {
    cell->next = element->next;
    element->next = cell;
  }

  if (cell->next == NULL) {
    list->tail = cell;
  }

  list->size++;

  return 0;
}

int list_insert_values(list_t *list, int count, ...) {
  int i;
  int return_value;
  va_list args;
  list_cell_t *cell = NULL;

  va_start(args, count);

  for (i = 0; i < count; i++) {
    return_value = list_insert(list, cell, va_arg(args, void*));

    if (return_value != 0) {
      return return_value;
    }

    cell = list->tail;
  }

  va_end(args);

  return 0;
}

void list_concat(list_t *list1, list_t* list2) {
  list1->size += list2->size;
  list1->tail->next = list2->head;
  list1->tail = list2->tail;
}

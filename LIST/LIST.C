#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "list.h"

void list_init(list_t *list) {
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}

void list_destroy(list_t *list) {
  list_cell_t *cell = list->head;

  while (cell != NULL) {
    free(cell);
    cell = cell->next;
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

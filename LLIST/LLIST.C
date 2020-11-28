#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "llist.h"

void ll_init(ll_list_t *list) {
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}

int ll_insert(ll_list_t *list, ll_cell_t *element, void* data) {
  ll_cell_t *cell = (ll_cell_t*)malloc(sizeof(ll_cell_t));

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

#ifndef LIST_H
#define LIST_H

#include "../base.h"

typedef struct _list_cell_t {
  void *data;
  struct _list_cell_t *next;
} list_cell_t;

typedef struct {
  int size;
  list_cell_t *head;
  list_cell_t *tail;
  void (*destroy)(void *data);
} list_t;

int list_init(list_t *list);
void list_destroy(list_t *list);
int list_insert(list_t *list, list_cell_t *element, void* data);
int list_insert_values(list_t *list, int count, ...);
void list_concat(list_t *list1, list_t* list2);
void list_invert(list_t *list);
list_cell_t *list_search(list_t *list, void *data);
void list_swap(list_cell_t *cell1, list_cell_t *cell2);
int list_remove_next(list_t *list, list_cell_t *cell);

#endif

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
} list_t;

void list_init(list_t *list);
void list_destroy(list_t *list);
int list_insert(list_t *list, list_cell_t *element, void* data);

#endif
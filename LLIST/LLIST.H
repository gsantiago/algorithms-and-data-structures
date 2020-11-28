#ifndef LLIST_H
#define LLIST_H

#include "../base.h"

typedef struct _ll_cell_t {
  void *data;
  struct _ll_cell_t *next;
} ll_cell_t;

typedef struct {
  int size;
  ll_cell_t *head;
  ll_cell_t *tail;
} ll_list_t;

void ll_init(ll_list_t *list);
int ll_insert(ll_list_t *list, ll_cell_t *element, void* data);

#endif

#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include "../BASE.H"

typedef struct cell {
  int data;
  struct cell *next;
} cell_t;

cell_t* ll_cell(int data);
cell_t* ll_list(int count, ...);
void ll_print(cell_t *list);
int ll_count(cell_t *list);
int ll_height(cell_t *cell);
int ll_depth(cell_t *head, cell_t *cell);
int ll_count_r(cell_t *list, int count);
cell_t* ll_search(cell_t *head, int data);
cell_t* ll_search_r(cell_t *cell, int data);
bool ll_is_asc_order(cell_t *head);
cell_t* ll_insert(cell_t *cell, int data);
cell_t* ll_copy(cell_t *cell);
void ll_concat(cell_t *first, cell_t *second);
char* ll_stringify(cell_t *head);
bool ll_is_equal(cell_t *list1, cell_t *list2);

#endif

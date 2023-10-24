#ifndef LIST_H
#define LIST_H

typedef struct s_cell {
    int val;
    struct s_cell** next;
} cell;

typedef struct s_list {
    cell* head;
} list;

#endif
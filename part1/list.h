#ifndef LIST_H
#define LIST_H

typedef struct s_cell {
    int val;
    struct s_cell** next;
} cell;

typedef struct s_list {
    cell* head;
} list;

list* createList();

void addElement(list* l, int val);

void displayLevelledList(list* l);

void freeList(list* l);

void sortList(list* l);

#endif
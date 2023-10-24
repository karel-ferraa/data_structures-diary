#ifndef LIST_H
#define LIST_H


typedef struct s_cell {
    int val;
    int level;
    struct s_cell** next;
} cell;

typedef struct s_list {
    cell* head;
    int maxLevel=5;
} list;

list* createList(int maxlevel);

void addElement(list* l, int val);

void displayLevelledList(list* l);

void freeList(list* l);

void sortList(list* l);

#endif
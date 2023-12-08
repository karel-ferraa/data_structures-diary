#ifndef LISTTYPES_H
#define LISTTYPES_H

#include "appointment.h"

typedef struct s_cell {
    appointment val;
    struct s_cell* next;
} cell;

typedef struct s_list {
    cell* head;
} list;

list* createList();

void insertElement(list* l, appointment val);

void sortedInsert(list* l, appointment val);

void insertAtPos(list* l, appointment val,int index);

void displayList(list* l);

void freeList(list* l);

void sortList(list* l);

int isEmpty(list l);

int listLength(list l);

void removeElement(list* l, appointment val);

void removeAtPos(list* l, int index);

int getElementIndex(list l, appointment val);

#endif

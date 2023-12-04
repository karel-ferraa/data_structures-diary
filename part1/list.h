#ifndef LIST_H
#define LIST_H

#include "calendar.h"
#include "appointment.h"

typedef struct l_cell {
    calendarEntry* val;
    int level;
    struct l_cell** next;
} level_cell;

typedef struct s_level_list {
    level_cell** head;
    int maxLevel;
} level_list;

level_list* createLevelList(int maxlevel);

void insertElementLevelList(level_list* l, calendarEntry ce);

void sortedInsertLevelList(level_list* l, calendarEntry ce);

void insertAtPosLevelList(level_list* l, calendarEntry ce,int index);

void displayLevelledList(level_list* l);

void freeLevelCell(level_cell* lc);

void freeLevelList(level_list* l);

void sortLevelList(level_list* l);

int isLevelListEmpty(level_list l);

int levelListLength(level_list l);

void removeElementLevelList(level_list* l, calendarEntry ce);

void removeAtPosLevelList(level_list* l, int index);

int getElementIndexLevelList(level_list l, calendarEntry ce);



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

#ifndef LIST_H
#define LIST_H


typedef struct l_cell {
    int val;
    int level;
    struct l_cell** next;
} level_cell;

typedef struct s_level_list {
    level_cell** head;
    int maxLevel;
} level_list;

level_list* createLevelList(int maxlevel);

void insertElementLevelList(level_list* l, int val);

void sortedInsertLevelList(level_list* l, int val);

void insertAtPosLevelList(level_list* l, int val,int index);

void displayLevelledList(level_list* l);

void freeLevelList(level_list* l);

void sortLevelList(level_list* l);

int isLevelListEmpty(level_list l);

int levelListLength(level_list l);

void removeElementLevelList(level_list* l, int val);

void removeAtPosLevelList(level_list* l, int index);

int getElementIndexLevelList(level_list l, int val);

void balanceList(level_list* l);


typedef struct s_cell {
    int val;
    struct s_cell* next;
} cell;

typedef struct s_list {
    cell* head;
    int maxLevel;
} list;

list* createList();

void insertElement(list* l, int val);

void sortedInsert(list* l, int val);

void insertAtPos(list* l, int val,int index);

void displayList(list* l);

void freeList(list* l);

void sortList(list* l);

int isEmpty(list l);

int listLength(list l);

void removeElement(list* l, int val);

void removeAtPos(list* l, int index);

int getElementIndex(list l, int val);



#endif

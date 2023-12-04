#include "list.h"
#include "appointment.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
    Levelled list
*/

void freeLevelCell(level_cell* lc){
    freeCalendarEntry(lc->val);
    free(lc->next);
    free(lc);
}

int isLevelListEmpty(level_list l){
    return l.head[0] == NULL;
}

int levelListLength(level_list l){
    int i=0;
    level_cell* n =l.head[0];
    while (n != NULL){
        n=n->next[0];
        i++;
    }
    return i;
}

void removeElementLevelList(level_list* l, calendarEntry ce){
    int index = getElementIndexLevelList(*l, ce);
    if (index == -1){
        return;
    }
    removeAtPosLevelList(l, index);
}

void removeAtPosLevelList(level_list* l, int index){
    if (index == 0){
        level_cell* to_free = l->head[0];
        l->head[0] = l->head[0]->next[0];
        freeLevelCell(to_free);
        return;
    }
    level_cell* n = l->head[0];
    level_cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next[0];
    }
    prev->next[0] = n->next[0];
    freeLevelCell(n);
}

int getElementIndexLevelList(level_list l,calendarEntry ce){
    if (isLevelListEmpty(l)) {
        return -1;
    }

    /*We will use a 4-level list
Level constitution: the levels correspond to the successive letters in the name strings.
At the highest level (3), chaining is performed on the first letter of the string (two cells are linked if
the first letter of their string is different).
At level 2, chaining is performed if the first letter of the cell strings is the same but the second letter
is different.
At level 1, chaining is performed if the first two letters of the cell strings are the same but the third
letter is different.
At level 0, we chain all the cells*/
    int i = -1;
    level_cell* n = l.head[0];
    while (getIdentifier(*(n->val)) != getIdentifier(ce)){
        n = n->next[0];
        i++;
        if (n == NULL){
            return -1;
        }
    }
    return i;
}

// Create a new level_list
level_list* createLevelList(int maxlevel) {
    level_list *l = malloc(sizeof(level_list));
    l->head = malloc(sizeof(level_cell*)*maxlevel);
    for (int i = 0; i < maxlevel; i++)
    {
        l->head[i] = NULL;
    }
    
    l->maxLevel = maxlevel;
    return l;
}

// Free a level_list
void freeLevelList(level_list *l) {
    level_cell *n = l->head[0];
    level_cell *to_free = NULL;
    while (n->next[0] != NULL){
        to_free = n;
        n = n->next[0];
        freeLevelCell(to_free);
    }
    freeLevelCell(n);
    free(l);
}

// Add a new element to the level_list
void insertElementLevelList(level_list* l, calendarEntry ce){
    level_cell* new = malloc(sizeof(level_cell));
    new->val = &ce;
    new->level = 1;
    new->next = malloc(sizeof(level_cell*)*l->maxLevel);
    for (int i = 0; i < l->maxLevel; i++){
        new->next[i] = NULL;
    }
    new->next[0] = l->head[0];
    l->head[0] = new;
}

// Add a new element to the level_list in a sorted way (assuming the list is sorted in ascending order)
void sortedInsertLevelList(level_list* l, calendarEntry ce){
    if (isLevelListEmpty(*l)) {
        insertElementLevelList(l, ce);
        return;
    }
    level_cell* n = l->head[0];
    level_cell* prev = NULL;
    while (strcmp(getIdentifier(*(n->val)), getIdentifier(ce)) < 0){
        prev=n;
        n = n->next[0];
        if (n == NULL){
            break;
        }
    }
    if (prev==NULL){
        insertElementLevelList(l, ce);
        return;
    }
    else{
        level_cell* new = malloc(sizeof(level_cell));
        new->val = &ce;
        new->level = 1;
        new->next = malloc(sizeof(level_cell*) * (l->maxLevel));
        for (int i = 0; i < l->maxLevel; i++){
            new->next[i] = NULL;
        }
        new->next[0] = n;
        prev->next[0] = new;
    }
}

// Add a new element to the level_list at a given position

void insertAtPosLevelList(level_list* l, calendarEntry ce,int index){
    if (index == 0){
        insertElementLevelList(l, ce);
        return;
    }
    level_cell* n = l->head[0];
    level_cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next[0];
    }
    level_cell* new = malloc(sizeof(level_cell));
    new->val = &ce;
    new->level = 1;
    new->next = malloc(sizeof(level_cell*) * (l->maxLevel));
    for (int i = 0; i < l->maxLevel; i++){
        new->next[i] = NULL;
    }
    new->next[0] = n;
    prev->next[0] = new;
}

void sortLevelList(level_list* l){
    if (isLevelListEmpty(*l)) {
        return;
    }
    level_cell* n = l->head[0];
    level_cell* prev = NULL;
    while (n->next[0] != NULL){
        prev = n;
        n = n->next[0];
        if (strcmp(getIdentifier(*(prev->val)), getIdentifier(*(n->val))) > 0){
            calendarEntry* tmp = prev->val;
            prev->val = n->val;
            n->val = tmp;
            n = l->head[0];
            prev = NULL;
        }
    }
}

void displayLevelledList(level_list* l){
    if (isLevelListEmpty(*l)) {
        printf("Empty list\n");
        return;
    }
    level_cell* n = l->head[0];
    while (n->next[0] != NULL){
        printCalendarEntry(n->val);
        n = n->next[0];
    }
    printCalendarEntry(n->val);
}


/*
    Simple list
*/


list* createList(){
    list* l = malloc(sizeof(list));
    l->head = NULL;
    return l;
};

int listLength(list l){
    int i=0;
    cell* n =l.head;
    while (n != NULL){
        n=n->next;
        i++;
    }
    return i;
}

int isEmpty(list l){
    return l.head == NULL;
}

void insertElement(list* l, appointment val){
    cell new = {val, NULL};
    if (l->head == NULL){
        l->head = &new;
        return;
    }
    cell* n = l->head;
    while (n->next != NULL){
        n = n->next;
    }
    n->next = &new;
};

int appointementCmp(appointment a, appointment b){
    if (a.year < b.year){
        return -1;
    }
    else if (a.year > b.year){
        return 1;
    }
    else{
        if (a.month < b.month){
            return -1;
        }
        else if (a.month > b.month){
            return 1;
        }
        else{
            if (a.day < b.day){
                return -1;
            }
            else if (a.day > b.day){
                return 1;
            }
            else{
                if (a.hour < b.hour){
                    return -1;
                }
                else if (a.hour > b.hour){
                    return 1;
                }
                else{
                    if (a.minute < b.minute){
                        return -1;
                    }
                    else if (a.minute > b.minute){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
            }
        }
    }
}

//We assume the list is sorted in ascending order
void sortedInsert(list* l, appointment val){
    cell new = {val, NULL};
    if (l->head == NULL){
        l->head = &new;
        return;
    }
    cell* n = l->head;
    cell* prev = NULL;
    while (appointementCmp(n->val, val) < 0){
        prev = n;
        n = n->next;
        if (n == NULL){
            break;
        }
    }
    if (prev==NULL){
        new.next = l->head;
        l->head = &new;
        return;
    }
    else{
        prev->next = &new;
        new.next = n;
    }
};

void insertAtPos(list* l, appointment val,int index){
    cell new = {val, NULL};
    if (index == 0){
        new.next = l->head;
        l->head = &new;
        return;
    }
    cell*n = l->head;
    cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next;
    }
    prev->next = &new;
    new.next = n;
};

void displayList(list* l){
    if (l->head == NULL){
        printf("Empty list\n");
        return;
    }
    cell* n = l->head;
    while (n->next != NULL){
        printAppointment(n->val);
        n = n->next;
    }
    printAppointment(n->val);
};

void freeCell(cell* c){
    freeAppointment(&c->val);
    free(c);
}

void freeList(list* l){
    cell* n = l->head;
    cell* to_free = NULL;
    while (n->next != NULL){
        to_free = n;
        n = n->next;
        freeCell(to_free);
    }
    freeCell(n);
    free(l);
};

void sortList(list* l){
    if (l->head == NULL){
        return;
    }
    cell* n = l->head;
    cell* prev = NULL;
    while (n->next != NULL){
        prev = n;
        n = n->next;
        if (appointementCmp(prev->val, n->val) > 0){
            appointment tmp = prev->val;
            prev->val = n->val;
            n->val = tmp;
            n = l->head;
            prev = NULL;
        }
    }
};

void removeElement(list* l, appointment val){
    int index = getElementIndex(*l, val);
    if (index == -1){
        return;
    }
    removeAtPos(l, index);
};

void removeAtPos(list* l, int index){
    if (index == 0){
        cell* to_free = l->head;
        l->head = l->head->next;
        freeCell(to_free);
        return;
    }
    cell* n = l->head;
    cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next;
    }
    prev->next = n->next;
    freeCell(n);
};

int getElementIndex(list l, appointment val){
    if (l.head == NULL) {
        return -1;
    }
    int i = -1;
    cell* n = l.head;
    while (appointementCmp(n->val, val) != 0){
        n = n->next;
        i++;
        if (n == NULL){
            return -1;
        }
    }
    return i;
};


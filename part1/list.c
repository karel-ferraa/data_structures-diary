#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
    Levelled list
*/

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

void removeElementLevelList(level_list* l, int val){
    int index = getElementIndexLevelList(*l, val);
    if (index == -1){
        return;
    }
    removeAtPosLevelList(l, index);
}

void removeAtPosLevelList(level_list* l, int index){
    if (index == 0){
        level_cell* to_free = l->head[0];
        l->head[0] = l->head[0]->next[0];
        free(to_free);
        return;
    }
    for (int i = 0; i < l->maxLevel; i++){
        int power = pow(2,i);
        if (index % power != 0){
            break;
        }
        if (l->head[i] == NULL){
            continue;
        }
        level_cell* n = l->head[i];
        level_cell* prev = NULL;
        for(int j = 0; j < (index/power)+1; j++){
            prev = n;
            n = n->next[i];
        }
        prev->next[i] = n->next[i];
        free(n);
    }
}

int getElementIndexLevelList(level_list l,int val){
    if (isLevelListEmpty(l)) {
        return -1;
    }
    int current_level = l.maxLevel-1;
    int i = -1;
    while (l.head[current_level] == NULL){
        current_level--;
    }
    level_cell* n = l.head[current_level];
    int isInHead = 1;
    int to_compare = n->val;
    while (current_level >= 0){
        if (isInHead){
            if (to_compare == val){
                return i+pow(2, current_level);
            }
            else if (to_compare < val){
                i+=pow(2, current_level);
                n = l.head[current_level];
                current_level--;
                isInHead = 0;
                if (current_level < 0){
                    return -1;
                }
                to_compare = n->next[current_level]->val;
            }
            else{
                current_level--;
                if (current_level < 0){
                    return -1;
                }
                n = l.head[current_level];
                to_compare = n->val;
            }
        }
        else{
            if (to_compare == val){
                return i+pow(2, current_level);
            }
            else if (to_compare < val){
                i+=pow(2, current_level);
                n = n->next[current_level];
                current_level--;
                isInHead = 0;
                if (current_level < 0){
                    return -1;
                }
                to_compare = n->next[current_level]->val;
            }
            else{
                current_level--;
                to_compare = n->next[current_level]->val;
            }
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
        free(to_free);
    }
    free(n);
    free(l);
}

// Add a new element to the level_list
void insertElementLevelList(level_list* l, int val){
    level_cell* new = malloc(sizeof(level_cell));
    new->val = val;
    new->level = 1;
    new->next = malloc(sizeof(level_cell*)*l->maxLevel);
    for (int i = 0; i < l->maxLevel; i++){
        new->next[i] = NULL;
    }
    new->next[0] = l->head[0];
    l->head[0] = new;
}

// Add a new element to the level_list in a sorted way (assuming the list is sorted in ascending order)
void sortedInsertLevelList(level_list* l,int val){
    if (isLevelListEmpty(*l)) {
        insertElementLevelList(l, val);
        return;
    }
    level_cell* n = l->head[0];
    level_cell* prev = NULL;
    while (n->val < val){
        prev=n;
        n = n->next[0];
        if (n == NULL){
            break;
        }
    }
    if (prev==NULL){
        insertElementLevelList(l, val);
        return;
    }
    else{
        level_cell* new = malloc(sizeof(level_cell));
        new->val = val;
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
void insertAtPosLevelList(level_list* l,int val,int index){
    if (index == 0){
        insertElementLevelList(l, val);
        return;
    }
    level_cell*n = l->head[0];
    level_cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next[0];
    }
    level_cell* new = malloc(sizeof(level_cell));
    new->val = val;
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
        if (prev->val > n->val){
            int tmp = prev->val;
            prev->val = n->val;
            n->val = tmp;
            n = l->head[0];
            prev = NULL;
        }
    }
}

void displayLevelledList(level_list* l){
    if (isLevelListEmpty(*l)) {
	    printf("Empty level_list\n");
	    return;
    }
    level_cell* n ;
    for (int i=0;i<l->maxLevel;i++){
        if (l->head[i] == NULL){
            printf("NULL\n");
            continue;
        }
        n = l->head[i];
        for (int j = 1; j < pow(2,i)-1; j++){
            printf("------------");
        }
        if (i > 0){
            printf("----------->");
        }
        while (n->next[i] != NULL){
            printf("[ %05d ]-", n->val);
            for (int j = 1; j < pow(2,i); j++){
                printf("------------");
            }
            printf("->");
            n = n->next[i];
        }
        printf("[ %05d ]\n", n->val);
    }
}


void balanceList(level_list* l){
	int i, j;
	level_cell *node, *prev;
	for (i=1; i<l->maxLevel; i++) {
        // for each level, starting from the second one
        //Get the 2**n node of the level_list
        node = l->head[0];
        for (j=1; j<pow(2,i); j++) {
            node = node->next[0];
            if (node == NULL) {
                break;
            }
        }
        l->head[i] = node;
        while (node != NULL) {
            prev=node;
            for (j=0; j<pow(2,i); j++) {
                node = node->next[0];
                if (node == NULL) {
                    break;
                }
            }
            prev->next[i] = node;
        }
	}
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

void insertElement(list* l, int val){
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

//We assume the list is sorted in ascending order
void sortedInsert(list* l, int val){
    cell new = {val, NULL};
    if (l->head == NULL){
        l->head = &new;
        return;
    }
    cell* n = l->head;
    cell* prev = NULL;
    while (n->val < val){
        prev=n;
        n = n->next;
        if (n == NULL){
            break;
        }
    }
    if (prev==NULL){
        l->head = &new;
        new.next = n;
        return;
    }
    else{
        prev->next = &new;
        new.next = n;
    }
};

void insertAtPos(list* l, int val,int index);

void displayList(list* l);

void freeList(list* l);

void sortList(list* l);

int isEmpty(list l);

int listLength(list l);

void removeElement(list* l, int val);

void removeAtPos(list* l, int index);

int getElementIndex(list l, int val);


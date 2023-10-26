#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int isEmpty(list l){
    return l.head[0] == NULL;
}

int listLength(list l){
    int i=0;
    cell* n =l.head[0];
    while (n != NULL){
        n=n->next[0];
        i++;
    }
    return i;
}

void removeElement(list* l, int val){
    int index = getElementIndex(*l, val);
    if (index == -1){
        return;
    }
    removeAtPos(l, index);
}

void removeAtPos(list* l, int index){
    if (index == 0){
        cell* to_free = l->head[0];
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
        cell* n = l->head[i];
        cell* prev = NULL;
        for(int j = 0; j < (index/power)+1; j++){
            prev = n;
            n = n->next[i];
        }
        prev->next[i] = n->next[i];
        free(n);
    }
}

int getElementIndex(list l,int val){
    if (isEmpty(l)) {
        return -1;
    }
    int current_level = l.maxLevel-1;
    int i = -1;
    while (l.head[current_level] == NULL){
        current_level--;
    }
    cell* n = l.head[current_level];
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

// Create a new list
list* createList(int maxlevel) {
    list *l = malloc(sizeof(list));
    l->head = malloc(sizeof(cell*)*maxlevel);
    for (int i = 0; i < maxlevel; i++)
    {
        l->head[i] = NULL;
    }
    
    l->maxLevel = maxlevel;
    return l;
}

// Free a list
void freeList(list *l) {
    cell *n = l->head[0];
    cell *to_free = NULL;
    while (n->next[0] != NULL){
        to_free = n;
        n = n->next[0];
        free(to_free);
    }
    free(n);
    free(l);
}

// Add a new element to the list
void insertElement(list* l, int val){
    cell* new = malloc(sizeof(cell));
    new->val = val;
    new->level = 1;
    new->next = malloc(sizeof(cell*)*l->maxLevel);
    for (int i = 0; i < l->maxLevel; i++){
        new->next[i] = NULL;
    }
    new->next[0] = l->head[0];
    l->head[0] = new;
}

// Add a new element to the list in a sorted way
void sortedInsert(list* l,int val){
    if (isEmpty(*l)) {
        insertElement(l, val);
        return;
    }
    cell* n = l->head[0];
    cell* prev = NULL;
    while (n->val < val){
        prev=n;
        n = n->next[0];
        if (n == NULL){
            break;
        }
    }
    if (prev==NULL){
        insertElement(l, val);
        return;
    }
    else{
        cell* new = malloc(sizeof(cell));
        new->val = val;
        new->level = 1;
        new->next = malloc(sizeof(cell*) * (l->maxLevel));
        for (int i = 0; i < l->maxLevel; i++){
            new->next[i] = NULL;
        }
        new->next[0] = n;
        prev->next[0] = new;
    }
}

// Add a new element to the list at a given position
void insertAtPos(list* l,int val,int index){
    if (index == 0){
        insertElement(l, val);
        return;
    }
    cell*n = l->head[0];
    cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next[0];
    }
    cell* new = malloc(sizeof(cell));
    new->val = val;
    new->level = 1;
    new->next = malloc(sizeof(cell*) * (l->maxLevel));
    for (int i = 0; i < l->maxLevel; i++){
        new->next[i] = NULL;
    }
    new->next[0] = n;
    prev->next[0] = new;
}

void sortList(list* l){
    if (isEmpty(*l)) {
        return;
    }
    cell* n = l->head[0];
    cell* prev = NULL;
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

void displayLevelledList(list* l){
    if (isEmpty(*l)) {
	    printf("Empty list\n");
	    return;
    }
    cell* n ;
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


void balanceList(list* l){
	int i, j;
	cell *node, *prev;
	for (i=1; i<l->maxLevel; i++) {
        // for each level, starting from the second one
        //Get the 2**n node of the list
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

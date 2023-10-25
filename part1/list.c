#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int isEmpty(list* l){
    return l->head[0] == NULL;
}

// Create a new list
list *createList(int maxlevel) {
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
    new->next[0] = l->head[0];
    l->head[0] = new;
}

// Add a new element to the list in a sorted way
void sortedInsert(list* l,int val){
    if (isEmpty(l)) {
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
    new->next[0] = n;
    prev->next[0] = new;
}

void sortList(list* l){
    if (isEmpty(l)) {
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
    if (isEmpty(l)) {
	    printf("Empty list\n");
	    return;
    }
    cell* n = l->head[0];
    while (n->next[0] != NULL){
        printf("[ %d ]-->", n->val);
        n = n->next[0];
    }
    printf("[ %d ]\n", n->val);
}


void balanceList(list* l){

}
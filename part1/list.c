#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// Create a new list
list *createList(int maxlevel) {
    list *l = malloc(sizeof(list));
    l->head = NULL;
    l->maxLevel = maxlevel;
    return l;
}

// Free a list
void freeList(list *l) {
    cell *n = l->head;
    cell *to_free = NULL;
    int br = 0;
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
    new->next = l->head[0];
    l->head[0] = new;
}

void insertAtPos(list* l,int val,int index){
    if (index == 0){
        insertElement(l, val);
        return;
    }
    cell*n = l->head;
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

void displayLevelledList(list* l){
    cell* n = l->head[0];
    while (n->next[0] != NULL){
        printf("[ %d ]-->", n->val);
        n = n->next[0];
    }
    printf("[ %d ]\n", n->val);
}
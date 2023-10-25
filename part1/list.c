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
    cell* n = l->head[0];
    cell* prev = NULL;
    for(int i = 0; i < index; i++){
        prev = n;
        n = n->next[0];
    }
    prev->next[0] = n->next[0];
    free(n);
}

int getElementIndex(list l,int val){
    if (isEmpty(l)) {
        return -1;
    }
    int current_level = l.maxLevel-1;
    int i = 0;
    cell* n = l.head[current_level];
    do
    {
        if (n->val == val){
            i+=pow(2, current_level);
            return i;
        }
        else if (n->val > val){
            current_level--;
            n = l.head[current_level];
        }
        else{
            i+=pow(2, current_level);
            current_level--;
            n = n->next[current_level];
        }
    } while((n->val > val || n->next[current_level] != NULL) && current_level > 0);
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
    cell* n = l->head[0];
    while (n->next[0] != NULL){
        printf("[ %d ]-->", n->val);
        n = n->next[0];
    }
    printf("[ %d ]\n", n->val);
}


void balanceList(list* l){
	int i, j, k;
	cell *node, *next_node;
	for (i=1; i<l->maxLevel; i++) {
		node = l->head[i];
		for (j=0; j<listLength(*l)/pow(2,i); j++) {
			next_node = node;
			for (k = 0; k<pow(2,i); k++) {
				next_node = next_node->next[0];
			}
			node->next[i] = next_node;
			node = node->next[i];
		}
		
		// jump pow(2, i) nodes, then link the node to the next we are going to jump to.
	}
}

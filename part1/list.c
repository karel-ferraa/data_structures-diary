#include <list.h>
#include <stdlib.h>

// Create a new list
list *list_new(int maxlevel) {
    list *l = malloc(sizeof(list));
    l->head = NULL;
    l->maxLevel = maxlevel;
    return l;
}

// Free a list
void list_free(list *l) {
    cell *n = l->head;
    cell *to_free = NULL;
    int br = 0;
    while (n->next[0] != NULL){
        to_free = n;
        n = n->next[0];
        free(to_free);
    }
    free(l->maxlevel);
    free(n);
    free(l);
}

// Add a new element to the list
void addElement(list* l, int val){
    cell *new = malloc(sizeof(cell));
    new->val = val;
    new->next = malloc(sizeof(cell*) * MAX_LEVEL);
    for (int i=0; i<MAX_LEVEL; i++){
        new->next[i] = NULL;
    }
    cell *n = l->head;
    if (n == NULL){
        new->level=1;
        l->head = new;
        l->size = 1;
        return;
    }
    else{
        int level = l->size;
        new->level = level+1;
        for (int i=level; i>=0; i--){
            cell *n = l->head;
            for (int j=0; j<i; j++){
                n = n->next[j];
            }
        }

    }
}
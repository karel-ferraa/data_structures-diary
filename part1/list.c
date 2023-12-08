#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

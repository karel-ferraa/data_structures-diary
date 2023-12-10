#include "calendar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


calendarEntry* createCalendarEntry(contact c) {
    calendarEntry* ce = malloc(sizeof(calendarEntry));
    ce->c = c;
    ce->appointments = createList();
    return ce;
}

void printCalendarEntry(calendarEntry* ce) {
    printContact(&ce->c);
    displayList(ce->appointments);
}

char* getIdentifier(calendarEntry ce) {
    char* id = malloc(sizeof(char) * (strlen(ce.c.surname) + strlen(ce.c.firstName) + 2));
    for (int i = 0; i < strlen(ce.c.surname); i++) {
        id[i] = tolower(ce.c.surname[i]);
    }
    strcat(id, "_");
    for (int i = 0; i < strlen(ce.c.firstName); i++) {
        id[i + strlen(ce.c.surname) + 1] = tolower(ce.c.firstName[i]);
    }
    return id;
}

void freeCalendarEntry(calendarEntry* ce) {
    freeList(ce->appointments);
    free(ce);
}



void addAppointment(calendarEntry* ce, appointment* a){
    insertElement(ce->appointments, *a);
}

void removeAppointment(calendarEntry* ce, appointment* a){
    removeElement(ce->appointments, *a);
}

#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* scanString(void) {
    char* buffer = malloc(sizeof(char) * 100);
    scanf("%s", buffer);
    return buffer;
}

contact* createContact(char* surname, char* firstName) {
    contact* c = malloc(sizeof(contact));
    c->surname = malloc(sizeof(char) * (strlen(surname) + 1));
    strcpy(c->surname, surname);
    c->firstName = malloc(sizeof(char) * (strlen(firstName) + 1));
    strcpy(c->firstName, firstName);
    return c;
}

void printContact(contact* c) {
    printf("%s, %s\n", c->surname, c->firstName);
}

void freeContact(contact* c) {
    free(c->surname);
    free(c->firstName);
    free(c);
}

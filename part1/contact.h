#ifndef CONTACT_H
#define CONTACT_H

typedef struct s_contact {
    char* surname;
    char* firstName;
} contact;

char* scanString(void);

contact* createContact(char* surname, char* firstName);

void printContact(contact* c);

void freeContact(contact* c);

#endif 


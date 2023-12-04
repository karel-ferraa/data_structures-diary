#ifndef CALENDAR_H

#define CALENDAR_H
#include "contact.h"
#include "appointment.h"
#include "list.h"

typedef struct s_calendarEntry{
    contact c;
    list* appointments;
} calendarEntry;

calendarEntry* createCalendarEntry(contact c);

void addAppointment(calendarEntry* ce, appointment* a);

void removeAppointment(calendarEntry* ce, appointment* a);

void printCalendarEntry(calendarEntry* ce);

void freeCalendarEntry(calendarEntry* ce);

char* getIdentifier(calendarEntry ce);

#endif
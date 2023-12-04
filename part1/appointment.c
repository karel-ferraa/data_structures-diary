#include "appointment.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

appointment* createAppointment(int day, int month, int year, int hour, int minute, char* purpose) {
    appointment* a = malloc(sizeof(appointment));
    a->day = day;
    a->month = month;
    a->year = year;
    a->hour = hour;
    a->minute = minute;
    a->purpose = malloc(sizeof(char) * (strlen(purpose) + 1));
    strcpy(a->purpose, purpose);
    return a;
}

void printAppointment(appointment a) {
    printf("%d/%d/%d %d:%d - %s\n", a.day, a.month, a.year, a.hour, a.minute, a.purpose);
}

void freeAppointment(appointment* a) {
    free(a->purpose);
    free(a);
}

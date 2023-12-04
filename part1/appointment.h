#ifndef APPOINTMENT_H

#define APPOINTMENT_H

typedef struct appointment{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    char* purpose;
} appointment;

appointment* createAppointment(int day, int month, int year, int hour, int minute, char* purpose);

void printAppointment(appointment a);

void freeAppointment(appointment* a);

#endif
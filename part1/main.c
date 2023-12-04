#include "calendar.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int verifyDate(int day, int month, int year){
	if (year < 0){
		return 0;
	}
	if (month < 1 || month > 12){
		return 0;
	}
	if (day < 1){
		return 0;
	}
	if (month == 2){
		if (year % 4 == 0){
			if (day > 29){
				return 0;
			}
		} else {
			if (day > 28){
				return 0;
			}
		}
	} else if (month == 4 || month == 6 || month == 9 || month == 11){
		if (day > 30){
			return 0;
		}
	} else {
		if (day > 31){
			return 0;
		}
	}
	return 1;
}

int verifyHour(int hour, int minute){
	if (hour < 0 || hour > 23){
		return 0;
	}
	if (minute < 0 || minute > 59){
		return 0;
	}
	return 1;
}

int verifyAppointment(appointment a){
	return verifyDate(a.day, a.month, a.year) && verifyHour(a.hour, a.minute);
}

int verifyContact(contact c){
	if (strlen(c.firstName) == 0 || strlen(c.surname) == 0){
		return 0;
	}
	for (int i = 0; i < strlen(c.firstName); i++){
		if (!isalpha(c.firstName[i])){
			return 0;
		}
	}
	for (int i = 0; i < strlen(c.surname); i++){
		if (!isalpha(c.surname[i])){
			return 0;
		}
	}
	return 1;
}


	
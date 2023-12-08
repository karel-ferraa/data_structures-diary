#include "calendar.h"
#include "list.h"
#include "levellist.h"

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

int menu() {
	char choice = 'a';

	// 48 and 55 are ascii values for 0 and 7
	while (choice < 48 || choice > 55) {
		printf("Select the action to perform by typing in the corresponding number\n");
		printf("0. Quit the program");
		printf("1. Search for a contact\n");
		printf("2. View a contact's appointments\n");
		printf("3. Create a contact\n");
		printf("4. Create an appointment for a contact\n");
		printf("5. Delete an appointment\n");
		printf("6. Save the file of all appointments\n");
		printf("7. Load the file of all appointments\n");

		scanf("%c", &choice);
	}
	return choice;
}

int main() {
	int choice;
	while (choice != '0') {
		choice = menu();
		switch (choice) {
			case '1':
			{
					printf("Search is not yet implemented");
			}
			case '2':
			{
					printf("Viewing a contact's appointments is not yet implemented");
			}
			case '3':
			{
					printf("Creating a contact is not yet implemented");
			}
			case '4':
			{
					printf("Creating a appointment for a contact is not yet implemented");
			}
			case '5':
			{
					printf("Deleting an appointment is not yet implemented");
			}
			case '6':
			{
					printf("Saving the file of all appointments is not yet implemented");
			}
			case '7':
			{
					printf("Loading the file of all appointments is not yet implemented");
			}
		}
	}
}

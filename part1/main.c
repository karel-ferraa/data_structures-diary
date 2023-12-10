#include "calendar.h"
#include "list.h"
#include "levellist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

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
		printf("0. Quit the program\n");
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

void searchContact(level_list* main_list) {
	char surname[100];
	char firstName[100];
	printf("Enter the contact's surname\n");
	scanf("%s",&surname);
	printf("Enter the contact's firstname\n");
	scanf("%s",&firstName);
	contact* contact_to_search = createContact(surname, firstName);
	calendarEntry* ce_to_search = createCalendarEntry(*contact_to_search);
	level_cell* contact_cell = getElementPtrLevelList(*main_list, *ce_to_search);
	if (contact_cell != NULL) {
		printContact(&(contact_cell->val->c));
	} else {
		printf("The entered contact does not exist\n");
	}
	return;
}

void viewContactAppointments(level_list* main_list) {
	char surname[100];
	char firstName[100];
	printf("Enter the contact's surname\n");
	scanf("%s",&surname);
	printf("Enter the contact's firstname\n");
	scanf("%s",&firstName);
	contact* contact_to_search = createContact(surname, firstName);
	calendarEntry* ce_to_search = createCalendarEntry(*contact_to_search);
	level_cell* contact_cell = getElementPtrLevelList(*main_list, *ce_to_search);
	if (contact_cell != NULL) {
		assert(contact_cell->val->appointments != NULL);
		cell* curr_cell = contact_cell->val->appointments->head;
		while (curr_cell != NULL) {
			printAppointment(curr_cell->val);
			curr_cell = curr_cell->next;
		}
	} else {
		printf("The entered contact does not exist\n");
	}
	return;
}

void addNewContact(level_list* main_list) {
	char surname[100];
	char firstName[100];
	printf("Enter the contact's surname\n");
	scanf("%s",&surname);
	printf("Enter the contact's firstname\n");
	scanf("%s",&firstName);
	contact* new_contact = createContact(surname, firstName);
	// fgets adds a \n at the end of the buffer, which makes the verifyContact fail. We could use scanf instead of fgets, but that means we are assuming that people's names don't contain spaces in them which is bad. Actually, [you shouldn't assume anything about people's names](https://www.kalzumeus.com/2010/06/17/falsehoods-programmers-believe-about-names/)
	if (verifyContact(*new_contact) != 1) {
	    printf("Error: Contact surname and Firstname must contain only alphabetic characters and be non-empty, aborting\n");
	} else {
		calendarEntry* new_calendar_entry = createCalendarEntry(*new_contact);
		sortedInsertLevelList(main_list, *new_calendar_entry);
		printf("New contact added\n");
	}
	return;
}

void addNewAppointment(level_list* main_list) {
	char surname[100];
	char firstName[100];
	printf("Enter the contact's surname\n");
	scanf("%s",&surname);
	printf("Enter the contact's firstname\n");
	scanf("%s",&firstName);
	contact* contact_to_search = createContact(surname, firstName);
	calendarEntry* ce_to_search = createCalendarEntry(*contact_to_search);
	level_cell* contact_cell = getElementPtrLevelList(*main_list, *ce_to_search);
	if (contact_cell != NULL) {
		int year;
		int month;
		int day;
		int hour;
		int minute;
		char purpose[200];
		appointment* new_appointment;
		do
		{
			printf("Enter the year, month, day, hour and minute of the appointment under the form: year-month-day:hour:minute");
			scanf("%d-%d-%d:%d:%d", &year, &month, &day, &hour, &minute);
			printf("Enter the purpose of the appointment (max 200 characters)");
			fgets(purpose, 200, stdin);
			new_appointment = createAppointment(day, month, year, hour, minute, purpose);
		} while (!verifyAppointment(*new_appointment));
		insertElement(contact_cell->val->appointments, *new_appointment);
	} else {
		printf("The entered contact does not exist");
	}
	return;
}

void deleteAppointment(level_list* main_list) {
	__fpurge(stdin);
	char surname[100];
	char firstName[100];
	printf("Enter the contact's surname\n");
	fgets(surname, 100, stdin);
	printf("Enter the contact's firstname\n");
	fgets(firstName, 100, stdin);
	contact* contact_to_search = createContact(surname, firstName);
	calendarEntry* ce_to_search = createCalendarEntry(*contact_to_search);
	// right now the getElementPtr is O(n) complexity which is bad.
	level_cell* contact_cell = getElementPtrLevelList(*main_list, *ce_to_search);
	if (contact_cell != NULL) {
		int index; 
		do
		{
			printf("Enter the number of the appointment you want to delete\n");
			__fpurge(stdin);
			scanf("%d", &index);
		} while (index < 0 || index > listLength(*(contact_cell->val->appointments))); //index should start at one, otherwise put >=
		removeAtPos(contact_cell->val->appointments, index);
	} else {
		printf("The entered contact does not exist");
	}
	return;
}

void saveAppointmentFile() {
	printf("Saving the file of all appointments is not yet implemented");
	return;
}

void loadAppointmentFile() {
	printf("Loading the file of all appointments is not yet implemented");
	return;
}

int main() {
	level_list* main_list = createLevelList(4);
	// load all the contacts from the contact file
	// not yet implemented

	int choice;
	do
	{
		choice = menu();
		switch (choice) {
			case '1':
			{
				searchContact(main_list);
				break;
			}
			case '2':
			{
				viewContactAppointments(main_list);
				break;
			}
			case '3':
			{
				addNewContact(main_list);
				break;
			}
			case '4':
			{
				addNewAppointment(main_list);
				break;
			}
			case '5':
			{
				deleteAppointment(main_list);
				break;
			}
			case '6':
			{
				saveAppointmentFile();
				break;
			}
			case '7':
			{
				loadAppointmentFile();
				break;
			}
		}
	} while (choice != '0');
	freeLevelList(main_list);
}

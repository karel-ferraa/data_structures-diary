#include "list.h"
#include <stdio.h>

int main(){
	level_list* my_list;
	my_list = createLevelList(3);
	displayLevelledList(my_list);
	
	insertElementLevelList(my_list, 18);
	insertElementLevelList(my_list, 32);
	insertElementLevelList(my_list, 25);
	insertElementLevelList(my_list, 31);
	insertElementLevelList(my_list, 59);
	insertElementLevelList(my_list, 91);
	insertElementLevelList(my_list, 56);
	displayLevelledList(my_list);
	sortLevelList(my_list);
	balanceList(my_list);
	displayLevelledList(my_list);
	printf("Index of 18: %d\n", getElementIndexLevelList(*my_list, 18));
	printf("Index of 25: %d\n", getElementIndexLevelList(*my_list, 25));
	printf("Index of 31: %d\n", getElementIndexLevelList(*my_list, 31));
	printf("Index of 32: %d\n", getElementIndexLevelList(*my_list, 32));
	printf("Index of 56: %d\n", getElementIndexLevelList(*my_list, 56));
	printf("Index of 59: %d\n", getElementIndexLevelList(*my_list, 59));
	printf("Index of 91: %d\n", getElementIndexLevelList(*my_list, 91));
	printf("Index of 12: %d\n", getElementIndexLevelList(*my_list, 12));
	removeElementLevelList(my_list, 32);
	balanceList(my_list);
	displayLevelledList(my_list);
	return 0;
}

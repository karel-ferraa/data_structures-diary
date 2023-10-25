#include "list.h"

int main(){
	list* my_list;
	my_list = createList(3);
	displayLevelledList(my_list);
	
	insertElement(my_list, 18);
	insertElement(my_list, 32);
	insertElement(my_list, 25);
	insertElement(my_list, 31);
	insertElement(my_list, 59);
	insertElement(my_list, 91);
	insertElement(my_list, 56);
	displayLevelledList(my_list);
	sortList(my_list);
	balanceList(my_list);
	displayLevelledList(my_list);
	printf("Index of 25: %d\n", getElementIndex(*my_list, 25));
	return 0;
}

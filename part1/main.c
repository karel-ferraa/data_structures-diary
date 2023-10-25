#include "list.h"

int main(){
	list* my_list;
	my_list = createList(1);
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
	displayLevelledList(my_list);
	return 0;
}

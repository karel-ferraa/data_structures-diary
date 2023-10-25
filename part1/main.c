#include "list.h"

int main(){
	list* my_list;
	my_list = createList(1);
	displayLevelledList(my_list);
	
	sortedInsert(my_list, 18);
	sortedInsert(my_list, 32);
	sortedInsert(my_list, 25);
	sortedInsert(my_list, 31);
	sortedInsert(my_list, 59);
	sortedInsert(my_list, 91);
	sortedInsert(my_list, 56);
	displayLevelledList(my_list);

	return 0;
}

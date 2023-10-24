int main(){
	s_list list;
	list = createList(1);
	displayLevelledList(list);

	insertElement(list, 18);
	insertElement(list, 25);
	insertElement(list, 31);
	insertElement(list, 32);
	insertElement(list, 56);
	insertElement(list, 59);
	insertElement(list, 59);
	insertElement(list, 91);

	displayLevelledList(list);

	return 0;
}

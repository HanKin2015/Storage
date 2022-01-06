#include "list.h"

int main()
{
	
	list_t<int> *lst = list_t<int>::list_new();  // ´´½¨
	lst->push_back(1);
	lst->push_back(2);
	lst->push_back(5);
	printf("%d\n", lst->size());
	std::cout << lst->begin()->data << std::endl;
	std::cout << *(lst->begin()) << std::endl;
	std::cout << *lst << std::endl;

	iterator<int> it = lst->list_get(lst, 3);
	printf("%d\n", *it);

	lst->list_iter_insert_before(it, 4);
	lst->list_iter_insert_after(it, 6);
	it = lst->list_iter_forward(it);
	lst->list_iter_insert_before(it, 3);
	it = lst->list_iter_next(it);
	it = lst->list_iter_next(it);
	lst->list_iter_insert_after(it, 7);
	lst->list_iter_set(it, 23333);
	printf("%d\n", lst->size());

	lst->list_foreach(lst, list_t<int>::list_print, 0);

	it = lst->list_find(lst, list_t<int>::list_get, 4);
	printf("%d\n", *it);

	it = lst->begin();
	printf("head = %d\n", lst->list_iter_data(it));
	lst->list_free(lst);   // Çå¿Õ
	printf("%d\n", lst->size());
	system("pause");
	return 0;
}

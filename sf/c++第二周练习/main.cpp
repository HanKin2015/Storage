#include "list.h"

/*
zhangsan male 23 single programer false/true 50 basketball
*/

void TEST()
{
	list_t *lst = list_new();  // 创建列表
	lst->push_back("zhangsan", "string");
	lst->push_back("male", "string");
	lst->push_back("23", "int");
	lst->push_back("false", "bool");
	printf("lst's size = %d\n", lst->size());

	iterator it = lst->list_find(lst, list_t::list_get, 1);	// 通过回调查找
	printf("%s\n", *it);

	lst->list_foreach(lst, list_t::list_print, 1);	// 通过回调遍历列表

	it = list_t::list_get(lst, 4);	// 按索引值建立迭代器
	printf("value = %s\n", *it);
	lst->list_iter_insert_before(it, "programer");	// 在前一个位置插入
	lst->list_iter_insert_after(it, "50");	// 在后一个位置插入
	iterator it1 = lst->list_iter_forward(it);	// 后一个迭代器
	lst->list_iter_insert_before(it1, "single");
	iterator it2 = lst->list_iter_next(it);	// 前一个迭代器
	lst->list_iter_insert_after(it2, "basketball");
	list_iter_set(it, "true");	// 修改迭代器所指的值
	lst->list_foreach(lst, list_t::list_print, 1);
	printf("lst's size = %d\n", lst->size());

	printf("list_iter_data = %s\n", list_iter_data(it));	// 获取迭代器所指的值

	list_iter_clear(it);	// 清除迭代器
	list_free(lst);	// 清空列表

	printf("lst's size = %d\n", lst->size());
	return;
}

int main()
{
	TEST();
	system("pause");
	return 0;
}

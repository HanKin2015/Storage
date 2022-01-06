#include "list.h"

/*
zhangsan male 23 single programer false/true 50 basketball
*/

void TEST()
{
	list_t *lst = list_new();  // �����б�
	lst->push_back("zhangsan", "string");
	lst->push_back("male", "string");
	lst->push_back("23", "int");
	lst->push_back("false", "bool");
	printf("lst's size = %d\n", lst->size());

	iterator it = lst->list_find(lst, list_t::list_get, 1);	// ͨ���ص�����
	printf("%s\n", *it);

	lst->list_foreach(lst, list_t::list_print, 1);	// ͨ���ص������б�

	it = list_t::list_get(lst, 4);	// ������ֵ����������
	printf("value = %s\n", *it);
	lst->list_iter_insert_before(it, "programer");	// ��ǰһ��λ�ò���
	lst->list_iter_insert_after(it, "50");	// �ں�һ��λ�ò���
	iterator it1 = lst->list_iter_forward(it);	// ��һ��������
	lst->list_iter_insert_before(it1, "single");
	iterator it2 = lst->list_iter_next(it);	// ǰһ��������
	lst->list_iter_insert_after(it2, "basketball");
	list_iter_set(it, "true");	// �޸ĵ�������ָ��ֵ
	lst->list_foreach(lst, list_t::list_print, 1);
	printf("lst's size = %d\n", lst->size());

	printf("list_iter_data = %s\n", list_iter_data(it));	// ��ȡ��������ָ��ֵ

	list_iter_clear(it);	// ���������
	list_free(lst);	// ����б�

	printf("lst's size = %d\n", lst->size());
	return;
}

int main()
{
	TEST();
	system("pause");
	return 0;
}

#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	Twitter twitter = new Twitter();
	
	// �û�1������һ�������� (�û�id = 1, ����id = 5).
	twitter.postTweet(1, 5);
	
	// �û�1�Ļ�ȡ����Ӧ������һ���б����а���һ��idΪ5������.
	twitter.getNewsFeed(1);
	
	// �û�1��ע���û�2.
	twitter.follow(1, 2);
	
	// �û�2������һ�������� (����id = 6).
	twitter.postTweet(2, 6);
	
	// �û�1�Ļ�ȡ����Ӧ������һ���б����а����������ģ�id�ֱ�Ϊ -> [6, 5].
	// ����id6Ӧ��������id5֮ǰ����Ϊ������5֮���͵�.
	twitter.getNewsFeed(1);
	
	// �û�1ȡ����ע���û�2.
	twitter.unfollow(1, 2);
	
	// �û�1�Ļ�ȡ����Ӧ������һ���б����а���һ��idΪ5������.
	// ��Ϊ�û�1�Ѿ����ٹ�ע�û�2.
	twitter.getNewsFeed(1);

	return 0;
}
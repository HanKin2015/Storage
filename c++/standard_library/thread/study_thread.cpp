#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int var = 100;
void *tfn(void *arg)
{
	int i = *(int *)&arg;
	var = 200;
	if (i == 2) {
		pthread_exit(NULL);
	}
	sleep(i);        //通过i来区别每个线程
	printf("I'm %dth thread, Thread_ID = %lu\n", i+1, pthread_self());

	return NULL;
}

int main(int argc, char *argv[])
{
	int n = 1;
	if (argc == 2) {
		n = atoi(argv[1]);
	}

	printf("At first var = %d\n", var);

	pthread_t tid;
	for (int i = 0; i < n; i++) {
		pthread_create(&tid, NULL, tfn, (void *)(long)i);  //将i转换为指针，在tfn中再强转回整形。
	}

	sleep(n);
	printf("I am main, I'm a thread!\n" "main_thread_ID = %lu\n", pthread_self());
	printf("after pthread_create, var = %d\n", var);
	return 0;
}


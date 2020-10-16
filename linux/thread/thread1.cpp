#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
 
void *tfn(void *arg)
{
    int i = 0;
    if (arg != NULL) {
        i = *((int *)&arg);
    }
	sleep(i);	 //通过i来区别每个线程
	printf("I'm %dth thread, Thread_ID = %lu\n", i + 1, pthread_self());
	return NULL;
}
 
int main(int argc, char *argv[])
{
	pthread_t tid;
 
    int n = 1;
	if (argc == 2) {
		n = atoi(argv[1]);
    }
    
    for (int i = 0; i < n; i++) {
        //pthread_create(&tid, NULL, tfn, NULL);
        pthread_create(&tid, NULL, tfn, (void *)(long)i);
    }
    
	//pid_t pid = wait(NULL);
    //printf("pid = %d\n", pid);
	sleep(n);   // 在多线程环境中，父线程终止，全部子线程被迫终止
    printf("I am main, my pid = %d\n", getpid());
	printf("I am main, main_thread_ID = %lu\n", pthread_self());
	return 0;
}

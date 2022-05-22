#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <unistd.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int sem_id; // 信号量唯一标识

// 初始化信号量
// int semctl(int sem_id, int sem_num, int command, [union semun sem_union]);
int init_semvalue()
{
	union semun sem_union;    
	sem_union.val = 1;	// 要传给信号量的初始值
	// 第二个参数除非使用一组信号量，否则它为0
	if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
		printf("init semvalue failed!\n");
		return 0;
	}
	printf("init semvalue success!\n");
	return 1;
}

// 修改信号量的值,等待操作
// int semop(int sem_id, struct sembuf *sem_opa, size_t num_sem_ops);
int semaphore_p()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;	// 除非使用一组信号量，否则它为0
	sem_b.sem_op = -1;	// 通常是两个数，一个是-1，即P（等待）操作，一个是+1，即V（发送信号）操作。 
	sem_b.sem_flg = SEM_UNDO;	// 通常为SEM_UNDO,使操作系统跟踪信号
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_p failed\n");
		return 0;
	}
	printf("semaphore_p success!\n");
	return 1;
}

// 修改信号量的值,发送信号操作
int semaphore_v()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1)	{
		fprintf(stderr,"semaphore_v failed\n");
		return 0;
	}
	printf("semaphore_v success!\n");
	return 1;
}

// 删除信号量
void del_semvalue()
{
	union semun sem_union;
	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1) {
		fprintf(stderr, "Failed to delete semaphore\n");
	} else {
		printf("delete semaphore success!\n");
	}
	return;
}

int main(int argc,char *argv[])
{
	char message = 'x';
	//创建信号量
	sem_id = semget((key_t)1234, 1, 0666|IPC_CREAT);
	if (argc > 1) {
		//初始化信号量
		if (!init_semvalue()) {
			fprintf(stderr,"init failed\n");
			exit(EXIT_FAILURE);
		}
		//参数的第一个字符赋给message
		message = argv[1][0];
	}
	int i=0;
	for (i=0; i<5; i++) {
		//等待信号量
		if (!semaphore_p()) {
			exit(EXIT_FAILURE);
		}
		printf("message -> %c\n", message);
		fflush(stdout);
		sleep(1);
		//发送信号量
		if (!semaphore_v()) {
			exit(EXIT_FAILURE);
		}
		sleep(1);
	}
	printf("\npid: %d finished!\n", getpid());
	if (argc > 1) {
		//退出前删除信号量
		del_semvalue();
	}
	exit(EXIT_SUCCESS);
	return 0;
}

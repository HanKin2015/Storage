/**
* 文 件 名: barrier.cpp
* 文件描述: https://blog.csdn.net/u013836909/article/details/120917553
* 作    者: HanKin
* 创建日期: 2022.12.16
* 修改日期：2022.12.16
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <string.h>
#define __USE_GNU 
#include <sched.h> 
#include <pthread.h>
static uint8_t fifo_buffer[4096]; 
static uint32_t fifo_total; 
static uint32_t fifo_free; 
static uint32_t read_index; 
static uint32_t write_index;
static pthread_mutex_t mutex; 
static pthread_cond_t cond_not_empty; 
static pthread_cond_t cond_not_full;
static uint32_t write_count = 0;

static int fifo_init(void) 
{    
	fifo_total = sizeof(fifo_buffer);    
	fifo_free = fifo_total;   
	memset(fifo_buffer, 0, fifo_total);   
	read_index = write_index = 0;
	pthread_mutex_init(&mutex, NULL);    
	pthread_cond_init(&cond_not_empty, NULL);    
	pthread_cond_init(&cond_not_full, NULL); 
}

static void* reader(void *arg)
{    
	uint32_t read_data = 0;    
	uint32_t read_count = 0;    
	uint32_t error_count = 0;    
	uint32_t count = 0;    
	uint32_t *pread = NULL;
	 // 设置线程亲和CPU0    
	cpu_set_t mask;    
	CPU_ZERO(&mask);    
	CPU_SET(0, &mask);    
	if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {        
		perror("pthread_setaffinity_np");    
	}
			
	while (1) {        
		pthread_mutex_lock(&mutex);        
		if (fifo_free == fifo_total) {            
			pthread_cond_wait(&cond_not_empty, &mutex);        
		}

		pread = (uint32_t *)(fifo_buffer + read_index);

		// 判断可读标志        
		count = 0;        
		while (1) {            
			if (*pread == 1) {                
				break;            
		}            
		usleep(1000);            

		count++;            
		if (count >= 1000) {
			count = 0;                
			printf("wait date readable\n");            
		}        
	}

		
		read_data = *(pread + 1);        
		read_count++;        
		if (read_count != read_data) {            
			printf("read data error: count=%u data=%u\n", read_count, read_data);            
			error_count++;
			// 出错后，sleep后可以读到正确写入的值，可以证明是CPU乱序执行导致前面出错            
			usleep(10000);            
			read_data = *(pread + 1);            
			printf(" re-read data: %u\n", read_data);        
		}
		
		read_index += 8;        
		read_index %= fifo_total;        
		fifo_free += 8;
		if (read_count % 10000 == 0) {            
			printf("read data: %u, error count: %u\n", read_count, error_count);      
		}
		
		pthread_mutex_unlock(&mutex);       
		pthread_cond_signal(&cond_not_full);   
	} 
}


static void* writer(void *arg) 
{    
	uint32_t write_data = 0;    
	uint32_t *pwrite = NULL;

	// 设置线程亲和除CPU0之外的其他CPU    
	cpu_set_t mask;    
	if (pthread_getaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {        
		perror("pthread_getaffinity_np");    }    
		CPU_CLR(0, &mask);    

	if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {        
		perror("pthread_setaffinity_np");    
	}
	
	while (1) {        
		pthread_mutex_lock(&mutex);        
		if (fifo_free == 0) {            
			pthread_cond_wait(&cond_not_full, &mutex);        
		}
		
		pwrite = (uint32_t *)(fifo_buffer + write_index);        
		*pwrite = 0;
		write_count++;       
		write_data = write_count;
		write_index += 8;        
		write_index %= fifo_total;       
		fifo_free -= 8;
		
		pthread_mutex_unlock(&mutex);        
		pthread_cond_signal(&cond_not_empty);

		// 如果没有加内存屏障，可能出现CPU乱序执行，即先赋值可读标志，再写数据        
		*(pwrite + 1) = write_data;   // 写入数据        
		__sync_synchronize();        
		*pwrite = 1;                  // 写入可读标志

		// 把互斥锁加在这里也可以解决        
		//pthread_cond_signal(&cond_not_empty);        
		//pthread_mutex_unlock(&mutex);
		usleep(1000);    
	} 
}

int main(int argc, char *argv[]) 
{    
	int ret, i;    
	int writers = 4;   
	pthread_t thread_handle;
	printf("barrier test\n");
	ret = fifo_init();    
	if (ret) {        
		printf("create thread reader ERROR!\n");        
		return -1;    
	}
	
	pthread_attr_t attr;    
	struct sched_param param;    
	pthread_attr_init(&attr);    
	pthread_attr_setschedpolicy(&attr, SCHED_RR);    
	param.__sched_priority = 11;    
	pthread_attr_setschedparam(&attr, &param);    
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);    
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);    
	
	ret = pthread_create(&thread_handle, &attr, reader, NULL);    
	if (ret) {        
		printf("create thread reader ERROR!\n");        
		return -1;    
	}    
	
	pthread_attr_destroy(&attr);
	for (i = 0; i < writers; i++) {        
		ret = pthread_create(&thread_handle, NULL, writer, NULL);        
		if (ret) {            
			printf("create thread reader ERROR!\n");           
	 		return -1;        
		}    
	}
 
	while (1) {        
		sleep(60);    
	}
 
	return 0; 
}

/* 实现的最简单的ringbuff 有更多提升空间，可以留言说明 */
#include "stdio.h"
#include "stdlib.h"

#define LEN 64

/*环形队列结构体*/
typedef struct ring_buff{
	int array[LEN];
	int W;
	int R;
}*ring;

/*环形队列初始化*/
struct ring_buff * fifo_init(void)
{
	struct ring_buff * p = NULL;
	p = (struct ring_buff *)malloc(sizeof(struct ring_buff));
	if(p == NULL)
	{
	   printf("fifo_init malloc error\n");
	   return NULL;
	}
	p->W = 0;
	p->R = 0;
	return p;
}

/*判断环形队列是否已经满了*/
int get_ring_buff_fullstate(struct ring_buff * p_ring_buff)
{
	/*如果写位置减去读位置等于队列长度，就说明这个环形队列已经满*/
	if((p_ring_buff->W - p_ring_buff->R) == LEN)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*判断环形队列为空*/
int get_ring_buff_emptystate(struct ring_buff * p_ring_buff)
{
	/*如果写位置和读的位置相等，就说明这个环形队列为空*/
	if(p_ring_buff->W == p_ring_buff->R)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*插入数据*/
int ring_buff_insert(struct ring_buff * p_ring_buff,int data)
{
	if(p_ring_buff == NULL)
	{
	   printf("p null\n");
	   return (-1);	
	}
	
	if(get_ring_buff_fullstate(p_ring_buff) == 1)
	{
		printf("buff is full\n");
		return (-2);
	}
	
	//p_ring_buff->array[p_ring_buff->W%LEN] = data;
	p_ring_buff->array[p_ring_buff->W&(LEN -1)] = data;	
	p_ring_buff->W ++;
	//printf("inset:%d %d\n",data,p_ring_buff->W);
	return (0);
}

/*读取环形队列数据*/
int ring_buff_get(struct ring_buff * p_ring_buff)
{
	int data = 0;
	
	if(p_ring_buff == NULL)
	{
	   printf("p null\n");
	   return (-1);	
	}
	
	if(get_ring_buff_emptystate(p_ring_buff) == 1)
	{
		printf("buff is empty\n");
		return (-2);
	}
	
	//data = p_ring_buff->array[p_ring_buff->R%LEN];
	data = p_ring_buff->array[p_ring_buff->R&(LEN -1)];
	p_ring_buff->R++;
	return data;
}

/*销毁*/
int ring_buff_destory(struct ring_buff * p_ring_buff)
{
	if(p_ring_buff == NULL)
	{
	   printf("p null\n");
	   return (-1);	
	}
	
	free(p_ring_buff);
	
	return (0);
}

int main()
{
	int i = 0;
	
	/*定义一个环形缓冲区*/
	ring pt_ring_buff = fifo_init();
	
	/*向环形缓冲区中写入数据*/
	for(i = 0;i<10;i++)
	{
		ring_buff_insert(pt_ring_buff,i);
	}
	
	/*从环形缓冲区中读出数据*/
	for(i = 0;i<10;i++)
	{
		printf("%d ",ring_buff_get(pt_ring_buff));
	}
	
	/*销毁一个环形缓冲区*/
	ring_buff_destory(pt_ring_buff);
	
	return (1);
}
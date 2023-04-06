//
//  dequeue.c
//  230406 datastructrues quiz meeting
//
//  Created by 한설 on 2023/04/06.
//

#include "queue.h"

void error(char str[])
{
    printf("%s", str);
    exit(1);
}

void init_queue(void) {front = rear = 0;}
int get_front(void) {return data[front];}
int is_empty(void) {return front == rear;}
int is_full(void) {return front == (rear - 1) % MAX_QUEUE_SIZE;}
void enqueue(int x);
int dequeue(void);

void enqueue(int x)
{
    if (is_full())
        error("큐 포화 에러");
    data[rear] = x;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
}

int dequeue(void)
{
    if (is_empty())
        error("큐 공백 에러");
    int res;
    res = data[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    return res;
}

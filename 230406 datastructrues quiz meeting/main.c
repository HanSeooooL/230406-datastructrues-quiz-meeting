//
//  main.c
//  230406 datastructrues quiz meeting
//
//  Created by 한설 on 2023/04/06.
//

//#include "queue.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#define MAX_QUEUE_SIZE 100
int front, rear;
Element data[MAX_QUEUE_SIZE] = { 0 };

void error(char str[]);
void init_queue(void);
int get_front(void);
int is_empty(void);
int is_full(void);
void enqueue(int x);
int dequeue(void);
void print_queue(void);

void error(char str[])
{
    printf("%s", str);
    exit(1);
}

void init_queue(void) {front = rear = 0;}
int is_empty(void) {return front == rear;}
int is_full(void) {return front == (rear - 1) % MAX_QUEUE_SIZE;}    //에러 수정해야함

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

int get_front(void)
{
    if (is_empty())
        error("큐 공백 에러");
    return data[front];
}
void print_queue(void)
{
    if(is_empty())
        error("큐 공백 에러");
    
    for(int i = front; i < rear; i++)
        printf("%d", data[i]);
}

int main(int argc, const char * argv[]) {
    
    int a;
    init_queue();
    for(int i = 0; i < 10; i++)
    {
        srand(time(NULL));
        a = rand() % 30;
        enqueue(a);
    }
    printf("front : %d  rear : %d", front, rear);
    printf("\n");
    print_queue();
}


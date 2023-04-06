//
//  main.c
//  230406 datastructrues quiz meeting
//
//  Created by 한설 on 2023/04/06.
//

#include <stdio.h>
#include <stdlib.h>

void error(char str[])
{
    printf("%s", str);
    exit(1);
}


typedef int Element;
#define MAX_QUEUE_SIZE 100
int front, rear;

Element data[MAX_QUEUE_SIZE] = { 0 };

void init_queue(void) {front = rear = 0;}
int get_front(void) {return data[front];}
int is_empty(void) {return front == rear;}
int is_full(void) {return front == (rear - 1) % MAX_QUEUE_SIZE;}


int enqueue(int x)
{
    
    data[rear] = x;
    rear = (rear + 1)
}

int main(int argc, const char * argv[]) {
    return 0;
}

//
//  main.c
//  230406 datastructrues quiz meeting
//
//  Created by 한설 on 2023/04/06.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void init_queue(void) {front = rear = 0;}
int get_front(void) {return data[front];}
int is_empty(void) {return front == rear;}
int is_full(void) {return front == (rear - 1) % MAX_QUEUE_SIZE;}
void enqueue(int x);
int dequeue(void);

int main(int argc, const char * argv[]) {
    return 0;
}

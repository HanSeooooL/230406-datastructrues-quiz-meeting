//
//  dequeue.h
//  230406 datastructrues quiz meeting
//
//  Created by 한설 on 2023/04/06.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct person {
    int gender;
    char name;
} Element;
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

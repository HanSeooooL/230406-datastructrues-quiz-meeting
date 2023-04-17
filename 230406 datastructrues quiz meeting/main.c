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
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef char Element;

typedef struct Queuee { //사람 정보 저장 구조체
    Element data[MAX_QUEUE_SIZE][80];
    int front;
    int rear;
} Queue;

//큐 추상자료형
void error(char str[]);
void init_queue(Queue *a);
Element get_front(Queue *a);
int is_empty(Queue *a);
int is_full(Queue *a);
void enqueue(Queue *a, Element *x);
Element dequeue(Queue *a);
void print_queue(Queue *a, char *str);

//시뮬레이션 추상자료형
void read_sim_params(void);
double rand0to1(void) { return rand() / (double)RAND_MAX;}
void run_simulation(void);
void insert_customer(void);
//void get_person(Queue *person);


int nSimulation;
double probArrival;

int main(int argc, const char * argv[]) {
    
    srand((unsigned)time(NULL));
    return 0;
}

void insert_customer(void) {
    int gender;
    gender = rand() % 2; //0이 나오면 여자 1이 나오면 남자
    
}

void run_simulation(void)
{
    
}

void read_sim_params(void)
{
    printf("시뮬레이션 할 최대 시간(예: 10) : ");
    scanf("%d", &nSimulation);
    printf("단위시간에 도착하는 고객 수 (예: 0.5) :");
    scanf("%lf", &probArrival);
}

void error(char str[])
{
    printf("%s", str);
    exit(1);
}

void init_queue(Queue *a) {a -> front = a -> rear = 0;}
int is_empty(Queue *a) {return a -> front == (a -> rear);}
int is_full(Queue *a) {return a -> front == (a -> rear + 1) % MAX_QUEUE_SIZE;}

void enqueue(Queue *a, Element *x)
{
    if (is_full(a))
        error("큐 포화 에러");
    strcpy(a -> data[a -> rear], x);
    a -> rear = (a -> rear + 1) % MAX_QUEUE_SIZE;
}

Element dequeue(Queue *a)
{
    if (is_empty(a))
        error("큐 공백 에러");
    Element res[80];
    strcpy(res, a -> data[a -> front]);
    a -> front = (a -> front + 1) % MAX_QUEUE_SIZE;
    return *res;
}

Element get_front(Queue *a)
{
    if (is_empty(a))
        error("큐 공백 에러");
    return *(a -> data[a -> front]);
}
void print_queue(Queue *a, char *str)
{
    if(is_empty(a))
        error("큐 공백 에러");
    printf("%s", str);
    
    for(int i = a -> front; i < a -> rear; i++)
        printf("%s", a -> data[i]);
    printf("\n");
}
/*
 void get_person(Queue *person)
 {
 int gender = 0, n;
 char name[80];
 printf("몇명 입력하시겠습니까? ");
 scanf("%d", &n);
 for (int i = 0; i < n; i++) {
 printf("남자면 1 여자면 0을 입력해주세요. ");
 scanf("%d", &gender);
 printf("이름을 입력해주세요. ");
 scanf("%s", name);
 enqueue(&person[gender], name);
 }
 }
 */

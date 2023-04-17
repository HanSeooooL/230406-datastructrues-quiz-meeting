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

typedef struct Element
{
    char name[80];
    int arrival;
}Element;   //data배열 저장되는 자료형 문자형태

typedef struct Queuee { //사람 정보 저장 구조체
    Element data[MAX_QUEUE_SIZE];   //문자열이므로 2차원배열 선언
    int front;  //앞
    int rear;   //뒤
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
int size(Queue *a);

//시뮬레이션 추상자료형
void read_sim_params(void); //파라마터 입력받는 함수
double rand0to1(void) { return rand() / (double)RAND_MAX;}
void run_simulation(void);
void insert_customer(Queue *person, int arrival);    //사람 넣기
void print_sim(Queue *person);


int nSimulation;    //시뮬레이션 시간
double probArrival; //단위시간에 도착하는 평균 고객 수
int acceptcouble;   //성립된 커플 수
int malewait; //남자가 기다린 시간 합
int femalewait; //여자가 기다린 시간 합

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    read_sim_params();
    run_simulation();
    return 0;
}

void insert_customer(Queue *person, int arrival) {
    Element a;
    char male[10][80] = {
        "광수", "성현", "범태", "가온", "가람", "기윤", "희찬", "해동", "태승", "박신"
    };
    char female[10][80] = {
        "시은", "지안", "리안", "진희", "시온", "하진", "채원", "다인", "하진", "다민"
    };
    int gender;
    a.arrival = arrival;
    gender = rand() % 2; //0이 나오면 여자 1이 나오면 남자
    if (gender == 0) {  //여자일 때
        printf("여학생 등록: ");
        strcpy(a.name, female[rand() % 10]);
        printf("%s", a.name);
        enqueue((person + 0), &a);
    }
    
    else if(gender == 1) {  //남자일 때
        printf("남학생 등록: ");
        strcpy(a.name, male[rand() % 10]);
        printf("%s", a.name);
        enqueue((person + 1), &a);
    }
    
}

void run_simulation(void)
{
    Queue person[2];
    int clock;
    clock = 0;
    
    init_queue(&person[0]);
    init_queue(&person[1]);
    
    while(clock < nSimulation)
    {
        Element boy, girl;
        clock++;
        printf("\n[ %d]: ", clock);
        
        if(rand0to1() < probArrival)
            insert_customer(person, clock);
        
        if(is_empty(&person[0]) == 0 && is_empty(&person[1]) == 0)
        {
            girl = dequeue(&person[0]);
            boy = dequeue(&person[1]);
            femalewait = femalewait + (clock - girl.arrival);
            malewait = malewait + (clock - boy.arrival);
            printf("  ===> 커플탄생! %s and %s  (%d, %d 기다림)", boy.name, girl.name, clock - boy.arrival, clock - girl.arrival);
            acceptcouble += 1;
        }
    }
    print_sim(person);
        
}

void read_sim_params(void)
{
    printf("시뮬레이션 할 최대 시간(예: 10) : ");
    scanf("%d", &nSimulation);
    printf("단위시간에 도착하는 고객 수 (예: 0.5) :");
    scanf("%lf", &probArrival);
}

void print_sim(Queue *person)
{
    printf("\n========================================");
    printf("\n성립된 커플의 수 %d", acceptcouble);
    printf("\n현재 대기 남학생 수 %d", size(&person[1]));
    printf("\n현재 대기 여학생 수 %d", size(&person[0]));
    printf("\n전체 남학생 대기시간 %d", malewait);
    printf("\n전체 여학생 대기시간 %d", femalewait);
    printf("\n남학생 평균 대기시간 %.2lf", (double)malewait / (double)acceptcouble);
    printf("\n여학생 평균 대기시간 %.2lf", (double)femalewait / (double)acceptcouble);
}

void error(char str[])
{
    printf("%s", str);
    exit(1);
}

void init_queue(Queue *a) {a -> front = a -> rear = 0;}
int is_empty(Queue *a) {return a -> front == (a -> rear);}
int is_full(Queue *a) {return a -> front == (a -> rear + 1) % MAX_QUEUE_SIZE;}
int size(Queue *a) { return (a -> rear - a -> front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;}

void enqueue(Queue *a, Element *x)
{
    if (is_full(a))
        error("큐 포화 에러");
    a -> data[a -> rear] = *x;
    a -> rear = (a -> rear + 1) % MAX_QUEUE_SIZE;
}

Element dequeue(Queue *a)
{
    if (is_empty(a))
        error("큐 공백 에러");
    Element res;
    res = a -> data[a -> front];
    a -> front = (a -> front + 1) % MAX_QUEUE_SIZE;
    return res;
}

Element get_front(Queue *a)
{
    if (is_empty(a))
        error("큐 공백 에러");
    return a -> data[a -> front];
}
void print_queue(Queue *a, char *str)
{
    if(is_empty(a))
        error("큐 공백 에러");
    printf("%s", str);
    
    for(int i = a -> front; i < a -> rear; i++) {
        printf("%s ", a -> data[i].name);
        printf("%d\n", a -> data[i].arrival);
    }
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

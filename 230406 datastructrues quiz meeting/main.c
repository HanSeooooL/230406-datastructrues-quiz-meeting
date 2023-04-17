//
//  main.c
//  230406 datastructrues quiz meeting
//
//  Created by 한설 on 2023/04/06.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef struct Element { //큐 배열에 저장되는 구조체

    char name[80];  //이름 저장
    int arrival;    //도착시간 저장
}Element;

typedef struct Queuee { //사람 정보 저장 구조체
    Element data[MAX_QUEUE_SIZE];   //문자열이므로 2차원배열 선언
    int front;  //앞
    int rear;   //뒤
} Queue;

//큐 추상자료형
void error(char str[]);
void init_queue(Queue *a);  //큐 초기화
Element get_front(Queue *a);    //가장 앞 원소 출력
int is_empty(Queue *a); //공백확인
int is_full(Queue *a);  //포화 확인
void enqueue(Queue *a, Element *x); //큐에 집어넣기
Element dequeue(Queue *a);  //가장 앞 원소 출력 및 삭제
void print_queue(Queue *a, char *str);  //큐 전체원소 출력
int size(Queue *a); //큐 사이즈 출력

//시뮬레이션 추상자료형
void read_sim_params(void); //파라마터 입력받는 함수
double rand0to1(void) { return rand() / (double)RAND_MAX;}  //RAND_MAX -> rand() 출력될 수 있는 최댓값. rand() / RAND_MAX를 하게되면, 무조건 rand()는 RAND_MAX보다 작은 수가 나오므로 0과 1 사이의 값이 나온다.
void run_simulation(void);  //시뮬레이션 돌리는 함수
void insert_customer(Queue *person, int arrival);    //사람 넣기
void print_sim(Queue *person);  //시뮬레이션 결과 출력

//시뮬레이션에 관련한 전역변수
int nSimulation;    //시뮬레이션 시간
double probArrival; //단위시간에 도착하는 평균 고객 수
int acceptcouble;   //성립된 커플 수
int malewait; //남자가 기다린 시간 합
int femalewait; //여자가 기다린 시간 합

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));    //난수 초기화
    read_sim_params();
    run_simulation();
    return 0;
}

void run_simulation(void)
{
    Queue person[2];
    int clock;
    clock = 0;
    
    init_queue(&person[0]); //여자 큐 초기화
    init_queue(&person[1]); //남자 큐 초기화
    
    while(clock < nSimulation)
    {
        Element boy, girl;  //남자 여자 저장 구조체 생성
        clock++;    //시간 + 1
        printf("\n[ %d]: ", clock);
        
        if(rand0to1() < probArrival)    //단위시간이 0과 1 사이 난수보다 큰 경우
            insert_customer(person, clock); //학생 한명 큐 저장
        
        if(is_empty(&person[0]) == 0 && is_empty(&person[1]) == 0)  //만약에 남자큐와 여자큐 둘다 최소 한명씩 있다면
        {
            girl = dequeue(&person[0]); //여자 저장 구조체에 여자 큐의 가장 앞 원소 출력 및 큐에서 삭제
            boy = dequeue(&person[1]);  //남자 저장 구조체에 남자 큐의 가장 앞 원소 출력 및 큐에서 삭제
            femalewait = femalewait + (clock - girl.arrival);   //여자 총 대기시간에 지금 매칭된 여자 대기시간 더하기
            malewait = malewait + (clock - boy.arrival);        //남자 총 대기시간에 지금 매칭된 남자 대기시간 더하기
            printf("  ===> 커플탄생! %s and %s  (%d, %d 기다림)", boy.name, girl.name, clock - boy.arrival, clock - girl.arrival); //콘솔 출력
            acceptcouble += 1;  //커플성립횟수 +1
        }
    }
    print_sim(person);  //시뮬레이션 결과 출력
        
}

void insert_customer(Queue *person, int arrival) {
    Element a;
    char male[10][80] = {   //남학생 이름 배열에 저장
        "광수", "성현", "범태", "가온", "가람", "기윤", "희찬", "해동", "태승", "박신"
    };
    char female[10][80] = { //여학생 이름 배열에 저장
        "시은", "지안", "리안", "진희", "시온", "하진", "채원", "다인", "하진", "다민"
    };
    int gender; //성별
    a.arrival = arrival;    //도착시간
    gender = rand() % 2; //0이 나오면 여자 1이 나오면 남자
    if (gender == 0) {  //여자일 때
        printf("여학생 등록: ");
        strcpy(a.name, female[rand() % 10]);    //여학생 이름이 저장된 배열에서 랜덤하게 하나 복사
        printf("%s", a.name);
        enqueue((person + 0), &a);
    }
    
    else if(gender == 1) {  //남자일 때
        printf("남학생 등록: ");
        strcpy(a.name, male[rand() % 10]);  //남학생 이름이 저장된 배열에서 랜덤하게 하나 복사
        printf("%s", a.name);
        enqueue((person + 1), &a);
    }
    
}

void read_sim_params(void)  //시뮬레이션 파라미터 입력s
{
    printf("시뮬레이션 할 최대 시간(예: 10) : ");
    scanf("%d", &nSimulation);
    printf("단위시간에 도착하는 고객 수 (예: 0.5) :");
    scanf("%lf", &probArrival);
}

void print_sim(Queue *person)   //시뮬레이션 결과출력
{
    printf("\n========================================");
    printf("\n성립된 커플의 수 %d", acceptcouble);
    printf("\n현재 대기 남학생 수 %d", size(&person[1]));
    printf("\n현재 대기 여학생 수 %d", size(&person[0]));
    printf("\n전체 남학생 대기시간 %d", malewait);
    printf("\n전체 여학생 대기시간 %d", femalewait);
    printf("\n남학생 평균 대기시간 %.2lf", malewait / (double)acceptcouble);
    printf("\n여학생 평균 대기시간 %.2lf", femalewait / (double)acceptcouble);
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

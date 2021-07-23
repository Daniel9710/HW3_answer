# HW3: Scheduling Algorithm 구현 실습

scheduling algorithm을 구현하면서, scheduler가 host와 cpu 사이에서 어떤 작업을 수행하는지 이해하고 각 scheduling algorithm 간의 특징과 차이점에 대해 생각해보자.


------------

## 파일 구성
> __src__ : 기본 구현에 필요한 파일들을 모아둔 디렉터리 (참고용)
> 
>> __cpu.h__, __cpu.c__ : cpu 모듈 관련 구현 파일
>> 
>> __host.h__, __host.c__ : host 모듈 관련 구현 파일
>> 
>> __process.h__ : process 구조체 관련 정의 파일
>> 
>> __parser.h__, __parser.c__ : parser 모듈 관련 구현 파일 (실행 파일 실행시 인자 parsing)
>> 
>> __util.h__, __util.c__ : 구현 관련해 사용할 함수 구현 파일
>> 
>> __defs.h__ : 구현 관련해 사용할 정의 구현 파일
>> 
> __traces__ : 시뮬레이션을 진행할 process들을 명세한 파일들을 모아둔 디렉터리
>
> __*.o__ : src에 모아둔 파일들을 object 파일로 미리 컴파일해둔 파일들 (make 사용시 이 파일들을 이용해 컴파일 진행됨)
>
> __scheduler.c__ : scheduler 모듈 관련 구현 파일 __(중점적으로 구현해야할 파일)__ 
> 
> __Makefile__ : 컴파일의 편의를 위해 만든 Makefile
> 
> __scheduler_ans__ : scheduler 모듈 답안 실행파일 __(이 파일의 동작과 똑같이 결과가 나오면 됨)__


------------

## trace 파일 구성

> 0 번째 줄: 총 create될 process의 개수 (N)
> 
> 1~N 번째 줄: 각 process의 도착 시간(시간 순, 동시 도착하는 경우 x), CPU를 사용하는 시간, 우선 순위(0 ~ 3)
> ~~~C
> 3 //create될 process의 개수 = 3
> 2 4 0 //2cycle에 도착, processing에 4cycle이 필요함, 우선순위는 0 (
> 5 2 2
> 8 5 2 
> ~~~

------------

## 주요 함수 (src에서의 함수는 이거만 사용해서 구현하도록)
### Create process
> ~~~C
> /* create_if_next_process_available
> // : host로부터 해당 time에 create된 process가 있는지 알 수 있음. 매 cycle이 시작될 때마다 호출됨
> // parameter: x
> // return: 해당 time에 create된 process가 있을 경우 생성된 process의 pointer
> //         없을 경우 NULL
> */
> Proc* create_if_next_process_available();
> ~~~

### Check CPU busy
> ~~~C
> /* is_cpu_busy
> // : cpu에 현재 schedule된 process가 있는지 알 수 있는 함수
> // parameter: x
> // return: 있을 경우 참(1), 없을 경우 거짓(0)
> */
> bool is_cpu_busy();
> ~~~

### Schedule to CPU
> ~~~C
> /* schedule_cpu
> // : cpu에 파라미터로 전달하는 process를 schedule요청할 때 사용하는 함수
> // parameter: schedule하고자 하는 process의 포인터
> // return: x
> */
> void schedule_cpu(Proc* process);
> ~~~

### Run CPU
> ~~~C
> /* run_cpu
> // : cpu가 한 cycle을 소화하도록 하는 함수 (매 cycle마다 실행되어야 함)
> // parameter: x
> // return: 현재 cycle에 만약 schedule되어있는 process가 있고 그 process가 사용해야할 또는 사용해야할 cycle을 모두 사용한 경우 참(1)
> //         아니면 거짓(0)
> */
> bool run_cpu();
> ~~~

### Unschedule from CPU
> ~~~C
> /* unschedule_cpu
> // : cpu에 현재 schedule되어 있는 process를 unschedule하고 싶을 때 사용하는 함수
> // parameter: x
> // return: unschedule한 process의 pointer      
> */
> Proc* unschedule_cpu();
> ~~~

### Terminate process  
> ~~~C
> /* terminate_process
> // : process를 terminate시키고 싶을 때 호출하는 함수.
> // parameter: terminate시키고 싶은 process의 pointer
> // return: x
> */
> void terminate_process(Proc* candidate_process);
> ~~~

### Get current time
> ~~~C
> /* get_current_time
> // : 현재 시간에 대해 얻을 수 있는 함수
> // parameter: x
> // return: 현재 시간
> */
> unsigned int get_current_time();
> ~~~
 
 
------------
 
## 구현 방법
### scheduler.c에 각 scheduling algorithm (FIFO, SJF, RoudRobin, MFLQ, Guarantee)를 구현한다.
> - 각 scheduling algorithm을 위해 필요한 데이터(ex. 큐)들을 저장하고 사용할 구조체 작성
>> ![struct](https://user-images.githubusercontent.com/44739822/125669568-935db2c1-7ac1-4f60-b2e1-68b1febd59ae.PNG)
> - 각 scheduling algorithm에 대해 시뮬레이션 시작 전에 해야할 initial 작업 구현
>> ![init](https://user-images.githubusercontent.com/44739822/125669561-8b7555ed-4c9a-49f9-9658-900e369fe137.PNG)  
> - 각 scheduling algorithm에 대해 한 cycle마다 수행할 작업 구현
>> ![simulate](https://user-images.githubusercontent.com/44739822/125669567-6ddd0301-8686-4e40-bd17-beddb0157cbc.PNG)
> - 각 scheduling algorithm에 대해 시뮬레이션이 끝나고 해야할 작업 (ex. 동적할당 해제) 작업 구현
>> ![terminate](https://user-images.githubusercontent.com/44739822/125669569-452e351a-6aed-427a-8bbb-31bb8e385785.PNG)

### 추가로 필요한 자료구조, 함수가 있으면 추가한다.
> - 추가할 헤더 파일이 있을 경우 scheduling.c의 해당 부분에 include
>> ![header](https://user-images.githubusercontent.com/44739822/125669552-1719cc92-44c9-4ddd-9370-1808eed81403.png)
> - 추가할 함수가 있을 경우 scheduling.c의 해당 부분에 작성
>> ![function](https://user-images.githubusercontent.com/44739822/125669572-164a05ad-374e-4add-b8b6-f955652f4831.png)
> - 추가할 .c 파일이 있을 경우 Makefile의 해당 부분에 작성
>> ![makefile](https://user-images.githubusercontent.com/44739822/125670175-5d8b11c5-c6a9-4659-9fd8-7593053b1136.png)

### 'make' 명령어를 사용해 컴파일을 완료하면 'schedule'이라는 실행파일을 만들 수 있다.
> ![make](https://user-images.githubusercontent.com/44739822/125670950-a14e998f-13b5-41fc-84c8-e843c81c7b5f.PNG)

### 아래 형식으로 명령을 작성해 테스트한다.
> - FIFO scheduling을 테스트 할 경우
> ~~~Bash
> ./schedule [trace 파일 경로] FIFO
> ~~~

> - SJF scheduling을 테스트 할 경우
> ~~~Bash
> ./schedule [trace 파일 경로] SJF
> ~~~

> - RR scheduling을 테스트 할 경우
> ~~~Bash
> ./schedule [trace 파일 경로] RR [Quantum 크기]
> ~~~

> - MLFQ scheduling을 테스트 할 경우
> ~~~Bash
> ./schedule [trace 파일 경로] MLFQ [URGENT Quantum 크기] [HIGH Quantum 크기] [MID Quantum 크기] [LOW Quantum 크기]
> ~~~

> - GUARANTEE scheduling을 테스트 할 경우
> ~~~Bash
> ./schedule [trace 파일 경로] GUARANTEE [Quantum 크기]
> ~~~  

### schedule_ans에 같은 명령을 테스트하고 결과를 비교한다.
![sim_result](https://user-images.githubusercontent.com/44739822/125686898-e8655f33-31db-4576-8477-168d784c8895.png)

------------

## 구현 결과
### - ex 1.
> ~~~Bash
> ./schedule traces/test SJF
> ~~~
> ![fifo test](https://user-images.githubusercontent.com/44739822/125686728-c25a9cc0-6a72-4c95-8ada-1da9c780319d.PNG)

### - ex 2.
> ~~~Bash
> ./schedule_ans traces/test_100 MLFQ 2 4 6 9
> ~~~
>
> ![sim_result2](https://user-images.githubusercontent.com/44739822/125686253-4025bcf2-f4e4-4edf-9dfc-a00ffb1cb4ba.PNG)
> 
> ![sim_result2-1](https://user-images.githubusercontent.com/44739822/125686247-07ba2643-d9f7-49e2-a545-ff98d7e4816a.PNG)

------------

## 구현 시 주의 사항
- 전역변수 사용 x
- src 내부의 코드는 고치지 x
- scheduler.c 내부 코드도 이미 작성되어 있는 부분은 고치지 x
- src의 모든 헤더파일은 꼭 다 보고 구현하기

### MLFQ priority 이동 규칙
- 매 cycle 가장 마지막에 priority이동이 일어난다.
- 이동 대상: 해당 priority에서 10cycle 머무르면 한 priority 높은 큐로 옮겨줌. (LOW -> MID -> HIGH -> URGENT, URGENT의 processs는 더이상 이동 x)
- 옮겨야 할 process가 여러개일 경우, 처리 우선 순위: terminate까지 남은 작업량(cycle) > 큐 안에서 순서 (앞일수록 우선)

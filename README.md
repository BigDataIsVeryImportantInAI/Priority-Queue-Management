# Priority Queue Management

----
## 개발 배경/목표

>* 프로세스 스케쥴링을 모델링한 Priority Queue Management 프로그램을 작성

>* 운영체제의 주 기능인 실행중인 프로그램을 CPU가 처리하는 방법을 시뮬레이션함

>* 여러가지 스케쥴링 방법 중 우선순위 스케쥴링 방법을 체택

>* 이 시뮬레이션 프로그램을 개발함으로 운영체제에 대한 이해도 향상 증진


----
## 개발 구성 및 과정

>* 프로세스를 모델링한 자료구조를 정의한 후 그것들을 Double Linked List로 연결해서 3단계의 레벨을 가진 Queue를 만든다

>![논리 구조](/image/image1.PNG)

>     typedef struct priority_queue *queue_pointer;
	struct priority_queue{
		int process_id;
		int priority;
		int computing_time;
		int computing_time_copy;
		int insert_OStime;
		queue_pointer left_link, right_link;
	};

>* 각 큐의 끝 노드를 헤더로 연결해 원형 큐를 구성했다

>* 프로세스의 정보를 담고있는 text파일을 읽어들어 시뮬레이션한다.

>* 해당 프로세스 정보를 읽고 우선순위가 높은것부터 컴퓨팅 타임동안 처리한다.

>* 컴퓨팅 타임동안 처리되지 않은 큐는 우선순위를 낮추고 큐의 뒤로 보낸다.

----
## 개발 내용

>* 프로세스를 모델링한 구조체는 ID와 priority값, computing_time, os_time 그리고 다른 노드를 가리키는 left_link와 right_link를 구조체의 포인터로 만든다.

>* 이 프로그램의 전반적인 모습을 그림으로 나타내면 옆의 첫 번째 그림과 같이 3개의 head node와 다른 노드를 가리키는 각 노드들로 구성되어 있다.

>![전체 큐 구조](/image/image3.png)

>* 큐를 초기화 하는 함수, text파일을 읽어 새로운 프로세스를 넣는 함수, 해당 프로세스를 실행시키고 삭제 혹은 우선순위를 낮추고 다시 넣는 함수, 출려하는 함수, 4가지 함수를 작성하여 전체적인 시뮬레이션이 돌아가도록 하였다.

>![블럭 플로우](/image/image4.png)

>* 각 함수마다 적절한 예외처리를 하여 잘못된 값이 입력되었을 경우 또한 대비하였다.

----
## 개발 관련 사항

>* 개발 언어 : C

>* 컴파일 : gcc

>* 실행 환경 : Unix

>* 담당분야 : 전체

----
## 실행 화면

>![실행화면](/image/image7.png)

//Operating System Report2 ProcessScheduling
//2010151009 Kim Eungi, 2012151029 Oh Woosuk, 2010151039 Cho Nakwon
//Make four queue by circular queue and node means process link by DoubleLinked List
//General process of the operation is equal to PriorityQueueManagement more action there real_time Process
//The input file in that directory is not 'input_file.txt', 'input_file' is it

#include <stdio.h>
#include <malloc.h>
#define QUEUE_LEVEL 4	//Four queues
#define TIME_QUANTUM 20 //Time quantom of processing

typedef struct priority_queue *queue_pointer;
struct priority_queue{
	int process_id;
	int priority;
	int computing_time;
	int computing_time_copy;
	int insert_OStime;
	queue_pointer left_link, right_link;
};

void initialize_queue();
int insert_queue(int, int, int);
int scheduling();
int real_timeRunning(queue_pointer);
void running();
int check_qLevel(int);

//Make four header nodes by global variable
queue_pointer head[QUEUE_LEVEL];
unsigned int OStime = 0;

int main(){
	FILE *stream;
	int file_state;
	int type = 0, process_id = 0, priority = 0, computing_time = 0;
	
	initialize_queue();

	//File open
	stream = fopen("input_file", "r");
	if(stream == NULL)
		printf("파일 열기 에러\n");

	printf("Procsee_id Queue_iD  priority computing_time turn_around time\n");
	//Start insert(), scheduling(), running() by type value that wrote 'input_file'
	while(1){
		fscanf(stream, "%d %d %d %d", &type, &process_id, &priority, &computing_time);
		switch(type){
			case 0:
				insert_queue(process_id, priority, computing_time);
				break;
			case 1:
				scheduling();
				break;
			case -1:
				running();
				break;
			default:
				printf("type값 오류\n");	//Wrong type value in file
				break;
		}
		if(type == -1)
			break;
	}
	//File close
	file_state = fclose(stream);
	if(file_state == EOF)
		printf("파일 닫기 에러\n");

	return 0;
}

void initialize_queue(){
	int i;
	for(i=0; i<QUEUE_LEVEL; i++){
		head[i] = (queue_pointer)malloc(sizeof(struct priority_queue));
		head[i]->left_link = head[i];	//Circular Queue
		head[i]->right_link = head[i];
		head[i]->process_id = 0;
		head[i]->priority = 0;
		head[i]->computing_time = 0;
		head[i]->computing_time_copy = head[i]->computing_time;
		head[i]->insert_OStime = 0;
	}
}

int insert_queue(int process_id, int priority, int computing_time){
	int qLevel = 0;			 //Queue Level variable
	queue_pointer qp;		 //Create a node
	queue_pointer already_qp;//Created node

	qp = (queue_pointer)malloc(sizeof(struct priority_queue));
	qp->process_id = process_id;
	qp->priority = priority;
	qp->computing_time = computing_time;
	qp->computing_time_copy = qp->computing_time;
	qp->insert_OStime = OStime;

	//Rriority value check, Queue ID calculation
	qLevel = check_qLevel(qp->priority);
	if(qLevel == -1){		//Real_time process
		real_timeRunning(qp);
		return 0;
	}
	else if(qLevel == -2){	//priority value is not in domain
		printf("priority값 오류. -10~-1, 1~31의 값 입력가능\n");
		return 0;
	}

	//process_id, computing_time value check
	if(process_id < 0){
		printf("process_id값 오류\n");
		return 0;
	}
	if(computing_time < 0){
		printf("computing_time값 오류\n");
		return 0;
	}

	//General process insert
	//Compare priority value
	already_qp = head[qLevel]->right_link;
	if(head[qLevel]->right_link == head[qLevel]){//Node is coming first time in this queue
		//Insert node
		qp->left_link = already_qp;
		qp->right_link = already_qp;
		already_qp ->right_link = qp;
		already_qp ->left_link = qp;
	}
	else{										//Node is already here
		//Fine location in insert
		while(already_qp != head[qLevel]){
			if(already_qp->priority > priority)
				break;
			already_qp = already_qp->right_link;
			
		}
		//Insert node
		qp->left_link = already_qp->left_link;
		qp->right_link = already_qp->left_link->right_link;;
		already_qp->left_link->right_link = qp;
		already_qp->left_link = qp;
	}
	return 0;
}

int scheduling(){
	int i = 0;
	int qLevel = 0;
	queue_pointer qp;
	queue_pointer already_qp;
	while(i<4){
		qp = head[i]->right_link;
		if(head[i]->right_link == head[i]){//That queue is empty(node at right_link of header is header)
			i++;//Next queue level
			if(i==4)//Scheduled to continue all the queues are empty when there
				printf("더 이상 scheduling할 노드가 없습니다\n");
		}
		else{							  //Header node to the next node scheduling(The priority of that node is highst)
			if(qp->computing_time <= TIME_QUANTUM){//Process is over by onte time_quantom
				OStime += qp->computing_time;
				printf("%-10d %-8d  %-8d %-14d %-16d\n",qp->process_id, i+1, qp->priority, qp->computing_time_copy, (OStime - qp->insert_OStime));
				//Delete node
				head[i]->right_link->right_link->left_link = head[i];
				head[i]->right_link = head[i]->right_link->right_link;
				break;
			}
			else{					//computing_time of process is left over and priority value increase
				qp->priority += 10;
				if(qp->priority > 31)	//priority value is not over 31
					qp->priority = 31;
				OStime += TIME_QUANTUM;
				qp->computing_time -= TIME_QUANTUM;
				qLevel = (qp->priority-1)/10;
				already_qp = head[qLevel]->right_link;

				//Fine location in insert
				while(already_qp != head[qLevel]){
					if(already_qp->priority > qp->priority)
						break;
					already_qp = already_qp->right_link;
			
				}
				//Insert node
				qp->left_link->right_link = qp->right_link;
				qp->right_link->left_link = qp->left_link;
				qp->left_link = already_qp->left_link;
				qp->right_link = already_qp->left_link->right_link;;
				already_qp->left_link->right_link = qp;
				already_qp->left_link = qp;
				break;
			}
		}
	}
	return 0;
}

int real_timeRunning(queue_pointer qp){
	printf("%-10d real_time %-8d %-14d %-16d\n", qp->process_id, qp->priority, qp->computing_time, qp->computing_time);
	OStime += qp->computing_time;
	return 0;
}

void running(){
	while(1){
		if (/*Exit Condition*/head[0]->right_link == head[0] && head[1]->right_link == head[1] && head[2]->right_link == head[2] && head[3]->right_link == head[3])
			break;
		scheduling();
	}
}

int check_qLevel(int priority){
	if(priority >= -10 && priority <= -1)//If real_time process qLevel is -1
		return -1;
	else if(priority >= 1 && priority <= 31)
		return (priority-1)/10;
	else								//priority value is not in domain
		return -2;
}
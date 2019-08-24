#include <stdio.h>
#define MAX_SIZE 200
int front=0,rear=-1,q[MAX_SIZE];
static void enqueue(int el){
	if(rear>=MAX_SIZE){
		printf("Queue full!\n");
		return;
	}
	q[++rear] = el;
}
static int dequeue(int *el){
	if(rear == -1){
		printf("Queue is empty!\n");
		return -1;
	}
	*el = q[front++];
	if(front > rear){
		front = 0; 
		rear = -1;
	}
	return 0;
}
static void display(){
	int i = front;
	while(i <= rear)
		printf("%d\n" , q[i++]);
}
int main(){

	int buf = 0, opt = 0;
	while(opt!=4){
		printf("\n\n::QUEUE OPERATIONS::\n");
		printf("1. Enqueue.\n2. Dequeue.\n3. Display.\n4. Exit. \n"	);
		printf("Please enter your options: ");
		scanf("%d" , &opt);
		switch(opt){
			case 1:
				printf("\n\nEnter the element to enqueue: ");
				scanf("%d" , &buf);
				enqueue(buf);
				break;
			case 2:
				if(!dequeue(&buf))
					printf("\n\nDequeued (%d)!\n\n",buf);
				break;
			case 3:
				display();
				break;
			default:
				opt = 4;
				break;
		}
	}
	return 0;
}

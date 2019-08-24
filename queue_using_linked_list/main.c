#include <stdlib.h>
#include <stdio.h>
typedef struct _queue_t {
	int data;
	struct _queue_t *next;
} queue_t;
void enqueue(queue_t **q, int el){
	while(*q)
		q = &((*q)->next);
	*q = calloc(1, sizeof **q);
	(*q)->data = el;
}
static int dequeue(queue_t **q, int *el){
	queue_t *p = *q;
	if(!p){
		printf("Queue is empty!\n");
		return -1;
	}
	*el = p->data;
	*q = (*q)->next;
	free(p);
	return 0;
}
static void display(queue_t *q){
	while(q){
		printf("%d\n",q->data);
		q=q->next;
	}
}
int main(){
	int opt = 0,
	    buf = 0;
	queue_t *q = NULL;
	while(opt!=4){
		printf("\n\n::QUEUE OPERATIONS::\n");
		printf("1. Enqueue.\n2. Dequeue.\n3. Display.\n4. Exit. \n");
		printf("Please enter your options: ");
		scanf("%d" , &opt);
		switch(opt){
			case 1:
				printf("Enter the element to enqueue: ");
				scanf("%d" , &buf);
				enqueue(&q, buf);
				break;
			case 2:
				if(!dequeue(&q, &buf))
					printf("Dequeued (%d)!\n", buf);
				break;
			case 3:
				display(q);
				break;
			default:
				opt = 4;
				break;
		}
	}
	return 0;
}

#include <stdio.h>
#define MAX_SIZE 200
#define parent(i) (i/2)
#define left_child(i) (2*i)
#define right_child(i) (left_child(i) + 1)
int heap[MAX_SIZE],heap_size=0;
static void insert(int v){
	int i = 0;
	if(heap_size >= MAX_SIZE){
		printf("Cannot enqueue, Queue is full!\n");
		return;
	}
	for(i=++heap_size;
	    i >= 2 && heap[parent(i)] > v;
	    i=parent(i))
		heap[i] = heap[parent(i)];
	heap[i] = v;
}
static int delete_min(int *v){
	int i = 0,last_el=0,child=0;
	if(!heap_size){
		printf("Priority Queue is empty!\n");
		return -1;
	}
	*v = heap[1];
	last_el = heap[heap_size--];
	for(i=1;left_child(i) <= heap_size ; i=child){
		/* Find the smaller child. */
		/* Note:
		 * Here we check if the left child is 
		 * the heap size which implies that 
		 * the right child was the last element and it 
		 * has been deleted so we don't need to check it. */
		child = left_child(i);
		if(child != heap_size &&
		   heap[right_child(i)] < heap[child])
			child = right_child(i);

		/* Precolate down. */
		/* If the smallest child of this node is smaller 
		 * than the last element which is trivially true for most cases.
		 * We move the smallest child to the root. 
		 * Then we set the new root node as this smallest 
		 * child and then repeat the above process until
		 * the last element is lesser than a node and 
		 * move it there. */
		if(last_el > heap[child])
			heap[i] = heap[child];
		else
			break;
	}
	heap[i] = last_el;
	return 0; /* no error. */
}
static void display(){
	int i = 1;
	while(i <= heap_size)
		printf("%d\n", heap[i++]);
}
int main(){
	int opt=0,buf=0;
	while(opt!=4){
		printf("\n\n::PRIORITY QUEUE OPERATION::\n");
		printf("1. Insert.\n2. Delete Minimum.\n3.Display.\n4. Exit.\n");
		printf("Enter your choice: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				printf("Enter the element to insert: ");
				scanf("%d", &buf);
				insert(buf);
				break;
			case 2:
				if(!delete_min(&buf))
					printf("Minimum Value: %d\n", buf);
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

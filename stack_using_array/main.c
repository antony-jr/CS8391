#include <stdio.h>
#define MAX_SIZE 200
int tos=-1,s[MAX_SIZE];
static void push(int el){
	if(tos >= MAX_SIZE){	
		printf("Stack is full!\n");
		return;
	}	
	s[++tos] = el;
}
static int pop(int *buf){
	if(0 > tos){
		printf("Stack is empty!\n");
		return -1;
	}
	*buf = s[tos--];
	return 0;
}
static void display(){
	int i = tos;
	while(i!=-1)
		printf("%d\n",s[i--]);
}
int main(){
	int opt = 0,buf = 0;
	while(opt!=4){
		printf("\n\n::STACK OPERATIONS::\n");
		printf("1. Push.\n""2. Pop.\n""3. Display.\n""4. Exit. \n");
		printf("Please enter your options: ");
		scanf("%d" , &opt);
		switch(opt){
			case 1:
				printf("Enter the element to push: ");
				scanf("%d" , &buf);
				push(buf);
				break;
			case 2:
				if(!pop(&buf))	
					printf("Poped element(%d)!\n\n",buf);
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

#include <stdio.h>
#define BUF_SIZE 50
int MAX_SIZE=0;
int list[BUF_SIZE];
static void insert(int pos, int v){
	int i = MAX_SIZE - 1;
	if(pos >= MAX_SIZE || pos < 0){
		printf("Invalid position!\n");
		return;
	}
	while(i > pos){
		list[i] = list[i-1];
		--i;
	}
	list[pos] = v;
}
static int search(int *pos, int v){
	int i = 0;
	while(i<MAX_SIZE){
		if(list[i++] == v){
			*pos = i-1;
			return 0;
		}
	}
	return -1;
}
static void delete(int pos){
	int i = pos;
	if(pos >= MAX_SIZE || pos < 0){
		printf("Invalid position!\n");
		return;
	}
	while(i < MAX_SIZE-1){
		list[i] = list[i+1];
		++i;
	}
}
static void display(){
	int i = 0;
	while(i<MAX_SIZE)
		printf("%d\n", list[i++]);
}
int main(){
	int opt = 0,buf1 = 0, buf2 = 0;
	printf("Enter the maximum size of list: ");
	scanf("%d", &MAX_SIZE);
	if(MAX_SIZE >= BUF_SIZE){
		printf("not enough memory!\n");
		return -1;
	}
	while(opt!=5){
		printf("\n\n::LIST OPERATIONS::\n");
		printf("1. Insert.\n2. Search.\n3. Delete.\n4. Display.\n5. Exit.\n");
		printf("Enter your choice: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				printf("Enter the position to insert: ");
				scanf("%d", &buf1);
				printf("Enter the value to insert: ");
				scanf("%d", &buf2);
				insert(buf1,buf2);
				break;
			case 2:
				printf("Enter the value to search: ");
				scanf("%d", &buf1);
				if(!search(&buf2, buf1))
					printf("Value found at position: %d\n", buf2);
				else
					printf("Value not found!\n");
				break;
			case 3:
				printf("Enter the position to delete: ");
				scanf("%d", &buf1);
				delete(buf1);
				break;
			case 4:
				display();
				break;
			default:
				opt = 5;
				break;
		}
	}
	return 0;
}

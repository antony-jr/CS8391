#include <stdio.h>
#define MAX_SIZE 200
static int lsearch(int *a, int n, int v, int *buf){
	int i = 0;
	do{
		if(*(a+i)!=v)
			continue;
		*buf = i;
		return 0;
	}while(++i<n);
	return -1;
}
int main(){
	int a[MAX_SIZE],n=0,i=0;
	printf("Enter the upper limit: ");
	scanf("%d", &n);
	do{
		printf("Enter value[%d]: ", i+1);
		scanf("%d", a+i);
	}while(++i<n);
	printf("Enter the value to search: ");
	scanf("%d", &i);
	if(!lsearch(a,n,i,&i)){
		printf("Value found at position: %d.\n",i+1);
		return 0;
	}
	printf("Value not found!\n");
	return -1;
}

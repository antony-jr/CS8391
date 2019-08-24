#include <stdio.h>
#define MAX_SIZE 200
int bsearch(int *a,int n,int v,int *buf){
	int left=0,right=n,mid=0;
	while(left<=right){
		*buf = mid = (left+right)/2;
		if(a[mid] == v){
			return 0;
		}else if(v < a[mid]){
			right = mid-1;
		}else{
			left = mid+1;
		}
	}
	return -1;
}
int main(){
	int a[MAX_SIZE],n=0,i=0;
	printf("Enter the upper limit: ");
	scanf("%d", &n);
	printf("::Enter the array in ascending order::\n");
	do{
		printf("Enter value[%d]: ", i+1);
		scanf("%d", a+i);
	}while(++i<n);
	printf("Enter the value to search: ");
	scanf("%d", &i);
	if(!bsearch(a,n,i,&i)){
		printf("Value found at position: %d.\n",i+1);
		return 0;
	}
	printf("Value not found!\n");
	return -1;

}

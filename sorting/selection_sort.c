#include <stdio.h>
#include <stdlib.h>

#define SWAP(a , b) do{int temp=a;a=b;b=temp;}while(0)

static void ssort(int *array , int n){
	int i = 0,
	    j = 0,
	    pos = 0;
	while(i<n){
		pos = i;
		j = i + 1;
		while(j<n){
			if(*(array + j) < *(array + pos)){
				pos = j;
			}
			++j;
		}

		if(pos != i){
			SWAP(*(array + i),
			     *(array + pos));
		}
		++i;
	}
}

int main(int ac , char **av){
	int n = ac - 1,
	    *arr = NULL,
	    *p = NULL;

	if(!n){
		printf("Usage: %s [NUMBERS.... ]\n" , *av);
		return -1;
	}

	p = arr = calloc(n + 1 , sizeof(*arr));
	++av;
	while(*av){
		*p++ = atoi(*av);
		++av;
	}
	ssort(arr , n);
	p = arr;
	while(*p){
		printf(" %d " , *p++);
	}
	putchar('\n');
	free(arr);
	return 0;
}

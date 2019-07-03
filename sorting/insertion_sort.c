#include <stdio.h>
#include <stdlib.h>

static void isort(int *array , int n){
	int i = 1,
	    j = 0,
	    key = 0;
	while(i<n){
		key = *(array + i);
		j = i - 1;
		while(j >= 0 && 
		      *(array + j) > key){
			*(array + j + 1) = *(array + j);
			--j;
		}
		*(array + j + 1) = key;
		++i;
	}
	return;
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
	isort(arr , n);
	p = arr;
	while(*p){
		printf(" %d " , *p++);
	}
	putchar('\n');
	free(arr);
	return 0;
}

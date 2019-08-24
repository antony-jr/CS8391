#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 200
static int is_op(char c){
	return (c == '-' || c == '+' || 
		c == '*' || c == '/') ? 1 : 0;
}
static int do_op(int a, int b, char c){
	return (c == '-') ? a-b: (c == '+') ? a+b:
	       (c == '*') ? a*b: (c == '/') ? a/b: 0;
}
int main(){
	char buf[MAX_SIZE],*p = buf;
	int stack[MAX_SIZE],top=-1;
	printf("Enter the postfix expression: "); gets(buf);
	while(*p){
		if(is_op(*p)){
			if(top < 1){goto err;}
			stack[top] = do_op(stack[--top], stack[top], *p);
		}else if(isdigit(*p)){
			stack[++top] = *p - '0';
		}else{if(!isspace(*p)){goto err;}}
		++p;
	}
	if(top != 0){goto err;}
	printf("Result: %d\n" , stack[top]);
	return 0;
err:
	printf("Malformed postfix expression!\n");
	return -1;
}

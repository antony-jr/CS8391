#include <string.h>
#include <ctype.h>
#include <stdio.h>
#define MAX_SIZE 200
static int priority(char c){
	return (c == '-') ? 1 : (c == '+') ? 2 :
	       (c == '*') ? 3 : (c == '/') ? 4 :
	       (c == '(' || c == ')') ? 5 : -1;
}
static void printchar(char c){
	if(c == '(' || c == ')'){return;}
	putchar(c);
}
int main(){
	int top = -1,stack[MAX_SIZE];
	char buf[MAX_SIZE],*p = buf;
	printf("Enter the infix expression: "); gets(buf);
	printf("The postfix expression: ");
	while(*p){
		if((*p != '(' && *p != ')' && isalnum(*p))
		    ||isspace(*p)){
			printchar(*p);
			++p;
			continue;
		}
		while((top>=0) &&
		      priority(stack[top]) >= priority(*p)){
			printchar(stack[top--]);
		}
		stack[++top] = *p;
		++p;
	}
	while(top >= 0){
		printchar(stack[top--]);
	}
	printchar('\n');
	return 0;
}

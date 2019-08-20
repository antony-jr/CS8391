#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *get_line(){
	int c = 0;
	int size = 1;
	char *r = calloc(size , sizeof *r);
	while((c = getchar()) != EOF && c != '\n'){
		r[size-1] = c;
		++size;
		r = realloc(r , size * (sizeof(*r)));
	}
	r[size-1] = '\0';
	return r;
}

int main(){
	int top = -1;
	int *stack = NULL;
	size_t s = 0;
	char *expr = NULL,
             *p = NULL;

	printf("Enter the infix expression: ");
	expr = get_line();
	s = strlen(expr);
	if(!s){
		printf("fatal error: no input was given!\n");
		free(expr);
		return -1;
	}
	stack = calloc(s + 5, sizeof *stack);
	p = expr;
	printf("The postfix expression: ");
	while(*p){
		switch(*p){
			case '-':
				while((top >= 0) &&
				      (stack[top] == '+'||
				      stack[top] == '*' ||
				      stack[top] == '/' ||
				      stack[top] == '-')){
					putchar(stack[top--]);
				}
				stack[++top] = *p;
				break;
			case '+':
				while((top >= 0) &&
				      (stack[top] == '*'||
				      stack[top] == '/' ||
				      stack[top] == '+')){
					putchar(stack[top--]);
				}
				stack[++top] = *p;
				break;
			case '*':
				while((top >= 0) &&
				      (stack[top] == '*'||
				      stack[top] == '/')){
					putchar(stack[top--]);
				}
				stack[++top] = *p;
				break;
			case '/':
				while((top >= 0) && stack[top] == '/'){
					putchar(stack[top--]);
				}
				stack[++top] = *p;
				break;
			case '(':
				stack[++top] = *p;
				break;
			case ')':
				while(top >= 0 && stack[top] != '('){
					putchar(stack[top--]);
				}
				--top;
				break;
			default:
				if(*p != ' '){
					putchar(*p);
				}
				break;
		}
		++p;
	}
	while(top >= 0){
		putchar(stack[top--]);
	}
	putchar('\n');
	free(expr);
	free(stack);
	return 0;
}

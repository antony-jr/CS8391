#include <stdio.h>
#include <stdlib.h>
typedef struct _sll_t {
	int data;
	struct _sll_t *next;
} sll_t;
static void append(sll_t **r, int x){
	while(*r){
		r = &((*r)->next);
	}
	*r = calloc(1, sizeof **r);
	(*r)->data = x;
}
static sll_t *find_prev(sll_t *r, int x){
	while(r){
		if((r->next && r->next->data == x) ||
		   r->data == x){
			return r;
		}
		r = r->next;
	}
	return NULL;
}
static void insert(sll_t *r, int after_x, int y){
	sll_t *p = NULL;
	r = find_prev(r, after_x);
	r = r ? r->data != after_x ? r->next : r:NULL;
	if(!r){
		printf("Cannot find %d in list!\n", after_x);
		return;
	}
	p = calloc(1, sizeof *r);
	p->data = y;
	p->next = r->next;
        r->next = p;	
}
static void delete(sll_t **r, int x){
	sll_t *p = find_prev(*r,x),*t;
	if(!p){
		printf("Cannot find %d in list!\n", x);
		return;
	}
	if(p->data == x){
		*r = p->next;
		free(p);
		return;
	}
	t = p->next;
	p->next = t->next;
	free(t);
}
static void display(sll_t *r){
	while(r){
		printf("[%p]: %d\n",r,r->data);
		r = r->next;
	}
}
int main(){
	int opt = 0, buf = 0,b=0;
	sll_t *list = NULL,*p = NULL;
	while(opt!=6){
		printf("\n\n::LINKED LIST OPERATIONS::\n");
		printf("1. Append.\n2. Insert.\n3. Delete.\n4. Search.\n5. Display.\n6. Exit.\n");
		printf("Enter a choice: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				printf("Enter the value to append: ");
				scanf("%d", &buf);
				append(&list, buf);
				break;
			case 2:
				printf("Enter the value before this value: ");
				scanf("%d", &b);
				printf("Enter the value: ");
				scanf("%d", &buf);
				insert(list, b, buf);
				break;
			case 3:
			       printf("Enter the value to delete: ");
			       scanf("%d", &buf);
			       delete(&list, buf);
			       break;
			case 4:
			       printf("Enter the value to search: ");
		               scanf("%d", &buf);
		               p = find_prev(list,buf);
		               p = p ? p->data != buf ? p->next : p:NULL;
			       if(p)
				       printf("Value found at [%p].\n",p);
			       else
				       printf("Value not found!\n");
			       break;
			case 5:
			       display(list);
			       break;
			default:
				opt = 6;
				break;
		}
	}
	return 0;
}

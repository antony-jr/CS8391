#include <stdlib.h> /* for memory allocation */
#include <stdio.h> /* for sprintf */
#include "singly_linked_list.h"

/*
 * Allocates space for a new singly linked list node 
 * and initializes it to zero and sets the data with respect to
 * the given value.
 * 
 * Example:
 * 	slinked_list_node_t *new_node = slinked_list_node_create(10);
 * 	new_node->next; // reference to next node in the list.
 * 	new_node->element; // data , in this case 10.
*/
slinked_list_node_t *slinked_list_node_create(int el){
	slinked_list_node_t *r = calloc(1 , sizeof(*r));
	if(!r){
		return NULL;
	}
	r->element = el;
	r->next = NULL;
	return r;
}

/*
 * Destroys a singly linked list node along with its children 
 * iteratively.
 *
 * Example:
 * 	slinked_list_node_destroy(new_node); //new_node is free.
 *
*/
void slinked_list_node_destroy(slinked_list_node_t *node){
	slinked_list_node_t *t = node,
			    *p = NULL;
	while(t){
		p = t;
		t = t->next;	
		free(p);
	}
	return;
}

/*
 * Creates a context for a singly linked list. */
slinked_list_t *slinked_list_create(){
	slinked_list_t *r = calloc(1 , sizeof *r);
	return r;
}

/*
 * Destroys context. */
void slinked_list_destroy(slinked_list_t *ctx){
	if(!ctx){
		return;
	}
	slinked_list_node_destroy(ctx->head);
	free(ctx);
}

/*
 * Returns 1 if the given singly linked list is empty. */
int slinked_list_is_empty(slinked_list_t *ctx){
	return !(ctx && ctx->head);
}

/*
 * Returns the reference to node in the linked list context which has
 * the same data as the given argument element. */
slinked_list_node_t *slinked_list_find(slinked_list_t *ctx , int element){
	slinked_list_node_t **p = NULL;
	if(!ctx){ 
		return NULL;
	}

	p = &(ctx->head);
	while(*p){
		if((*p)->element == element){
			return *p;
		}
		p = &((*p)->next);
	}
	return NULL;
}

/*
 * Same as slinked_list_find but returns the previous
 * node of the required node. */
slinked_list_node_t *slinked_list_find_previous(slinked_list_t *ctx , int element){
	slinked_list_node_t **p = NULL;
	if(!ctx){
		return NULL;
	}

	p = &(ctx->head);
	while(*p){
		if((*p)->next &&
		   (*p)->next->element == element){
			return *p;
		}
		p = &((*p)->next);
	}
	return NULL;
}

/* 
 * Inserts the given node after the referenced node with respect to
 * the context. */
int slinked_list_insert(slinked_list_t *ctx , slinked_list_node_t *node , int element){
	slinked_list_node_t *e = NULL;
	if(!node){
		return -1;
	}
	(void)ctx;

	if(!(e = slinked_list_node_create(element))){
		return -1;
	}

	e->next = node->next;
	node->next = e;
	return 0;
}

/* 
 * Deletes the node which has the same data as the given argument 
 * element with respect to the context.*/
int slinked_list_delete(slinked_list_t *ctx , int element){
	slinked_list_node_t **p = NULL,
			    *t = NULL;
	if(!ctx){
		return -1;
	}

	p = &(ctx->head);
	while(*p){
		if((*p)->element == element){
			t = *p;
			*p = (*p)->next;
			
			t->next = NULL;	
			slinked_list_node_destroy(t);	
			return 0;
		}
		p = &((*p)->next);
	}
	return  -1;

}

/* Returns the singly linked list as C String which 
 * can be readily printed. It delimits each node by
 * a new line '\n'. */
char *slinked_list_to_string(slinked_list_t *ctx){
	slinked_list_node_t **p = NULL;
	char *r = NULL,
	     *g = NULL;
	size_t iter = 0;
	if(!ctx){
		return NULL;
	}

	/* let it grow by 50 bytes. */
	if(!(r = calloc(50 , sizeof *r))){
		return NULL;
	}

	p = &(ctx->head);
	while(*p){
		iter += sprintf(r + iter , "[%p]: %d\n" , *p , (*p)->element);	
		p = &((*p)->next);
		g = realloc(r , sizeof(*r) * (iter + 50));
		if(!g){
			free(r);
			return NULL;
		}
		r = g;
	}
	return r;
}


/* A Simple interface for python programs. */
void DISPLAY(slinked_list_t *ctx){
	slinked_list_node_t **p = NULL;
	if(!ctx){
		return;
	}
	p = &(ctx->head);
	while(*p){
		printf("[%p]: %d\n" , *p , (*p)->element);
		p = &((*p)->next);
	}
	return;
}

void FIND(slinked_list_t *ctx , int element){
	slinked_list_node_t *node = slinked_list_find(ctx , element);
	if(!node){
		printf("NULL\n");
	}
	printf("[%p]{ %d , %p }\n" , node , node->element , node->next);
	return;
}

int DELETE(slinked_list_t *ctx , int element){
	return slinked_list_delete(ctx , element);
}

int INSERT(slinked_list_t *ctx , int element){
	slinked_list_node_t **p =NULL;
	if(!ctx){
		return -1;
	}
	p = &(ctx->head);
	while(*p){
		if(!(*p)->next){
			slinked_list_insert(ctx , *p , element);
			return 0;
		}
		p = &((*p)->next);
	}
	*p = slinked_list_node_create(element);
	return 0;
}

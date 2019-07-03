#ifndef SINGLY_LINKED_LIST_H_INCLUDED
#define SINGLY_LINKED_LIST_H_INCLUDED

typedef struct _slinked_list_node_t {
	int element;
	struct _slinked_list_node_t *next;
} slinked_list_node_t;

typedef struct {
	slinked_list_node_t *head;
} slinked_list_t;

slinked_list_node_t *slinked_list_node_create(int);
void slinked_list_node_destroy(slinked_list_node_t*);

slinked_list_t *slinked_list_create();
void slinked_list_destroy(slinked_list_t*);
int slinked_list_is_empty(slinked_list_t*);
slinked_list_node_t *slinked_list_find(slinked_list_t*,int);
slinked_list_node_t *slinked_list_find_previous(slinked_list_t*,int);
int slinked_list_insert(slinked_list_t*, slinked_list_node_t*,int);
int slinked_list_delete(slinked_list_t*,int);
char *slinked_list_to_string(slinked_list_t*);
#endif /* SINGLY_LINKED_LIST_H_INCLUDED */

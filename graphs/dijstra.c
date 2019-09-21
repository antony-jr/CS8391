#include <stdlib.h>
#include <stdio.h>
#define True 1
#define False 0

typedef struct {
	int distance;
	int not_inf;
} dist_t;

/* Adjacency list representation. */
typedef struct _ll_t {
	int w;
	int cost;
	struct _ll_t *next;
} ll_t;
typedef struct {
	int known;
	int path;
	dist_t D;
	ll_t *adjv;
} graph_t;

static graph_t *makeGraph(int n){
	int c = 0;
	int w = 0;
	int iter = 0;
	int iterAdj = 0;
	graph_t *r = calloc(n, sizeof *r);
	ll_t **p = NULL;
	if(!r)
		return NULL;

	for(iter = 0; iter < n; ++iter){
		r[iter].path = -1;
		do{
			printf("Enter the no. of adj. vertices to Vertex %d: ", iter);
			scanf("%d", &iterAdj);
		}while(iterAdj >= n);
		p = &(r[iter].adjv);
		while(*p){
			p = &((*p)->next);
		}
		while(iterAdj--){
			printf("Enter adj. Vertex: ");
			*p = calloc(1, sizeof **p);
			scanf("%d" , &((*p)->w));
			printf("Enter adj. Vertex cost: ");
			scanf("%d", &((*p)->cost));
			p = &((*p)->next);
		}
		putchar('\n');
		putchar('\n');
	}
	return r;
}

static void printPath(int v, graph_t *g){
	if(g[v].path != -1){
		printPath(g[v].path, g);
		printf(" to ");
	}
	printf(" %d ", v);
}

static void Dijkstra(int V, graph_t *g, int n){
	ll_t *p = NULL;
	int *Q = calloc(n, sizeof *Q);
	int front = -1, rear = -1;
	g[V].D.distance = 0;
	g[V].D.not_inf = True;
	Q[++rear] = V;
	
	while(rear != -1){
		V = Q[++front];
		--rear;
		if(front > rear){
			front = rear = -1;
		}

		g[V].known = True;
		p = g[V].adjv;
		while(p){
			if(g[p->w].known == False){
				if(g[p->w].D.not_inf == False){
					g[p->w].D.not_inf = True;
					g[p->w].D.distance = g[V].D.distance + p->cost;
					g[p->w].path = V;
				}else if(g[V].D.not_inf == True && 
					 g[V].D.distance + p->cost < g[p->w].D.distance){
					g[p->w].D.distance = g[V].D.distance + p->cost;
					g[p->w].path = V;
				}
				Q[++rear] = p->w;
			}
			p = p->next;
		}
	}
}
int main(int ac, char **av){
	int is_silent = False;
	if(ac > 1){
		if(!strcmp(av[1] , "-q") ||
		   !strcmp(av[1],  "--quiet")){
			is_silent = True;
		}
	}
	int n = 0;
	int start = -1;
	graph_t *g = NULL;
	if(is_silent){
		freopen(NULL, "r" , stdout);
	}
	printf("Enter number of vertices: ");
	scanf("%d", &n);

	g = makeGraph(n);
	if(!g){
		printf("not enough memory!\n");
		return -1;
	}

	printf("\nEnter the start vertex: ");
	scanf("%d", &start);

	Dijkstra(start , g , n);

	printf("\nEnter the destination vertex: ");
	scanf("%d", &start);

	if(is_silent){
		freopen(NULL,  "w" , stdout);
	}
	printPath(start , g);
	putchar('\n');
	return 0;
}

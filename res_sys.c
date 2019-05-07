#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ** v_arr;

typedef struct edge{
	char * source;
	char * destination;
	int dist;
}Edge;

typedef struct graph{
	int num_vertices, num_edges;
	Edge * edge;
}Graph;

Edge create_edge(char * s, char * d, int distance){
	Edge e;
	e.source = malloc(sizeof(s));
	e.destination = malloc(sizeof(d));
	strcpy(e.source, s);
	strcpy(e.destination, d);
	e.dist = distance;
	return e;  	
}


Graph * make_graph(){
	Graph * graph = malloc(sizeof(Graph));
	//count vertices
	int v = 0;
	FILE* f;
        f = fopen("small-airports.txt", "r");
        char buffer[100];
        while(fgets(buffer, 100, f) != NULL)
               v++;
        fclose(f);
	graph->num_vertices = v;
	
	//count edges
	int e = 0;
        f = fopen("small-dists.txt", "r");
        while(fgets(buffer, 100, f) != NULL)
        	e++;
        fclose(f);
	graph->num_edges = e;
	
	//add edges to graph
	Edge edge[e];
	graph->edge = edge;
        f = fopen("small-dists.txt", "r");
	int i = 0;
        while(fgets(buffer, 100, f) != NULL){
		char * source = malloc(4);
		char * dest = malloc(4);
		int dist;
		sscanf(buffer, "%s %s %d", source, dest, &dist);	
		edge[i] = create_edge(source, dest, dist);
		i++;
	}
        fclose(f);
	return graph;	 
}
int bellman_ford(Graph * graph, char * src, char * dest){
	int v = graph->num_vertices;
        v_arr = malloc(sizeof(Vertex) * v);
        FILE* f;
	char buffer[100];
	f = fopen("small-aiports.txt", "r");
        while(fgets(buffer, 100, f) != NULL){
                char * source = malloc(4);
                sscanf(buffer, "%s", source);
                v_arr
        }
        fclose(f);	
	int e = graph->num_edges;
        int dist[v];

        for(int i = 0; i < v; i++){
		dist[i] = INT_MAX;
	dist[src] = 0;
	
	for(int i = 1; i < v - 1; i++)
		
	return 0;
}


int main(){
	fflush(stdin);
	Graph * graph = make_graph();
	printf("v: %d e: %d\n", graph->num_vertices, graph->num_edges);
	while(1){
		char a[100];
		printf("enter command> ");
		scanf("%s", a);
		if(strcmp(a, "airports") == 0){
			//printf("here\n");
			FILE* f;
			f = fopen("small-airports.txt", "r");
			char buffer[100];
			while(fgets(buffer, 100, f) != NULL)
				printf("%s", buffer); 
			fclose(f);
		}
		else if(strcmp(a, "help") == 0){
			printf("Type \'airports\' to see a list of airports and their cities.\n");
			printf("Type \'distance\' to find the shortest distance between two cities.\n");
			printf("Type \'quit\' to quit.\n");
			printf("Type \'help\' to see this message again.\n");
		}
		else if(strcmp(a, "quit") == 0){
			break;
		}
		else if(strcmp(a, "distance") == 0){
			char a1[100];
			char a2[100];
			scanf("%s", a1);
			scanf("%s", a2);
			bellman_ford(graph, a1, a2);
		}
		else{
			printf("Not a valid input.  Type \'help\' for more.\n");
		}
	}
	printf("Good bye!\n");
	return 0;
}
	

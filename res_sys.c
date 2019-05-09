#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int INT_MAX = 10000;
char ** v_arr;
int length;
char * filename_a;
char * filename_d;
//int * path;

typedef struct edge{
	int  source;
	int destination;
	int dist;
}Edge;

typedef struct graph{
	int num_vertices, num_edges;
	Edge * edge;
}Graph;

Edge create_edge(char * s, char * d, int distance){
	Edge e;
	//e.source = malloc(sizeof(s));
	//e.destination = malloc(sizeof(d));
	int ss = -1;
	int dd = -1;
	//printf("here\n");
	//printf("%d\n", length);
	for(int i = 0; i < length; i++){
	//	printf("array: %s arg: %s\n", v_arr[i], s);

        	if(strcmp(v_arr[i], s) == 0)
                        ss = i;
		if(strcmp(v_arr[i], d) == 0)
			dd = i;
	}
	if(ss == -1 || dd == -1){
		//printf("here\n");
		return e;
	}
	e.source = ss;
	//printf("source: %d\n", ss);
	e.destination = dd;
	//printf("dest: %d\n", dd);
	e.dist = distance;
	//printf("dist: %d\n", distance);
	return e;  	
}


Graph * make_graph(){
	Graph * graph = malloc(sizeof(Graph));
	//count vertices
	int v = 0;
	FILE* f;
        f = fopen(filename_a, "r");
        char buffer[100];
        while(fgets(buffer, 100, f) != NULL)
               v++;
        fclose(f);
	graph->num_vertices = v;
	
	v_arr = malloc(sizeof(char*) * v);
	//printf("%d\n", v);
	int index = 0;
	f = fopen(filename_a, "r");
        while(fgets(buffer, 100, f) != NULL){
        	//printf("here\n");
		v_arr[index] = malloc(4);
		sscanf(buffer, "%s", v_arr[index]);
        	index++;
        }
	
	//count edges
	int e = 0;
        f = fopen(filename_d, "r");
        while(fgets(buffer, 100, f) != NULL)
        	e++;
        fclose(f);
	e = e*2;
	graph->num_edges = e;
	length = v;
	
	//add edges to graph
	Edge * edge = malloc(sizeof(Edge) * e);
	graph->edge = edge;
        f = fopen(filename_d, "r");
	int i = 0;
	//printf("here\n");
        while(fgets(buffer, 100, f) != NULL){
		char * source = malloc(4);
		char * dest = malloc(4);
		int dist;
		sscanf(buffer, "%s %s %d", source, dest, &dist);	
		//printf("%s %s %d\n", source, dest, dist);
		edge[i] = create_edge(source, dest, dist);
		edge[i+1] = create_edge(dest, source, dist);
		//printf("%d, %d, %d\n", edge[i].source, edge[i].destination, edge[i].dist);
		i+=2;
	}
        fclose(f);
	return graph;	 
}
int bellman_ford(Graph * graph, char * source, char * dest){
	int v = graph->num_vertices;
        FILE* f;
	char buffer[100];
	f = fopen(filename_a, "r");
	int index = 0;
	char temp[4];
	while(fgets(buffer, 100, f) != NULL){
		sscanf(buffer, "%s", temp);
		v_arr[index] = malloc(4);
		strcpy(v_arr[index], temp);
		index++; 
        }
	int src = 0;
	int des = 0;
	for(int i = 0; i < length; i++){
		if(strcmp(v_arr[i], source) == 0){
			src = i;	
		}
		if(strcmp(v_arr[i], dest) == 0)
			des = i;
	}
	//printf("src is %d, dest is %d\n", src, des);
        fclose(f);	
	int e = graph->num_edges;
        int dist[v];

        for(int i = 0; i < v; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;
	
	int path[v];
	int weights[v];	
	for(int i = 1; i <= v - 1; i++)
		for(int j = 0; j < e; j++){
			int a = graph->edge[j].source;
			int b = graph->edge[j].destination;
			int weight = graph->edge[j].dist;
			if(dist[a] != INT_MAX && dist[a] + weight < dist[b]){
				dist[b] = dist[a] + weight;
				path[b] = a;
				weights[b] = weight;
			}
		}
	printf("Total distance is: %d\n", dist[des]);
	//int ** result = calloc(1, sizeof(int*)*v);
	int result[v][2];
	int counter = 0;
	int i = des;
	do{ 
		i = path[i];
		result[counter][0] = i;
		result[counter][1] = weights[i];
		counter++;
	}while(i != src);
	
	//for(int i = 0; i < counter; i++)
	//	printf("%d\n", weights);	

	for(int i = counter-1; i >= 1; i--)
	{
		printf("%s -> ", v_arr[result[i][0]]);
		printf("%s %d\n", v_arr[result[i - 1][0]], result[i - 1][1]);
	}
	printf("%s -> %s %d\n", v_arr[result[0][0]], v_arr[des], weights[des]);
	return 0;
}


int main(int argc, char ** argv){
	//fflush(stdin);
	filename_a = malloc(50);
	strcpy(filename_a, argv[1]);
	filename_d = malloc(50);
	strcpy(filename_d, argv[2]);
	//printf("%s %s\n", filename_a, filename_d);
	Graph * graph = make_graph();
	//printf("v: %d e: %d\n", graph->num_vertices, graph->num_edges);
	while(1){
		char a[100];
		printf("enter command> ");
		scanf("%s", a);
		if(strcmp(a, "airports") == 0){
			//printf("here\n");
			FILE* f;
			f = fopen(filename_a, "r");
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
	//		printf("%s\n", a1);
			bellman_ford(graph, a1, a2);
		}
		else{
			printf("Not a valid input.  Type \'help\' for more.\n");
		}
	}
	printf("Good bye!\n");
	return 0;
}
	

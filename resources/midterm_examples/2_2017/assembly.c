typedef struct Vertex{
	char * name;
	int index;
}Vertex;
typedef struct Node{
	Vertex start;
	Vertex end;
}Node;
typedef struct Graph{
	Vertex * vertexes;
	int n;
	Node * nodes;
	int * visited;
}Graph;

void DFS(int i, Graph gr, Vertex * start) {
    gr.visited[start->index] = 1;
    for(int j=0;j<gr.n;j++){
        if (gr.visited[gr.nodes[j].end.index] == 0){
	    DFS(gr.vertexes[j].index, gr, &gr.nodes[i].end);     	}
    }
}

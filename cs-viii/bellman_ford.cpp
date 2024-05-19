#include<iostream>
#include<vector>
#include<climits>
#include<iomanip>
using namespace std;

struct Edge{
    int src, dst, w;
};

struct Graph{
    int V, E;
    vector<Edge> edges;
};

Graph* createGraph(int V, int E){
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edges.resize(E);
    return graph;
}

void addEdge(Graph* g, int src, int dst, int w, int index){
    g->edges[index].src = src;
    g->edges[index].dst = dst;
    g->edges[index].w = w;
}

void printMatrix(vector<vector<int>>& matrix){
    cout << "-\t";
    for(int h = 0; h < matrix.size(); h++){
        cout << h << "\t";
    }
    cout << endl;
    for(int i = 0; i < matrix.size(); i++){
        cout << i << "\t";
        for( int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] == INT_MAX){
                cout << "INF\t";
            }
            else{
                cout << matrix[i][j] << "\t";
            }
        } 
        cout << endl;
    }
}

void printPath(vector<int>& parent, int j){
    if(parent[j] == -1){
        return;
    }
    printPath(parent, parent[j]);
    cout << j << " ";
}

void printSolution(vector<int>& dst, vector<int>& parent, int src){
    cout << "Nodo\tDistancia\tCamino" << endl;
    for(int i = 0; i < dst.size(); i++){
        cout << src << " -> " << i << "\t" << dst[i] << "\t\t" << src << " ";
        printPath(parent, i);
        cout << endl;
    }
}

void bellmanFord(Graph* g, int src){
    int V = g-> V;
    int E = g->E;
    vector<int> dst(V, INT_MAX);
    vector<int> parent(V, -1);
    dst[src] = 0;
    
    for(int i = 1; i <= V - 1; i++){
        for(int j = 0; j < E; j++){
            int u = g->edges[j].src;
            int v = g->edges[j].dst;
            int weight = g->edges[j].w;
            if(dst[u] != INT_MAX && dst[u] + weight < dst[v]){
                dst[v] = dst[u] + weight;
                parent[v] = u;
            }
        }
    }

    for(int i = 0; i < E; i++){
        int u = g->edges[i].src;
        int v = g->edges[i].dst;
        int weight = g->edges[i].w;
        if(dst[u] != INT_MAX && dst[u] + weight < dst[v]){
            cout << "El grafo contiene un ciclo negativo\n";
            return;
        }
    }
    printSolution(dst, parent, src);
}

int main(){
    int V = 5;
    int E = 7;
    Graph* g = createGraph(V, E);

    addEdge (g,0,1,2,0);
    addEdge (g,0,2,-1,1);
    addEdge (g,1,2,3,2);
    addEdge (g,1,3,5,3);
    addEdge (g,2,3,2,4);
    addEdge (g,2,4,4,5);
    addEdge (g,3,4,3,6);

    cout << "NODOS:\nA = 0\tB = 1\tC = 2\tD = 3\tE = 4\n";

    cout << "Matriz de adyacencia: " << endl;
    vector<vector<int>> matrix(V, vector<int>(V, INT_MAX));
    for(int i = 0; i < E; i++){
        matrix[g->edges[i].src][g->edges[i].dst] = g->edges[i].w;
    }
   printMatrix(matrix);

   cout << "\nResultado de Bellman-Ford\n";
   bellmanFord(g,0);
   return 0;
}

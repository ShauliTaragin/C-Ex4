
#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

int min(const int arr[],int n);
int factorial(int size);
int arrayc(pnode * head,int values[], int size);
int dijkstra(pnode* head , int src , int dest , int bool);
void tsp(pnode *head);
void per(pnode *head, int *values, int right, int left, int *permutat, int *n);
//int Combi(char *str, int left, int right, int size, const int *values, int **ShortestPath);
void swap(int *x, int *y);
void clean(int **ShortestPath,int size);
pnode createnode(int id);
pedge createedge(int weight, pnode end);
void removeedge(pedge *edge_to_rm, int dest);
void remove_all_edges(pnode target, pnode *head);
void removenode(pnode *head, int node_to_remove);
void insert_node_cmd(pnode *head, int id_of_node_to_add);

#endif
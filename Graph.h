#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

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

int* dijkstra(pnode* head , int src , int dest , int bool);

pnode createnode(int id);
pedge createedge(int weight, pnode end);
void removeedge(pedge *edge_to_rm, int dest);
void remove_all_edges(pnode target, pnode *head);
void removenode(pnode *head, int node_to_remove);
void insert_node_cmd(pnode *head, int id_of_node_to_add);

#endif

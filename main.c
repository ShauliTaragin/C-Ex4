#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9999

int vertex = 0;

/*
typedef struct Graph *pnode;

typedef struct Node {
    int  weight;
    pnode dest;
    struct Node *next;
} Node, *pedge;

typedef struct Graph { //typedef,
    int id;
    pedge edges;
    struct Graph *next;
} Graph,*pnode;
*/
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

pnode createnode(int id) {
    pnode a = (pnode) malloc(sizeof(node));
    if (!a) {
        return NULL;
    }
    a->node_num = id;
    a->edges = NULL;
    a->next = NULL;
    return a;
}

pedge createedge(int weight, pnode end) {
    pedge a = (pedge) malloc(sizeof(edge));
    if (!a) {
        return NULL;
    }
    a->weight = weight;
    a->endpoint = end;
    a->next = NULL;
    return a;
}

//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0

void build_graph_cmd(pnode *head) {
    head;
    scanf("%d", &vertex); // vertex graph.
    char n;
    scanf("%s", &n);
    for (int i = 0; i < vertex; ++i) {
        int src_id;
        scanf("%d", &src_id);
        pnode checker = *head;
        pnode node_data;
        if (i==0) {
            head = createnode(src_id);
            node_data = head;
        }
        while (checker) {
            if (checker->node_num == src_id) {
                break;
            }
            checker = checker->next;
        }
        if (!checker) {
            node_data = createnode(src_id);
            if (!node_data) {
                exit(0);
            }
        }
        pnode temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node_data;
        int dest;
        while (scanf("%d", &dest)) {
            pedge edge_data = NULL;
            int weight;
            scanf("%d", &weight);
            pnode destination = *head;
            while (destination) { // creating dest node if dosent exist
                if (destination->node_num == dest) {
                    break;
                }
                destination = destination->next;
            }
            if (!destination) {
                edge_data = createedge(weight, destination);
                if (!edge_data) {
                    exit(0);
                }
            } else {
                //need to create the endpoint node and create the edge with it
                destination = createnode(dest);
                if (!destination) {
                    exit(0);
                } else {
                    pnode temp = *head;
                    while (temp->next) {
                        temp = temp->next;
                    }
                    temp->next = destination;
                }
                edge_data = createedge(weight, destination);
                if (!edge_data) {
                    exit(0);
                }
            }
            //need to add edge to node->edges and need to see where to add it
            pedge temp = node_data->edges;
            if (!temp) {
                node_data->edges = edge_data;
            }
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = edge_data;
        }
        if (getchar() != 'n') {
            break;
        }
    }
}


void insert_node_cmd(pnode *head);

void delete_node_cmd(pnode *head);

void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode *head);

void shortsPath_cmd(pnode head);

void TSP_cmd(pnode head);



/*struct Graph *createGraph(const char *ptr) {

    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));

    graph->head = NULL;

    int index = 0;
    int FLAG = 0;
    while (ptr[index] != '\n') {
        if (ptr[index] == 'n') {
            index++;
        }
        int src = (ptr[index++] - '0');
        while (ptr[index] != 'n') {
            if (index >= strlen(ptr)) {
                FLAG = 1;
                break;
            }
            struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
            struct Edge temp;
            temp.src = src;
            temp.dest = ptr[index++] - '0';
            newNode->dest = temp.dest;
            temp.weight = ptr[index++] - '0';
            newNode->weight = temp.weight;
*//*            newNode->next = graph->head[src];
            graph->head[src] = newNode;*//*
        }
        if (FLAG) {
            break;
        }
    }
    return graph;
}*/


/*void printGraph(struct Graph *graph) {
    for (int i = 0; i < N; i++) {
        struct Node *ptr = graph->head[i];
        while (ptr != NULL) {
            printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
            ptr = ptr->next;
            printf("\n");
        }
    }
}*/


int main() {
    int FLAG = 1;
    node *head = NULL;
    while (FLAG) {
        int c = getchar();
        switch (c) {
            case 'A':
                getchar();
                scanf("%d", &vertex); // vertex graph.
                char n;
                scanf("%s", &n);
                for (int i = 0; i < vertex; ++i) {
                    int src_id;
                    scanf("%d", &src_id);
                    pnode node_data;//maybe not good declaration.
                    if (i==0) {
                        head = createnode(src_id);
                        node_data = head;
                    }
                    pnode checker = head;
                    while (checker) {
                        if (checker->node_num == src_id) {
                            break;
                        }
                        checker = checker->next;
                    }
                    if (!checker) {
                        node_data = createnode(src_id);
                        if (!node_data) {
                            exit(0);
                        }
                        pnode temp = head;
                        while (temp->next) {
                            temp = temp->next;
                        }
                        temp->next = node_data;
                    }
                    else{
                        node_data = checker;
                    }
                    int dest;
                    while (scanf("%d", &dest)) {
                        pedge edge_data = NULL;
                        int weight;
                        scanf("%d", &weight);
                        pnode destination = head;
                        while (destination) { // creating dest node if dosent exist
                            if (destination->node_num == dest) {
                                break;
                            }
                            destination = destination->next;
                        }
                        if (destination) {
                            edge_data = createedge(weight, destination);
                            if (!edge_data) {
                                exit(0);
                            }
                        } else {
                            //need to create the endpoint node and create the edge with it
                            destination = createnode(dest);
                            if (!destination) {
                                exit(0);
                            } else {
                                pnode temp = head;
                                while (temp->next) {
                                    temp = temp->next;
                                }
                                temp->next = destination;
                            }
                            edge_data = createedge(weight, destination);
                            if (!edge_data) {
                                exit(0);
                            }
                        }
                        //need to add edge to node->edges and need to see where to add it
                        pedge temp = node_data->edges;
                        if (!temp) {
                            node_data->edges = edge_data;
                        } else {
                            while (temp->next) {
                                temp = temp->next;
                            }
                            temp->next = edge_data;
                        }
                    }
                    if (getchar() != 'n') {
                        break;
                    }
                }
/*                vertex = getchar() - '0';
                char *One = (char *) calloc(20, sizeof(char));
                int index = 0;
                for (c = getchar(); c != '\n'; c = getchar()) {
                    if (index == 19) {
                        One = (char *) realloc(One, 21 * 10 * sizeof(char));
                    }
                    if (c == ' ') { continue; }
                    else {
                        One[index++] = c;
                    }
                }
                One[index] = '\0';
                //printf("%s\n", One);
                printf("size of Vertex:");
                printf("%d\n", vertex);*/
/*                graph = createGraph(One);
                printGraph(graph);*/
                break;
/*            case 'B':
                getchar();
                char *Two = (char *) calloc(20, sizeof(char));
                int index2 = 0;
                for (c = getchar(); c != '\n'; c = getchar()) {
                    if (index2 == 20) {
                        Two = (char *) realloc(Two, 21 * 10 * sizeof(char));
                    }
                    if (c == ' ') { continue; }
                    else {
                        Two[index2++] = c;
                    }
                }
                Two[index2] = '\0';
                index2 = 1;
                int src = Two[0] - '0';
                struct Node *ptr = graph->head[src];
                if (ptr == NULL) {
                    vertex = vertex + 1;
                    while (index2 < strlen(Two) - 1) {
                        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
                        struct Edge temp;
                        temp.src = src;
                        temp.dest = Two[index2++] - '0';
                        newNode->dest = temp.dest;
                        temp.weight = Two[index2++] - '0';
                        newNode->weight = temp.weight;
                        newNode->next = graph->head[src];
                        graph->head[src] = newNode;
                    }
                    printGraph(graph);
                } else {
                    graph->head[src] = NULL;
                    while (index2 < strlen(Two) - 1) {
                        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
                        struct Edge temp;
                        temp.src = src;
                        temp.dest = Two[index2++] - '0';
                        newNode->dest = temp.dest;
                        temp.weight = Two[index2++] - '0';
                        newNode->weight = temp.weight;
                        newNode->next = graph->head[src];
                        graph->head[src] = newNode;
                    }
                    printGraph(graph);
                }
                break;
            case 'D': // fix the pointer's
                getchar();
                char *Three = (char *) calloc(20, sizeof(char));
                int index3 = 0;
                for (c = getchar(); c != '\n'; c = getchar()) {
                    if (index3 == 20) {
                        Three = (char *) realloc(Three, 21 * 10 * sizeof(char));
                    }
                    if (c == ' ') { continue; }
                    else {
                        Three[index3++] = c;
                    }
                }
                Three[index3] = '\0';
                graph->head[Three[0] - '0'] = NULL;
                vertex--;
                for (int i = 0; i < N; ++i) {
                    struct Node *curr = graph->head[i];
                    while (curr != NULL) {
                        //struct Node *temp = graph->head[i];
                        struct Node *prev = graph->head[i];
                        if (curr->dest == Three[0] - '0') {
                            graph->head[i] = graph->head[i]->next;
                            //free(temp);
                        }

                        curr = curr->next;
                    }
                }
                printGraph(graph);
                break;
            case 'S':
                printf("S");
                break;
                */
            case 'T':
                printf("T");
                FLAG = 0;
                break;
            default:
                printf("Please Enter a key");
        }
    }
}



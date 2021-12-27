#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9999

int vertex = 0;


struct Graph { //typedef
    struct Node *head[N];
};

struct Node {
    int dest, weight;
    struct Node *next;
};

struct Edge {
    int src, dest, weight;
};

struct Graph *createGraph(const char *ptr) {

    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));

    for (int i = 0; i < N; i++) {
        graph->head[i] = NULL;
    }

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
            newNode->next = graph->head[src];
            graph->head[src] = newNode;
        }
        if (FLAG) {
            break;
        }
    }
    return graph;
}

void del(struct Node *before_del) {
    struct Node *temp;
    temp = before_del;
    before_del = before_del->next;
    free(temp);
}

void printGraph(struct Graph *graph) {
    for (int i = 0; i < N; i++) {
        struct Node *ptr = graph->head[i];
        while (ptr != NULL) {
            printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
            ptr = ptr->next;
            printf("\n");
        }
    }
}


int main() {
    int FLAG = 1;
    struct Graph *graph = NULL;
    while (FLAG) {
        int c = getchar();
        switch (c) {
            case 'A':
                graph = NULL;
                getchar();
                vertex = getchar() - '0';
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
                printf("%d\n", vertex);
                graph = createGraph(One);
                printGraph(graph);
                break;
            case 'B':
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
            case 'T':
                printf("T");
                FLAG = 0;
                break;
            default:
                printf("Please Enter a key");
        }
    }
}



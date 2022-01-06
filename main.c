#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"




int vertex = 0;

typedef struct GRAPH_NODE_ *pnode;


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

//when do we want to do remove edge? when removing a node we want to remove every single edge from that node. for that we can know the node src and dest
void removeedge(pedge *edge_to_rm, int dest) {
    if (!(*edge_to_rm)) {
        return;
    }
    if ((*edge_to_rm)->endpoint->node_num == dest) {
        pedge temp = *edge_to_rm;
        *edge_to_rm = (*edge_to_rm)->next;
        free(temp);
    }
    if (*edge_to_rm) {
        pedge temp = *edge_to_rm;
        while (temp->next) {//why not run on temp itself?
            if (temp->next->endpoint->node_num == dest) {
                pedge temp2 = temp->next;
                temp->next = temp->next->next;
                free(temp2);
                break;
            }
            temp = temp->next;
        }
    }
}

void remove_all_edges(pnode target, pnode *head) {
    if ((target->edges)) { //only if there is an edge
        pedge temp = target->edges;
        while (temp->next) {
            removeedge(&(temp->next), temp->next->endpoint->node_num);
        }
        removeedge(&temp, temp->endpoint->node_num);
        target->edges = NULL;
    }
    //until now we removed all edges going out of the node. now we need to remove all edges which goes in to the node,
    // meaning we need to iterate over all the graph and search for mentions of the node
    int node_target_id = target->node_num;
    pnode node_iter = *head;
    while (node_iter) {
        pedge temp = node_iter->edges;
        if (temp) {//if this is false this means no edges for the current node therefore we move on to check the next node
            //not sure about the following if code at all. need to deal with if removing first edge not sure how.
            if (temp->endpoint->node_num == node_target_id) {
                pedge temp2 = temp;
                temp = temp->next;
                if (!(temp)) { //this is the case for which there is only one edge in the linked list and i wish to remove it.
                    removeedge(&temp2, node_target_id);
                    node_iter->edges = NULL;
                    continue;
                }
                node_iter->edges = temp;
                removeedge(&temp2, node_target_id);
            }
            //until here not sure
            while (temp->next) {
                if (temp->next->endpoint->node_num ==
                    node_target_id) {//this means i found an edge coming in to the node i wish to remove edges for
                    removeedge(&(temp->next), node_target_id);
                }
                temp = temp->next;//move on to the next edge
                if (!(temp)) {
                    break;
                }
            }
        }
        node_iter = node_iter->next;//move on to the next node
    }
}

void removenode(pnode *head, int node_to_remove) {
    if (!(*head)) {
        return;
    }
    if ((*head)->node_num == node_to_remove) {
        pnode temp = *head;
        if (!(temp->next)) { //this is the case for which there is only one node in the linked list and i wish to remove it.
            remove_all_edges(temp, head);
            *head = (*head)->next; //im only changing the head here so i can call the remove edge function with the orignal head
            free(temp);
            *head = NULL;
            return;
        }
        remove_all_edges(temp, head);
        *head = (*head)->next;//im only changing the head here so i can call the remove edge function with the orignal head
        free(temp);
        return;
    } else {
        pnode temp = *head;
        while (temp->next) {
            if (temp->next->node_num == node_to_remove) {
                pnode temp2 = temp->next;
                remove_all_edges(temp2, head);
                temp->next = temp->next->next;
                free(temp2);
                return;
            }
            temp = temp->next;
        }
    }
}

//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0

void insert_node_cmd(pnode *head, int id_of_node_to_add) {
    pnode node_data;
    if (!*head) { //need to check here if its *head or head
        *head = createnode(id_of_node_to_add);
    }
    pnode check = *head;
    int flag = 1;
    while (check) { // creating dest node if dosent exist
        if (check->node_num == id_of_node_to_add) {
            if ((check->edges)) { //only if there is an edge
                pedge temp = check->edges;
                while (temp->next) {
                    removeedge(&(temp->next), temp->next->endpoint->node_num);
                }
                removeedge(&temp,
                           temp->endpoint->node_num);//big problem here for some reason not freeing the edge only freeing inside the function not wokring out of it
                check->edges = NULL;
            }
            flag = 0;
            break;
        }
        check = check->next;
    }
    if (flag) {
        node_data = createnode(id_of_node_to_add);
        if (!node_data) {
            exit(0);
        }
        pnode temp4 = *head;
        while (temp4->next) {
            temp4 = temp4->next;
        }
        temp4->next = node_data;
    } else {
        node_data = check;
    }
    int dest;
    while (scanf("%d", &dest)) {
        pedge edge_data = NULL;
        int weight;
        scanf("%d", &weight);
        pnode pnod1 = *head;
        int flag2 = 0;
        while (pnod1) { // creating dest node if dosent exist
            if (pnod1->node_num == dest) {
                flag2 = 1;
                break;
            }
            pnod1 = pnod1->next;
        }
        if (flag2) { // problem here.
            edge_data = createedge(weight, pnod1);
            if (!edge_data) {
                exit(0);
            }
        } else {
            //need to create the endpoint node and create the edge with it
            pnod1 = createnode(dest);
            if (!pnod1) {
                exit(0);
            } else {
                pnode temp = *head;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = pnod1;
            }
            edge_data = createedge(weight, pnod1);
            if (!edge_data) {
                exit(0);
            }
        }
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
    //add ending point here
}


int main() {
    int FLAG = 1;
    node *head = NULL;
    int c =0;
    int first =1;
    while (FLAG) {
        if(first) {
            c = getchar();
        }
        switch (c) {
            case 'A':
                head = NULL;//make sure code dosen't get stuck here
                getchar();
                scanf("%d", &vertex); // vertex graph.
                char n;
                scanf("%s", &n);
                for (int i = 0; i < vertex; ++i) {
                    int src_id;
                    scanf("%d", &src_id);
                    pnode node_data;//maybe not good declaration.
                    if (i == 0) {
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
                    } else {
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
                    c = getchar();
                    if (c != 'n') {
                        first=0;
                        break;
                    }
                }
                break;
            case 'B':
                getchar();//for the space
                int to_add;
                scanf("%d", &to_add);
                insert_node_cmd(&head, to_add);
                first=1;
                break;
            case 'D':
                getchar();
                int node_to_remove;
                scanf("%d", &node_to_remove);
                removenode(&head, node_to_remove);
                first=1;
                break;
            case 'S':
                getchar();
                int dest, src;
                scanf("%d %d", &src, &dest);
                printf("Dijsktra shortest path: ");
                dijkstra(&head, src, dest, 1);//maybe send without head since in debugger it shows 2 heads
                first=1;
                break;
            case 'T': // A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 0 4 2 1 S 5 4
                //A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 f
                getchar();
                tsp(&head);
                first=1;
                break;
            default:
                // printGraph(head);
                FLAG = 0;
                break;
        }
    }
    pnode removie = head;
    while(removie!=NULL){
        removenode(&head , removie->node_num);
        removie = head;
    }
}

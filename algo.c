#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "Graph.h"

//first i wish to create an array to represent our graph so find max node num to create it

int* dijkstra(pnode* head , int src , int dest , int bool){
    int max = INT_MIN;
    pnode temp = *head;
    while(temp){
        if(temp->node_num >max){
            max=temp->node_num;
        }
        temp = temp->next;
    }
    int *Queue = (int*) malloc((max+1));
    int *dist = (int*) malloc((max+1));
    if((!Queue) || (!dist)){
        return NULL;
    }
    temp = *head;

    for (int i = 0; i <sizeof(Queue); ++i) {
        dist[i] = INT_MAX;
        Queue[i] = -1;//want to make sure when i add nodes whichever index dosent hold a node will be -1
    }
    dist[src]=0;

    while(temp){//filling queue with nodes
        int index = temp->node_num;
        Queue[index]=1;
        temp = temp->next;
    }

    while(1){
        //the next 8 rows of code is my way to check if queue is empty
        int min = INT_MAX;
        int curr_node_id = -1;
        for (int i = 0; i <sizeof(Queue); ++i) {
            if(Queue[i]==1){//only if queue[i] is 1 then that i node exits and we can
                if(dist[i]<min){
                    min = dist[i];
                    curr_node_id = i;//if its the min distance then i will work on this node
                }
            }
        }
        if(min==INT_MAX){
            break;
        }
        Queue[curr_node_id]=-1; //remove node from queue
        temp= *head;
        //This next loop will find the node we want to work on and temp will hold that node.
        //once we found that node we break and iterate over temps neighbors which are still in Queue
        while(temp){
            if(temp->node_num==curr_node_id){
                break;
            }
            temp=temp->next;
        }
        //in each iteration we will hold an edge coming out of temp and the node at the end of that edge\
        //meaning the node which is temps neighbor
        pedge edge_of_neighbor = temp->edges;
        while(edge_of_neighbor){
            int neighbors_id = edge_of_neighbor->endpoint->node_num;
            int alternative = dist[curr_node_id]+ (edge_of_neighbor->weight);
            if(alternative<dist[neighbors_id]){
                dist[neighbors_id]= alternative;
            }
            edge_of_neighbor = edge_of_neighbor->next;
        }
    }
    if(bool){
        printf("%d" , dist[dest]);
    }
    free(Queue);
    return dist;
}
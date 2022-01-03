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
        if(dist[dest]!=INT_MAX){
            printf("%d" , dist[dest]);
        }
        else{
            int a = -1;
            printf("%d" , a);
        }
    }
//    free(Queue);
    return dist;
}

void swap(char *x, char *y) {
    char c;
    c = *x;
    *x = *y;
    *y = c;
}

void clean(int **ShortestPath,int size){
    for (int i = 0; i < size; i++) {
        free(ShortestPath[i]);
    }
    free(ShortestPath);
}


int Combi(char *str, int left, int right, int size, const int *values, int **ShortestPath) {
    int min = INT_MAX;
    if (left == right) {
        int total = 0, max = INT_MAX, length = size - 1;
        for (int i = 0; i < length; i++) {
            int distfromdijkstra = ShortestPath[str[i] - '0'][values[str[i + 1] - '0']];
            if (distfromdijkstra == max) return distfromdijkstra;
            total = total + distfromdijkstra;
        }
        return total;
    } else {
        int temp = 0;
        for (int i = left; i <= right; i++) {
            swap((str + left), (str + i));
            temp = Combi(str, left + 1, right, size, values, ShortestPath);
            if (temp < min) min = temp;
            swap((str + left), (str + i));
        }
        return min;
    }
}

void tsp(pnode *head) {
    int NumberOfNodes = 0;
    scanf("%d", &NumberOfNodes);
    int values[NumberOfNodes];
    for (int i = 0; i < NumberOfNodes; ++i) {
        scanf("%d", &values[i]);
    }
    char str[NumberOfNodes];
    for (int i = 0; i < NumberOfNodes; i++) {
        str[i] = (char)(i + '0');
    }
    int **ShortestPath = (int **) malloc(sizeof(int *) * NumberOfNodes);
    for (int i = 0; i < NumberOfNodes; i++) {
        ShortestPath[i] = dijkstra(head, values[i], values[i], 0);
    }
    int temp = Combi(str, 0, NumberOfNodes - 1, NumberOfNodes, values,ShortestPath);
    if (temp == INT_MAX) {
        printf(" TSP shortest path: -1\n");
    }else{
        printf(" TSP shortest path: %d\n",temp);
    }
    //clean(ShortestPath,NumberOfNodes);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

//first i wish to create an array to represent our graph so find max node num to create it

int dijkstra(pnode* head , int src , int dest , int bool){
    int max = INT_MIN;
    pnode temp = *head;
    while(temp){
        if(temp->node_num >max){
            max= (temp->node_num);
        }
        temp = temp->next;
    }
    int *Queue = (int*) malloc(sizeof (int) * (max+1));
    int *dist = (int*) malloc(sizeof (int) * (max+1));
    if((!Queue) || (!dist)){
        return -1;
    }
    temp = *head;
    for (int i = 0; i <max+1 ; ++i) {
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
        for (int i = 0; i <max+1; ++i) {
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
            printf("%d \n" , dist[dest]);
        }
        else{
            int a = -1;
            printf("%d \n" , a);
        }
    }
    free(Queue);
    int ret = dist[dest];
    free(dist);
    return  ret;
}

void swap(int *x, int *y) {
    int c;
    c = *x;
    *x = *y;
    *y = c;
}


int factorial(int size){
    if(size < 0) return 0;
    if(size == 0) return 1;
    return factorial(size-1)*size;
}
int arrayc(pnode * head,int values[], int size){
    int dist = 0;
    for (int i = 0; i < size-1; ++i) {
        int dijk = dijkstra(head,values[i],values[i+1],0);
        if(dijk == INT_MAX){
            return INT_MAX;
        }
        dist += dijk;
    }
    return dist;
}

int min(const int arr[],int n){
    int index = 0;
    for (int i = 1; i <n; ++i) {
        if(arr[i]<arr[index]){index = i;}
    }
    return index;
}


void per(pnode *head, int *values, int right, int left ,int *permutat, int *n){
    if(right == left){
        permutat[(*n)++] = arrayc(head, values, left+1);
        return;
    }
    for (int i = right; i <=left; ++i) {
        swap((values + i), (values + right));
        per(head,values,right+1,left,permutat,n);
        swap((values+i),(values+right));
    }
}

void tsp(pnode *head){
    int NumberOfNodes = 0;
    scanf("%d", &NumberOfNodes);
    int values[NumberOfNodes];
    for (int i = 0; i < NumberOfNodes; ++i) {
        scanf("%d", &values[i]);
    }
    int f = factorial(NumberOfNodes);
    int permutations[f];
    int temp = 0;
    per(head,values,0,NumberOfNodes-1,permutations,&temp);
    int n = min(permutations,f);
    if(permutations[n] == INT_MAX){
        printf("TSP Shortest path: %d \n",-1);
    }else{
        printf("TSP shortest path: %d \n",permutations[n]);
    }
}

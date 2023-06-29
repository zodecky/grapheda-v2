#include <stdio.h>
#include <stdlib.h>

struct priorityqueue
{
    int qtd;
    int *vtx;
    int *dist;
};
typedef struct priorityqueue *queue;

queue createqueue(int);
void enqueue(queue, int, int);
int dequeue(queue);
int isempty(queue);
int isfull(queue);
void printqueue(queue);

#define SIZEQUEUE 100
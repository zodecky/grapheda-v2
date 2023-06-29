#include "priorityqueue.h"

/**
 * @brief Cria uma nova fila de prioridade
 *
 * @param n
 * @return queue
 */
queue createqueue(int n)
{
    queue q = malloc(sizeof(struct priorityqueue));
    q->qtd = 0;
    q->vtx = malloc(n * sizeof(int));
    q->dist = malloc(n * sizeof(int));
    return q;
}

/**
 * @brief Adiciona um elemento na fila de prioridade
 *
 * @param q
 * @param vtx
 * @param dist
 */
void enqueue(queue q, int vtx, int dist)
{
    if (isfull(q))
        return;
    q->vtx[q->qtd] = vtx;
    q->dist[q->qtd] = dist;
    q->qtd++;
}

/**
 * @brief Remove o elemento com menor distancia da fila de prioridade
 *
 * @param q
 * @return int (o elemento removido)
 */
int dequeue(queue q)
{
    if (isempty(q))
        return -1;
    int min = 0;
    for (int i = 1; i < q->qtd; i++)
        if (q->dist[i] < q->dist[min])
            min = i;
    int vtx = q->vtx[min];
    q->vtx[min] = q->vtx[q->qtd - 1];
    q->dist[min] = q->dist[q->qtd - 1];
    q->qtd--;
    return vtx;
}

/**
 * @brief Verifica se a fila de prioridade está vazia
 *
 * @param q
 * @return int
 */
int isempty(queue q)
{
    return q->qtd == 0;
}

/**
 * @brief Verifica se a fila de prioridade está cheia (a partir do tamanho máximo SIZEQUEUE)
 *
 * @param q
 * @return int
 */
int isfull(queue q)
{
    return q->qtd == SIZEQUEUE;
}

/**
 * @brief Imprime a fila de prioridade
 *
 * @param q
 */
void printqueue(queue q)
{
    for (int i = 0; i < q->qtd; i++)
        printf("%d ", q->vtx[i]);
    printf("\n");
}
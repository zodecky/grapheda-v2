// Gabriel Zagury de Magalhães - 2210912
// Thiago Henriques - 2211171

/*

                    INTRODUÇÃO

O código é um exemplo de implementação de um grafo em C,
com funções para adicionar arestas, imprimir o grafo,
encontrar o caminho mais curto entre dois vértices e realizar uma busca em profundidade (DFS) no grafo.
O grafo é representado por uma lista de adjacências,
onde cada vértice é representado por um nó que contém um ponteiro para a lista de seus vértices adjacentes.
O programa também define algumas constantes e estruturas de dados auxiliares,
como uma fila de prioridade para a busca do caminho mais curto.
*/

/*

                    ESTRUTURA DO PROGRAMA

O programa é dividido em 3:
    priorityqueue.c: implementação da fila de prioridade
    priorityqueue.h: interface da fila de prioridade (reusadas do trabalho huffman)
    grapheda.c: implementação do grafo e dos algoritmos
*/

#include <stdio.h>
#include <stdlib.h>

// modulos reutilizado do trabalho huffman (levemente alterado)
#include "priorityqueue.h"

// Defines letras como numeros para não
// dar erro de acessar vetor como char (comportamento indefinido)
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

// representa o infinito em Dijkstra
#define INFINITY 100000000

struct no
{
    int vtx;         // vertice
    int dist;        // distancia (se for 0 é o primeiro elemento / o proprio vertice)
    struct no *next; // proximo
};

struct Graph
{
    int qtd_vtx;                  // quantidade de vertices no grafo
    int *visitado;                // vetor de visitados (para DFS)
    struct no **lista_adjacentes; // lista de adjacentes (para guardar as arestas)
};

// Cria um novo no
struct no *criano(int v)
{
    struct no *novono = malloc(sizeof(struct no)); // abre espaço
    novono->vtx = v;
    novono->next = NULL;
    novono->dist = 0; // distancia para ele mesmo sempre é 0
    return novono;
}

struct Graph *criagraph(int vertices)
{
    struct Graph *graph = malloc(sizeof(struct Graph));               // aloca memoria para o grafo
    graph->lista_adjacentes = malloc(vertices * sizeof(struct no *)); // para a lista de adjacentes
    graph->visitado = malloc(vertices * sizeof(int));                 // e para o vetor de visitados

    graph->qtd_vtx = vertices; // define a quantidade de vertices pela entrada do usuario

    for (int i = 0; i < vertices; i++) // inicializa lista de adjacentes e lista visitados
    {
        graph->lista_adjacentes[i] = NULL;
        graph->visitado[i] = 0; // vai ser utilizado para a busca em profundidade
    }

    return graph;
}

// Adiciona uma aresta, ou seja uma ligação entre dois vértices nos dois sentidos
void addaresta(struct Graph *graph, int s, int d, int dist)
{
    // add aresta de s para d
    struct no *novono = criano(d);
    novono->next = graph->lista_adjacentes[s];
    graph->lista_adjacentes[s] = novono;
    graph->lista_adjacentes[s]->dist = dist;

    // add aresta de d para s
    novono = criano(s);
    novono->next = graph->lista_adjacentes[d];
    graph->lista_adjacentes[d] = novono;
    graph->lista_adjacentes[d]->dist = dist;
}

// imprime o grafo
void printgraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->qtd_vtx; v++) // para cada vertice
    {
        struct no *temp = graph->lista_adjacentes[v];
        printf("\n%c: ", v + 'A'); // imprime o vertice
        while (temp)
        {
            printf("%c -> ", temp->vtx + 'A'); // e sua lista de adjacentes
            temp = temp->next;
        }
        printf("(null)\n"); // null no final
    }
}

// caminho mais curto
int caminho_mais_curto(struct Graph *graph, int s, int d)
{
    int *dist = malloc(graph->qtd_vtx * sizeof(int));     // vetor de distancias
    int *prev = malloc(graph->qtd_vtx * sizeof(int));     // vetor de predecessores
    int *visitado = malloc(graph->qtd_vtx * sizeof(int)); // vetor de visitados
    for (int i = 0; i < graph->qtd_vtx; i++)              // inicializa os vetores
    {
        dist[i] = INFINITY; // distancia inicialmente é infinito
        prev[i] = -1;       // predecessores inicialmente é -1
        visitado[i] = 0;    // visitados inicialmente é 0
    }
    dist[s] = 0;                           // distancia de s para s é 0 (pois é o mesmo vértice)
    queue q = createqueue(graph->qtd_vtx); // cria uma fila de prioridade
    enqueue(q, s, dist[s]);                // adiciona s na fila
    while (!isempty(q))                    // enquanto a fila não estiver vazia
    {
        int u = dequeue(q);                           // remove o primeiro elemento da fila
        visitado[u] = 1;                              // marca como visitado
        struct no *temp = graph->lista_adjacentes[u]; // ponteiro para a lista de adjacencia do vertice
        while (temp)                                  // percorre a lista de adjacencia
        {
            int v = temp->vtx; // vertice adjacente
            if (!visitado[v])  // se o vertice não foi visitado
            {
                int alt = dist[u] + temp->dist;
                if (alt < dist[v]) // se a distancia atual for menor que a distancia anterior
                {
                    dist[v] = alt;          // atualiza a distancia
                    prev[v] = u;            // atualiza o predecessor
                    enqueue(q, v, dist[v]); // add na fila
                }
            }
            temp = temp->next; // proximo vertice adjacente
        }
    }

    /* Dentro do laço while, o valor de i é atualizado
     para o vértice anterior de i.
     Isso efetivamente rastreia o caminho mais curto
      do vértice de destino para o vértice de origem. */
    int i = d;
    while (prev[i] != -1)
    {
        i = prev[i];
    }
    return dist[d];
}

void DFS(struct Graph *graph, int vertex)
{
    struct no *adjList = graph->lista_adjacentes[vertex]; // ponteiro para a lista de adjacencia do vertice
    struct no *temp = adjList;                            // ponteiro temporario para percorrer a lista de adjacencia

    graph->visitado[vertex] = 1; // marca o vertice como visitado
    printf("%c ", vertex + 'A'); // imprime o vertice

    while (temp != NULL) // percorre a lista de adjacencia
    {
        int vtx_conectado = temp->vtx; // vertice conectado ao vertice atual

        if (graph->visitado[vtx_conectado] == 0) // se o vertice conectado ainda não foi visitado
        {
            DFS(graph, vtx_conectado); // chama a função recursivamente para o vertice conectado
        }
        temp = temp->next; // vai para o proximo vertice conectado
    }
}

int main()
{
    struct Graph *graph = criagraph(8); // H - A = 8
    addaresta(graph, A, B, 5);
    addaresta(graph, A, C, 4);
    addaresta(graph, A, D, 2);
    addaresta(graph, B, C, 6);
    addaresta(graph, B, E, 6);
    addaresta(graph, B, H, 9);
    addaresta(graph, C, D, 3);
    addaresta(graph, C, E, 4);
    addaresta(graph, D, E, 5);
    addaresta(graph, D, F, 9);
    addaresta(graph, E, F, 2);
    addaresta(graph, E, H, 6);
    addaresta(graph, F, H, 3);

    printgraph(graph);

    printf("\nCaminho mais curto: %c -> %c = %d\n", 'A', 'A', caminho_mais_curto(graph, A, A));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'B', caminho_mais_curto(graph, A, B));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'C', caminho_mais_curto(graph, A, C));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'D', caminho_mais_curto(graph, A, D));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'E', caminho_mais_curto(graph, A, E));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'F', caminho_mais_curto(graph, A, F));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'G', caminho_mais_curto(graph, A, G));
    printf("\n------- ---- -----: %c -> %c = %d\n", 'A', 'H', caminho_mais_curto(graph, A, H));

    printf("\nBusca por profundidade (DFS):\n");
    DFS(graph, A);
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct {
    int vertex;
    int distance;
} element;

typedef struct {
    int size;
    element heap[MAX_VERTICES];
} HeapType;

typedef struct Edge {
    int vertex;
    int weight;
    struct Edge* next;
} Edge;

typedef struct GraphType {
    int n;
    Edge* adj_list[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int foundOrder[MAX_VERTICES];

// 힙 초기화
void initMinHeap(HeapType* h) {
    h->size = 0;
}

void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 1; i <= g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 1; i <= g->n; i++)
        printf("%d ", found[i]);
    printf("\n\n");
}

// 힙에 요소 삽입
void insertMinHeap(HeapType* h, int vertex, int distance) {
    int i = ++(h->size);
    while ((i != 1) && (distance < h->heap[i / 2].distance)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;
}

// 최소값 삭제
element deleteMinHeap(HeapType* h) {
    int parent=1, child=2;
    element item = h->heap[1];
    element temp = h->heap[(h->size)--];

    while (child <= h->size) {
        if ((child < h->size) && (h->heap[child].distance > h->heap[child + 1].distance))
            child++;
        if (temp.distance <= h->heap[child].distance) 
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 그래프 초기화
void initGraph(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

// 연결 리스트 - 간선 추가
void insert_edge(GraphType* g, int start, int end, int weight) {
    Edge* node = (Edge*)malloc(sizeof(Edge));
    node->vertex = end;
    node->weight = weight;
    node->next = g->adj_list[start];
    g->adj_list[start] = node;

    node = (Edge*)malloc(sizeof(Edge));
    node->vertex = start;
    node->weight = weight;
    node->next = g->adj_list[end];
    g->adj_list[end] = node;
}

// Dijkstra 알고리즘
void Dijkstra(GraphType* g, int start) {
    HeapType h;
    initMinHeap(&h);

    int count = 0;

    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;
    insertMinHeap(&h, start, 0);

    while (h.size > 0) {
        element min = deleteMinHeap(&h);
        int u = min.vertex;

        if (found[u]) 
            continue;
        found[u] = TRUE;
        foundOrder[count++] = u;

        print_status(g);

        for (Edge* node = g->adj_list[u]; node != NULL; node = node->next) {
            int next = node->vertex;

            if (!found[next] && distance[u] + node->weight < distance[next]) {
                distance[next] = distance[u] + node->weight;
                insertMinHeap(&h, next, distance[next]);
            }
        }
    }

    printf("Found Order: ");
    for (int k = 0; k < count; k++) {
        printf("%d ", foundOrder[k]);
    }
    printf("\n");
}

// 
void GenerateGraph(GraphType* g) {
    g->n = 10;

    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));

    initGraph(g);
    GenerateGraph(g);
    
    printf("2. 연결 리스트를 이용해 구현\n\n");
    Dijkstra(g, 1);  

    free(g);
    return 0;
}

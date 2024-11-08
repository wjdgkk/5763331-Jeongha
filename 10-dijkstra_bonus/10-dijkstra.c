#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int found[MAX_VERTICES]; 
int distance[MAX_VERTICES];
int foundOrder[MAX_VERTICES];

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
    }
}

// 그래프 간선 추가
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start - 1][end - 1] = weight;
    g->weight[end - 1][start - 1] = weight;
}

// 최소 거리 선택 함수
int choose(int distance[], int n, int found[]) {
    int min = INF;
    int minpos = -1;

    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 현재 상태 출력 함수
void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 0; i < g->n; i++)
        printf("%d ", found[i]);
    printf("\n\n");
}

// 최단 경로 계산 함수
void Dijkstra(GraphType* g, int start) {
    int u;
    int count = 0;

    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    for (int i = 0; i < g->n; i++) {
        u = choose(distance, g->n, found); 
        if (u == -1) break; 

        found[u] = TRUE;
        foundOrder[count++] = u + 1; 
        print_status(g);

        
        for (int w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] != INF && distance[u] + g->weight[u][w] < distance[w]) {
                distance[w] = distance[u] + g->weight[u][w];
            }
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

// 그래프 생성 함수
void GenerateGraph(GraphType* g) {
    graph_init(g);

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
    GraphType g;

    GenerateGraph(&g);

    printf("1. 인접 행렬을 이용해 구현\n\n");
    Dijkstra(&g, 0);

    return 0;
}

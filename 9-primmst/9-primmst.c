#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

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

// 최소 거리 값을 갖는 노드의 인덱스 찾기
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

// Prim을 이용해 MST 찾기
void FindPrimMST(GraphType* g) {
    printf("Prim MST Algoruthm\n");
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        selected[i] = FALSE;
    }
    distance[0] = 0;

    for (int j = 0; j < g->n; j++) {
        int i = get_min_vertex(g->n);
        selected[i] = TRUE;
        if (distance[i] == INF) return;
        printf("정점 %d 추가\n", i + 1);  

        for (int v = 0; v < g->n; v++) {
            if (g->weight[i][v] != INF && !selected[v] && g->weight[i][v] < distance[v]) {
                distance[v] = g->weight[i][v];
            }
        }
    }
}

// 그래프 생성 함수
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

    graph_init(g);     
    GenerateGraph(g);   
    FindPrimMST(g);      // Prim 알고리즘으로 MST 찾기

    free(g);
    return 0;
}

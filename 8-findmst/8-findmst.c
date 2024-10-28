#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; 

// 부모 배열 초기화
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr가 속하는 집합을 반환
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

// 두 개의 원소가 속한 집합을 합침
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// 간선을 나타내는 구조체
struct Edge {
    int start, end, weight; 
};

typedef struct GraphType {
    int n; 
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// 간선 삽입 
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++; 
}

// qsort()에 사용되는 함수
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight); 
}

// Qsort 기반 크루스칼 알고리즘
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; 
    int uset, vset;
    struct Edge e;

    set_init(g->n);
    qsort(g->edges, g->n, sizeof(struct Edge), compare); 

    printf("Quick Based Kruskal\n");
    int i = 0;

    while (edge_accepted < (g->n - 1) && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) { 
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++; 
    }
}

typedef struct MinHeap {
    int size;
    int capacity;
    struct Edge* edge;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->edge = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    return minHeap;
}

void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙의 속성을 유지하기 위한 함수
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx; 
    int left = 2 * idx + 1;
    int right = 2 * idx + 2; 

    if (left < minHeap->size && minHeap->edge[left].weight < minHeap->edge[smallest].weight)
        smallest = left;

    if (right < minHeap->size && minHeap->edge[right].weight < minHeap->edge[smallest].weight)
        smallest = right;


    if (smallest != idx) {
        swap(&minHeap->edge[smallest], &minHeap->edge[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 힙에서 최솟값 추출
struct Edge extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        struct Edge infEdge = { 0, 0, INF }; 
        return infEdge;
    }

    struct Edge root = minHeap->edge[0]; 
    minHeap->edge[0] = minHeap->edge[minHeap->size - 1]; 
    minHeap->size--; 
    minHeapify(minHeap, 0);

    return root; 
}

// 간선 삽입
void insertMinHeap(MinHeap* minHeap, struct Edge edge) {
    if (minHeap->size == minHeap->capacity) {
        printf("MinHeap is full\n");
        return;
    }

    minHeap->size++;
    int i = minHeap->size-1;
    minHeap->edge[i] = edge; 

    while (i != 0 && minHeap->edge[(i - 1) / 2].weight > minHeap->edge[i].weight) {
        swap(&minHeap->edge[i], &minHeap->edge[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// MinHeap을 사용해 MST를 찾는 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    struct Edge e;

    MinHeap* minHeap = createMinHeap(g->n);
    for (int i = 0; i < g->n; i++) {
        insertMinHeap(minHeap, g->edges[i]);
    }
    set_init(g->n);

    printf("\n");
    printf("MinHeap Based Kruskal\n");
    while (edge_accepted < (g->n - 1)) {
        e = extractMin(minHeap);
        if (set_find(e.start) != set_find(e.end)) {
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(e.start, e.end);
        }
    }
    free(minHeap->edge);
    free(minHeap);
}

// edge 생성
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 6, 7);

    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);
    
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

    //그래프를 생성하는 함수
    GenerateGraph(g);

    QuickKruskal(g); // quick 기반 kruskal
    MinHeapKruskal(g); // minheap 기반 kruskal

    free(g);
    return 0;
}

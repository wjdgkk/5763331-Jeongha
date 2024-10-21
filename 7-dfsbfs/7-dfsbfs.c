#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

typedef struct {
    int data[MAX_VERTICES];
    int top;
} StackType;

typedef struct {
    int data[MAX_VERTICES];
    int front, rear;
} QueueType;

// 그래프
GraphMatType* create_mat_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void destroy_mat_graph(GraphMatType* g) {
    free(g);
}

void init_mat_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if ((g->n) >= MAX_VERTICES - 1) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

void insert_edge_mat_graph(GraphMatType* g, int s, int e) {
    if (g->n <= s || g->n <= e) {
        fprintf(stderr, "vertex number error");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// 스택
void init_stack(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return s->top == -1;
}

int is_full(StackType* s) {
    return s->top == MAX_VERTICES - 1;
}

void push(StackType* s, int item) {
    if (is_full(s)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    s->data[++(s->top)] = item;
}

int pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// 큐
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty_queue(QueueType* q) {
    return q->front == q->rear;
}

void enqueue(QueueType* q, int item) {
    q->data[q->rear++] = item;
}

int dequeue(QueueType* q) {
    return q->data[(q->front)++];
}

// 깊이 우선 탐색 함수
void dfs(GraphMatType* graph, int start, int target) {
    StackType s;
    init_stack(&s);
    int visited[MAX_VERTICES] = { 0 }; 
    int visitedCount = 0;
    int found = 0; 

    if (target >= graph->n || start >= graph->n) {
        printf("탐색 실패!\n");
        return;
    }

    push(&s, start); 
    visited[start] = 1; 
    visitedCount++; 

    while (!is_empty(&s)) {
        int node = pop(&s);
        printf("%d ", node); 

        if (node == target) { 
            printf("\n탐색 성공 : %d\n", target);
            printf("방문한 노드의 수 : %d\n", visitedCount);
            return;
        }

        for (int i = 0; i < graph->n; i++) {
            if (graph->adj_mat[node][i] && !visited[i]) {
                push(&s, node);
                push(&s, i); 
                visited[i] = 1; 
                visitedCount++; 
                found = 1; 
                break; 
            }
        }
        if (!found) {
            visitedCount++; 
        }
    }
}

// 너비 우선 탐색 함수
void bfs(GraphMatType* g, int start, int target) {
    QueueType queue;
    init_queue(&queue);

    int visited[MAX_VERTICES] = { 0 };
    int visitedCount = 0; 

    if (start >= g->n || target >= g->n) {
        printf("탐색 실패!\n");
        return;
    }

    enqueue(&queue, start);
    visited[start] = 1;
    printf("%d ", start);

    while (!is_empty_queue(&queue)) {
        int node = dequeue(&queue);

        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[node][i] && !visited[i]) {
                enqueue(&queue, i); 
                visited[i] = 1; 
                visitedCount++; 
                printf("%d ", i); 

                if (i == target) {
                    printf("\n탐색 성공 : %d\n", target);
                    printf("방문한 노드의 수 : %d\n", visitedCount);
                    return; 
                }
            }
        }
    }
}

// 그래프 초기화 하고 생성
void generateGraph(GraphMatType* g) {
    init_mat_graph(g);

    for (int i = 0; i < 11; i++) {
        insert_vertex_mat_graph(g, i);
    }

    insert_edge_mat_graph(g, 0, 2);
    insert_edge_mat_graph(g, 0, 4);
    insert_edge_mat_graph(g, 0, 5);
    insert_edge_mat_graph(g, 0, 6);
    insert_edge_mat_graph(g, 0, 9);
    insert_edge_mat_graph(g, 1, 4);
    insert_edge_mat_graph(g, 1, 5);
    insert_edge_mat_graph(g, 1, 7);
    insert_edge_mat_graph(g, 1, 10);
    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 4);
    insert_edge_mat_graph(g, 3, 4);
    insert_edge_mat_graph(g, 3, 5);
    insert_edge_mat_graph(g, 4, 5);
    insert_edge_mat_graph(g, 4, 6);
    insert_edge_mat_graph(g, 4, 7);
    insert_edge_mat_graph(g, 6, 7);
    insert_edge_mat_graph(g, 6, 8);
    insert_edge_mat_graph(g, 6, 9);
    insert_edge_mat_graph(g, 7, 10);
    insert_edge_mat_graph(g, 8, 9);
    insert_edge_mat_graph(g, 8, 10);
}

// 사용자와의 인터페이스 제공
void runUserInterface(GraphMatType* g) {
    char menu;
    int start, target;
    printf("---------------------------------\n");
    printf("|  1\t: 깊이 우선 탐색\t|\n");
    printf("|  2\t: 너비 우선 탐색\t|\n");
    printf("|  3\t: 종료\t\t\t|\n");
    printf("---------------------------------\n");

    while (1) {
        printf("\n\n메뉴 입력 : ");
        scanf_s("%d", &menu);

        switch (menu) {
        case 1: {
            printf("시작 번호와 탐색할 값 입력 : ");
            scanf_s("%d %d", &start, &target);
            dfs(g, start, target);
            break;
        }
        case 2: {
            printf("시작 번호와 탐색할 값 입력 : ");
            scanf_s("%d %d", &start, &target);
            bfs(g, start, target);
            break;
        }
        case 3:
            printf("프로그램을 종료합니다.\n");
            exit(1);
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

int main() {
    GraphMatType* g = (GraphMatType*)malloc(sizeof(GraphMatType));
    generateGraph(g);
    runUserInterface(g);
    destroy_mat_graph(g);
}

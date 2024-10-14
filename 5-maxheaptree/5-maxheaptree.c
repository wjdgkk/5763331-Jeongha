#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

typedef struct {
    TreeNode* data[MAX_SIZE];
    int front, rear;
} QueueType;

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return q->front == q->rear;
}

void enqueue(QueueType* q, TreeNode* item) {
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = item;
}

TreeNode* dequeue(QueueType* q) {
    q->front = (q->front + 1) % MAX_SIZE;
    return q->data[q->front];
}

TreeNode* new_node(int key) {
    TreeNode* temp;
    temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

// 트리의 노드를 레벨 순서로 출력
void print_node(TreeNode* root) {
    if (root == NULL) return;
    QueueType q;
    init_queue(&q);
    enqueue(&q, root);
    while (!is_empty(&q)) {
        TreeNode* temp = dequeue(&q);
        printf("%d ", temp->data);
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
    printf("\n");
}

// 힙 트리에 새로운 노드 삽입 (노드 이동 과정, 횟수 출력)
void insertMaxHeapTree_print(TreeNode** root, int key) {  
    if (*root == NULL) {
        *root = new_node(key);
        return;
    }

    QueueType q;
    init_queue(&q);
    enqueue(&q, *root);

    TreeNode* temp = NULL;
    while (!is_empty(&q)) {
        temp = dequeue(&q);
        if (temp->left == NULL) {
            temp->left = new_node(key);
            temp->left->parent = temp;
            temp = temp->left;
            break;
        }
        else if (temp->right == NULL) {
            temp->right = new_node(key);
            temp->right->parent = temp;
            temp = temp->right;
            break;
        }
        else {
            enqueue(&q, temp->left);
            enqueue(&q, temp->right);
        }
    }

    int count = 0;

    print_node(*root);
    while (temp->parent != NULL && temp->data > temp->parent->data) {
        int swap = temp->data;
        temp->data = temp->parent->data;
        temp->parent->data = swap;
        temp = temp->parent;
        print_node(*root);
        count++;
    }
    printf("노드가 이동된 횟수 : %d\n", count);
}

// 힙 트리에 새로운 노드 삽입 (출력은 하지 않음)
void insertMaxHeapTree(TreeNode** root, int key) {
    if (*root == NULL) {
        *root = new_node(key);
        return;
    }

    QueueType q;
    init_queue(&q);
    enqueue(&q, *root);

    TreeNode* temp = NULL;
    while (!is_empty(&q)) {
        temp = dequeue(&q);
        if (temp->left == NULL) {
            temp->left = new_node(key);
            temp->left->parent = temp;
            temp = temp->left;
            break;
        }
        else if (temp->right == NULL) {
            temp->right = new_node(key);
            temp->right->parent = temp;
            temp = temp->right;
            break;
        }
        else {
            enqueue(&q, temp->left);
            enqueue(&q, temp->right);
        }
    }

    while (temp->parent != NULL && temp->data > temp->parent->data) {
        int swap = temp->data;
        temp->data = temp->parent->data;
        temp->parent->data = swap;
        temp = temp->parent;

    }
}

// 힙 트리 생성 
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        insertMaxHeapTree(&root, inputData[i]);
    }
    return root;
}

// 루트 노드 삭제
void deleteMaxHeapTree(TreeNode** root) {
    if (*root == NULL) return;

    QueueType q;
    init_queue(&q);
    enqueue(&q, *root);
    TreeNode* last = NULL;

    while (!is_empty(&q)) {
        last = dequeue(&q);
        if (last->left) enqueue(&q, last->left);
        if (last->right) enqueue(&q, last->right);
    }

    int delete = (*root)->data;
    (*root)->data = last->data;

    if (last->parent) {
        if (last->parent->left == last)
            last->parent->left = NULL;
        else
            last->parent->right = NULL;
    }

    if (last == *root) {
        free(last);
        *root = NULL;
        return;
    }
    free(last);

    TreeNode* temp = *root;
    int count = 1;
    print_node(*root);
    while (1) {
        TreeNode* largest = temp;
        if (temp->left && temp->left->data > largest->data)
            largest = temp->left;
        if (temp->right && temp->right->data > largest->data)
            largest = temp->right;

        if (largest == temp) break;

        int swap = temp->data;
        temp->data = largest->data;
        largest->data = swap;
        temp = largest;
        print_node(*root);
        count++;
    }

    printf("노드가 이동된 횟수 : %d\n", count);
}

// 트리 레벨별 출력
void printTreeLevel(TreeNode* root) {
    if (root == NULL) return;
    QueueType q;
    init_queue(&q);
    enqueue(&q, root);
    int level = 1;
    while (!is_empty(&q)) {
        int level_size = (q.rear - q.front + MAX_SIZE) % MAX_SIZE;
        printf("[%d] ", level);
        for (int i = 0; i < level_size; i++) {
            TreeNode* temp = dequeue(&q);
            printf("%d ", temp->data);
            if (temp->left) enqueue(&q, temp->left);
            if (temp->right) enqueue(&q, temp->right);
        }
        level++;
        printf("\n");
    }
}

// 사용자 인터페이스 제공
// 노드 추가, 삭제, 트리 레벨별 출력, 프로그램 종료 작업 
void runUserInterface(TreeNode** root) {
    char menu;
    int value;
    printf("-------------------------\n");
    printf("|  i\t: 노드 추가\t|\n");
    printf("|  d\t: 노드 삭제\t|\n");
    printf("|  p\t: 레벨별 출력\t|\n");
    printf("|  c\t: 종료\t\t|\n");
    printf("-------------------------\n");

    while (1) {
        printf("\n\n메뉴 입력 : ");
        scanf_s(" %c", &menu);

        switch (menu) {
        case 'i': {
            printf("추가할 값 입력: ");
            scanf_s("%d", &value);
            insertMaxHeapTree_print(root, value);
            break;
        }
        case 'd':
            deleteMaxHeapTree(root);
            break;
        case 'p':
            printf("트리 레벨별 출력\n");
            printTreeLevel(*root);
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            return; 
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

// 메모리 해제
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = generateMaxHeapTree(inputData, size);

    runUserInterface(&root);

    freeTree(root);
    return 0;
}

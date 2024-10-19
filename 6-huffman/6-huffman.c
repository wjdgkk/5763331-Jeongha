#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 힙 구조체 동적으로 생성
HeapType* createHeap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 구조체 초기화
void initHeap(HeapType* h) {
    h->heap_size = 0;
}

// 최소 힙에 새로운 요소 삽입
void insertMinHeap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;

    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// 최솟값 삭제하고 힙 구조 재정렬
element deleteMinHeap(HeapType* h) {
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key)
            break;
        
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 이진 트리노드 생성 함수
TreeNode* makeTree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 이진 트리 노드 해제 함수
void destroyTree(TreeNode* root) {
    if (root == NULL)
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// 자식 노드가 없는 경우 1을 반환, 그렇지 않으면 0을 반환
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 배열 요소 출력
void printArray(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 허프만 코드 출력
void printHuffmanCodes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;
        printHuffmanCodes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;
        printHuffmanCodes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        printArray(codes, top);
    }
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = createHeap();
    initHeap(heap);
    for (int i = 0; i < size; i++)
{
        node = makeTree(NULL, NULL);
        e.ch = node->ch = characters[i];
        e.key = node->weight = frequencies[i];
        e.ptree = node;
        insertMinHeap(heap, e);
    }
    for (int j = 1; j < size; j++) {
        e1 = deleteMinHeap(heap);
        e2 = deleteMinHeap(heap);

        x = makeTree(e1.ptree, e2.ptree);

        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("///%d + %d -> %d \n", e1.key, e2.key, e.key);
        insertMinHeap(heap, e);
    }
    e = deleteMinHeap(heap);
    printHuffmanCodes(e.ptree, codes, top);
    destroyTree(e.ptree);
    free(heap);
}

int main(void)
{
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}

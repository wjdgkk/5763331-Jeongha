#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000

int compareCount = 0;
int searchCount = 0;

typedef struct Node {
    int key; 
    struct Node* left; 
    struct Node* right;
    int height; 
} Node;

// 노드의 높이 반환
int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// 노드의 균형인수 반환
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 노드 동적으로 생성
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// 오른쪽으로 회전시키는 함수
Node* rotateRight(Node* y) {
    Node* x = y->left; 
    Node* T2 = x->right; 

    x->right = y; 
    y->left = T2; 

    y->height = 1 + getHeight(y->left) > getHeight(y->right)
        ? getHeight(y->left) : getHeight(y->right);
    x->height = 1 + getHeight(x->left) > getHeight(x->right)
        ? getHeight(x->left) : getHeight(x->right);

    return x; 
}

// 왼쪽으로 회전시키는 함수
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x; 
    x->right = T2; 

    x->height = 1 + getHeight(x->left) > getHeight(x->right)
        ? getHeight(x->left) : getHeight(x->right);
    y->height = 1 + getHeight(y->left) > getHeight(y->right)
        ? getHeight(y->left) : getHeight(y->right);

    return y;
}

// AVL 트리 노드 삽입
Node* insertAVL(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    return node;

    node->height = 1 + getHeight(node->left) > getHeight(node->right)
        ? getHeight(node->left) : getHeight(node->right);

    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// 최소값 찾는 함수
Node* minNode(Node* node) {
    Node* current = node; 
    while (current->left != NULL)
        current = current->left;
    return current; 
}

// 트리에서 노드 삭제
Node* deleteAVL(Node* root, int key) {
    if (root == NULL) 
        return root; 

    if (key < root->key)
        root->left = deleteAVL(root->left, key); 
    else if (key > root->key)
        root->right = deleteAVL(root->right, key); 
    else {
        if (root->left == NULL) {
            Node* temp = root->right; 
            free(root); 
            return temp; 
        }
        else if (root->right == NULL) {
            Node* temp = root->left; 
            free(root); 
            return temp; 
        }
        Node* temp = minNode(root->right); 
        root->key = temp->key; 
        root->right = deleteAVL(root->right, temp->key); 
    }

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) 
        ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root); 

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root); 

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left); 
        return rotateRight(root); 
    }

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right); 
        return rotateLeft(root); 
    }
    return root;
}

// 이진 트리 노드 삽입
Node* insertBinary(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertBinary(node->left, key);
    else if (key > node->key)
        node->right = insertBinary(node->right, key);
    return node;
}

// 이진 트리에서 노드 삭제
Node* deleteBinary(Node* root, int key) {
    if (root == NULL) 
        return root; 

    if (key < root->key)
        root->left = deleteBinary(root->left, key); 
    else if (key > root->key)
        root->right = deleteBinary(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root); 
            return temp; 
        }
        else if (root->right == NULL) {
            Node* temp = root->left; 
            free(root); 
            return temp; 
        }
        Node* temp = minNode(root->right); 
        root->key = temp->key; 
        root->right = deleteBinary(root->right, temp->key); 
    }
    return root;
}

// 트리 메모리 해제 
void freeTree(Node* root) {
    if (root == NULL) return; 
    freeTree(root->left);
    freeTree(root->right); 
    free(root); 
}

// 트리에서 노드 탐색
Node* search(Node* root, int key, int* compareCount) {
    if (root == NULL) 
        return NULL;

    (*compareCount)++;
    if (key == root->key) 
        return root;

    (*compareCount)++;
    if (key < root->key)
        return search(root->left, key, compareCount);
    return search(root->right, key,compareCount);
}

// AVL 트리 배치 함수
void doAVLBatch(Node* root) {
    int compareCt = 0;
    int searchCt = 0;

    for (int i = 0; i < SIZE; i++) {
        int A = rand() % 3; 
        int B = rand() % 1000; 

        switch (A) {
        case 0:
            root = insertAVL(root, B); 
            break;
        case 1:
            root = deleteAVL(root, B); 
            break;
        case 2:
            searchCt++;
            search(root, B, &compareCt);
            break;
        }
    }
    compareCount = compareCt;
    searchCount = searchCt;
}

// 이진 트리 배치 함수
void doBinaryBatch(Node* root) {
    int compareCt = 0;
    int searchCt = 0;

    for (int i = 0; i < SIZE; i++) {
        int A = rand() % 3; 
        int B = rand() % 1000; 

        if (A == 0) {
            root = insertBinary(root, B);
        }
        else if (A == 1) {
            root = deleteBinary(root, B);
        }
        else if (A == 2) {
            searchCt++;
            search(root, B, &compareCt);
        }
    }
    compareCount = compareCt;
    searchCount = searchCt;
}

int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}

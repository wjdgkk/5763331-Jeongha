#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef TreeNode* element;

typedef struct StackNode {
    element data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return (s->top == NULL);
}

void push(LinkedStackType* s, element item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

element pop(LinkedStackType* s) {
    if (is_empty(s)) return NULL;

    StackNode* temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    free(temp);
    return data;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

// 0:left 1:right
void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    init(&s);
    
    int sum = 0;

    if (root == NULL) return 0;
    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }

        nptr = pop(&s);
        sum += nptr->data;
        nptr = nptr->right;
    }

    printf("Sum of nodes: %d\n", sum);
    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    init(&s);
    
    int count = 0;

    if (root == NULL) return 0;
    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }

        nptr = pop(&s);
        count++;
        nptr = nptr->right;
    }

    printf("Number of nodes: %d\n", count);
    return count;
}

int GetHeightOfTree(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    init(&s);

    int maxHeight = 0;
    int currentHeight = 0;

    if (root == NULL) return 0;
    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            currentHeight++;
            nptr = nptr->left;
        }
        nptr = pop(&s);

        if (nptr->left == NULL && nptr->right == NULL) {
            if (currentHeight > maxHeight) {
                maxHeight = currentHeight;
            }
        }

        currentHeight--; 
        nptr = nptr->right;
    }

    printf("Height of Tree: %d\n", maxHeight);
    return maxHeight;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    init(&s);

    int leafCount = 0;
    
    if (root == NULL) return 0;
    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }

        nptr = pop(&s);
        if (nptr->left == NULL && nptr->right == NULL) {
            leafCount++;
        }
        nptr = nptr->right;
    }

    printf("Number of leaf nodes: %d\n", leafCount);
    return leafCount;
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateLinkTree(root);

    GetSumOfNodes(root);
    GetNumberOfNodes(root);
    GetHeightOfTree(root);
    GetNumberOfLeafNodes(root);

    return 0;
}

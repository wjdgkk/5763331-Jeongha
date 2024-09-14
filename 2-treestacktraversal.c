#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
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
    printf("push(%d) ", item->data);
}

element pop(LinkedStackType* s) {
    if (is_empty(s)) return NULL;

    StackNode* temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    free(temp);
    printf("pop(%d) visit(%d)\n", data->data, data->data);

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

void LinkPreOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            printf("visit(%d)\n", nptr->data);
            nptr = nptr->left;
        }

        if (!is_empty(&s)) {
            nptr = pop(&s);
            nptr = nptr->right;
        }
    }
}

void LinkInOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }

        nptr = pop(&s);

        nptr = nptr->right;
    }
}

void LinkPostOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    TreeNode* last_visited = NULL;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }

        TreeNode* top_node = s.top->data;

        if (top_node->right == NULL || top_node->right == last_visited) {
            pop(&s);
            last_visited = top_node;
        }
        else {
            nptr = top_node->right;
        }
    }
    printf("\n");
}

void LinkOrders(TreeNode* root) {
    printf("LinkedPreOrder : \n");
    LinkPreOrder(root); 
    printf("\n");
    printf("LinkedInOrder : \n");
    LinkInOrder(root);
    printf("\n");
    printf("LinkedPostOrder : \n");
    LinkPostOrder(root);
    printf("\n");
}

int main()
{
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateLinkTree(root);

    //순회는 전위,중위,후위 모두 진행
    //이때 모든 push와 pop은 출력
    LinkOrders(root);
    return 0;
}

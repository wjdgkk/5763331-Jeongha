#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

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

void LinkPreOrder(TreeNode* np) {
    if (np != NULL) {
        printf("%d ", np->data);
        LinkPreOrder(np->left);
        LinkPreOrder(np->right);
    }
}

void LinkInOrder(TreeNode* np) {
    if (np == NULL) return;
    
    printf("push(%d) ", np->data);
    LinkInOrder(np->left);
    printf("pop(%d) visit(%d) ", np->data, np->data);
    LinkInOrder(np->right);
}

void LinkPostOrder(TreeNode* np) {
    if (np != NULL) {
        LinkPostOrder(np->left);
        LinkPostOrder(np->right);
        printf("%d ", np->data);
    }
}

/*void LinkOrders(TreeNode* root) {
    LinkPreOrder(root); 
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
    printf("\n");
}*/

int main()
{
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateLinkTree(root);

    //순회는 전위,중위,후위 모두 진행
    //이때 모든 push와 pop은 출력
    //LinkOrders(root);
    LinkInOrder(root);
    return 0;
}

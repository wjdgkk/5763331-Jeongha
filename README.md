#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* new_noede(int key) {
	TreeNode* temp;

	temp = malloc(sizeof(TreeNode));
	temp->data = key;
	temp->right = temp->left = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	if (root == NULL)
		return new_node(key);

	if (root->data == key) return root;
	else if (root->data > key) root->left = insert_node(root->left, key);
	else root->right = insert_node(root->right, key);

	return root;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root = NULL;
	int size = sizeof(inputData) / sizeof(inputData[0]);
	for (int i = 0; i < size; i++) {
		root = insert_node(root, inputData[i]);
	}
	return root;
}

void BinaryTreeInOrder(TreeNode* root) {
	if (root != NULL) return;
	BinaryTreeInOrder(root->left);
	printf("%d ", root->data);
	BinaryTreeInOrder(root->right);
}

int main() {
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,7 };
	// 트리 생성, *root에 트리를 생성해 반환
	TreeNode* root = GenerateBinaryTree(inputData);
	BinaryTreeInOrder(root);
	return 0;
}

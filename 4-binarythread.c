#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct ThreadNode {
	int data;
	struct ThreadNode* left;
	struct ThreadNode* right;
	int leftThread;
	int rightThread;
} ThreadNode;

TreeNode* new_node(int key) {
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

TreeNode* GenerateBinaryTree(int inputData[], int size) {
	TreeNode* root = NULL;

	printf("Binary tree inorder: ");
	for (int i = 0; i < size; i++) {
		root = insert_node(root, inputData[i]);
	}
	return root;
}

void BinaryTreeInOrder(TreeNode* root) {
	
	if (root == NULL) return;
	BinaryTreeInOrder(root->left);
	printf("%d ", root->data);
	BinaryTreeInOrder(root->right);
}

ThreadNode* new_thread_node(int key) {
	ThreadNode* temp;
	temp = malloc(sizeof(ThreadNode));
	temp->data = key;
	temp->left = temp->right = NULL;
	temp->leftThread = temp->rightThread = 0;
	return temp;
}

ThreadNode* insert_thread_node(ThreadNode* root, int key) {
	if (root == NULL)
		return new_thread_node(key);

	if (root->data == key) return root;
	else if (root->data > key) {
		if (root->leftThread == 0) {
			root->left = insert_thread_node(root->left, key);
		}
	}
	else if (root->data < key) {
		if (root->rightThread == 0) {
			root->right = insert_thread_node(root->right, key);
		}
	}

	return root;
}

ThreadNode* GenerateThreadTree(int inputData[], int size) {
	ThreadNode* root = NULL;

	printf("\nThread tree inorder: ");
	for (int i = 0; i < size; i++) {
		root = insert_thread_node(root, inputData[i]);
	}
	return root;
}

void ThreadTreeInOrder(ThreadNode* root) {
	if (root == NULL) return;
	ThreadTreeInOrder(root->left);
	printf("%d ", root->data);
	ThreadTreeInOrder(root->right);
}

int main() {
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };
	int size = sizeof(inputData) / sizeof(inputData[0]);

	TreeNode* root = GenerateBinaryTree(inputData, size);
	BinaryTreeInOrder(root);

	ThreadNode* troot = GenerateThreadTree(inputData, size);
	ThreadTreeInOrder(troot);

	free(root);
	free(troot);

	return 0;
}



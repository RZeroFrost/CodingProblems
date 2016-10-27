#include "stdafx.h"
#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <thread>


using namespace std;

//Step 1: what is a tree. Node(data)(left,right)
struct node {
	int data;
	struct node* left;
	struct node* right;

};

//Test Helper: newNode functionality
struct node* newNode(int data) {
	struct node* n = (struct node*)malloc(sizeof(struct node));
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return n;
}

//Step2: Solution function -> Operating on the assumption that we are given the root
bool hasSumPath(struct node* root, int sum) {
	bool answer = 0;
	int remSum = sum - root->data;
	//Case1: root = null -> return true only if sum == 0
	if (root == NULL) {
		if (sum == 0) return true;
		else return false;
	}
	//Case2: root has no children -> return true if root->data == sum
	else if (root->left == NULL && root->right == NULL) {
		if (sum == root->data) return true;
		else return false;
	}
	//Case3: check both children recursively.
	else {
		//Base Case: we reach leaf and remSum == 0 -> return true
		if (remSum == 0 && root->left == NULL && root->right == NULL) {
			return 1;
		}
		if (root->left) {		//Check leftwise if remaining sum is present until we hit base Case.
			answer = answer || hasSumPath(root->left, remSum);
		}
		if (root->right) {		//Check rightwise if remaining sum is present until we hit base Case.
			answer = answer || hasSumPath(root->right, remSum);
		}
		return answer;			//Return final answer after recursive iteration.
	}
}

/*
//TEST PROGRAM DRIVER: use newNode(int data) to initialize new node with given data for test.
int main() {
	//Build a tree -> (TEST CASE: root->left->left is a leaf, the path  = 21)
	struct node* testRoot = newNode(10);
	testRoot->left = newNode(8);
	testRoot->right = newNode(2);
	testRoot->left->left = newNode(3);
	testRoot->left->right = newNode(5);

	//Test run / debug printing method
	if (hasSumPath(testRoot, 21)) {
		cout << "There is a root to leaf path of sum: " << " " << 21 << endl;
	}
	else cout << "No path for given sum found!" << endl;
	Sleep(5000);

}
*/
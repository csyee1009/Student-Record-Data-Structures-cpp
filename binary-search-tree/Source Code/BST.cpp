#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"

using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}





/////////////////////////////////////////////////
			// (b) - Print deepest nodes

bool BST::deepestNodes() {
	BTNode* cur;

	if (empty()) {
		return false;
	}

	Queue q;
	q.enqueue(root);

	const int maxLevel = 100; // Maximum nodes expected at one level
	BTNode* levelNodes[maxLevel]; // Array to hold nodes at the current level
	int levelCount = 0; // Number of nodes at the current level

	// Level-order traversal
	while (!q.empty()) {
		int levelSize = q.size();
		levelCount = 0; // Reset for this level

		for (int i = 0; i < levelSize; i++) {
			q.dequeue(cur);
			levelNodes[levelCount++] = cur; // Store current level's node

			if (cur->left != NULL)
				q.enqueue(cur->left);
			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
		// After the loop, levelNodes[] holds the current level's nodes
	}

	// After traversal, levelNodes[] contains deepest level nodes
	cout << "Student IDs at the deepest level:" << endl;
	for (int i = 0; i < levelCount; i++) {
		cout << levelNodes[i]->item.id << endl;
	}

	return true;
}



/////////////////////////////////////////////////
			// (c) - Display student

bool BST::display(int order, int source) {
	if (empty()) {
		return false;
	}

	Queue q;

	// Traverse tree based on selected order
	if (order == 1) {
		traverseAscending(root, q); // In-order traversal
	}
	else if (order == 2) {
		traverseDescending(root, q); // Reverse in-order traversal
	}
	else {
		return false; // Invalid order
	}

	BTNode* node;

	// Print to console
	if (source == 1) {
		while (!q.empty()) {
			q.dequeue(node);
			node->item.print(cout);
			cout << "------------------------------" << endl;
		}
	}
	// Print to file
	else if (source == 2) {
		ofstream outFile("student-info.txt");

		if (!outFile) {
			cout << "Failed to open file." << endl;
			return false;
		}

		while (!q.empty()) {
			q.dequeue(node);
			node->item.print(outFile);
			outFile << "------------------------------" << endl;
		}
		outFile.close();
		cout << "Successfully saved in file." << endl;
	}

	return true;
}


void BST::traverseAscending(BTNode* node, Queue& q) {
	if (node == NULL) return;

	// Traverse the tree in ascending order (in-order traversal)
	// Enqueue each node into the queue.
	traverseAscending(node->left, q);
	q.enqueue(node);
	traverseAscending(node->right, q);
}


void BST::traverseDescending(BTNode* node, Queue& q) {
	if (node == NULL) return;

	// Traverse the tree in descending order (reverse in-order traversal)
	// Enqueue each node into the queue.
	traverseDescending(node->right, q);
	q.enqueue(node);
	traverseDescending(node->left, q);
}


/////////////////////////////////////////////////
			// (d) - Clone Subtree


bool BST::CloneSubtree(BST t1, type item) {

	ClearSubtree(); // Clear t2 before cloning

	BTNode* cur = t1.root;
	bool  founditem = false;

	// Check if t1 is empty
	if (t1.empty()) {
		cout << endl<< "The tree is empty!" << endl;
		return false;
	}
	

	// Travel t1 to look for item
	CloneSubtree2(cur, item, founditem);


	if (!founditem) {
		return false; // Item not found in t1
	}
	
	

	return true;
}


void BST::CloneSubtree2(BTNode* cur, type item, bool &founditem ) {

	if (cur == NULL) {
		return;
	}

	// Found the node to clone
	if (cur->item.compare2(item)) {
		founditem = true;
		CloneSubtree3(cur); // Start cloning subtree
	}

	// If item is smaller, go left; otherwise go right
	if (cur->item.compare1(item)) {
		return CloneSubtree2(cur->left, item, founditem);
	}
	else {
		return CloneSubtree2(cur->right, item, founditem);
	}

}


void BST::CloneSubtree3(BTNode* cur) {

	if (cur == NULL) {
		return;
	}
	insert(cur->item); // Insert current node's item
	CloneSubtree3(cur->left); // Clone left subtree
	CloneSubtree3(cur->right); // Clone right subtree
}


void BST::ClearSubtree() {

	// Clears the current tree by removing all nodes
	while (root != NULL) {
		remove(root->item);
	}
}



/////////////////////////////////////////////////
			// (e) - Print Level Nodes

bool BST::printLevelNodes() {

	BTNode* cur;
	Queue q;
	int level = 1; // Keeps track of current level

	if (empty()) {
		return false; // Return false if the tree is empty
	}
	q.enqueue(root); // Start from the root node

	while (!q.empty()) {

		int levelSize = q.size(); // Number of nodes at current level
		cout << "Level " << level << " nodes: ";

		// Process all nodes at the current level
		for (int i = 0; i < levelSize; i++) {
			q.dequeue(cur); // Get the front node from the queue

			if (cur != NULL) {
				cout << cur->item.id << " "; // Print node ID

				// Enqueue left and right children if they exist
				if (cur->left != NULL) {
					q.enqueue(cur->left);
				}
				if (cur->right != NULL) {
					q.enqueue(cur->right);
				}
			}
		}
		cout << endl;  
		level++; // Move to next level
	}

	return true;  // Indicate that the tree was printed successfully
}


/////////////////////////////////////////////////
			// (f) - Print Path

bool BST::printPath() {

	if (empty()) {
		return false; // Return false if tree is empty
	}
	cout << endl;
	cout << "Below are all the external paths for the tree: " << endl << endl;

	bool gotoright = false;
	int path[1000], n=0; // Array to store the path and its current length
	printPath2(root,path, n); // Start recursive path printing from root
	return true;
}


void BST::printPath2(BTNode* cur, int path[], int& n) {

	if (cur == NULL) {
		return; // Base case: null node
	}

	path[n++] = cur->item.id; // Add current node ID to path

	// If current node is a leaf, print the path
	if (cur->left == NULL && cur->right == NULL) {
		for (int i = 0; i < n; i++) {
			cout << path[i] << " ";
			
		}
		cout << endl;
		
	}
	else {
		// Recursively explore left and right subtrees
		printPath2(cur->left, path,n);
		printPath2(cur->right, path,n);
	}
	n--; // Backtrack after exploring current node
}



















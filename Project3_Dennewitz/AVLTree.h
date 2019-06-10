/**
Ethan Dennewitz
CS-3100
Project 3: AVL Tree
*/
#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
The AVLNode is a node that is being stored in the AVLTree. The AVLnode contains pointers to the left child, right child, and parent nodes. 
*/
class AVLnode {
public:
	AVLnode * rightChild;
	AVLnode * leftChild;
	AVLnode * parent;
	int key;
	string value;
	int height;
	AVLnode(int newKey, string newValue) {
		key = newKey;
		value = newValue;
		rightChild = nullptr;
		leftChild = nullptr;
		parent = nullptr;
		height = 1;
	}
};

/*
The AVLTree class is a self balancing binary search tree . The tree remains balanced by constantly monitoring the height of the tree and
preforming one or more single or double rotation when the tree becomes imbalanced on either the left or right.
*/
class AVLTree {
public:
	AVLnode * head;
	int size;
	AVLTree();
	//required methods
	bool insert(int, string);
	int getHeight();
	int getSize();
	friend ostream& operator<<(ostream& os, const AVLTree& me);
	bool find(int, string&);
	vector<string>findRange(int, int);

	//helper methods
	void recursivePrint(AVLnode *, int);
	bool findKeyBool(AVLnode *, int);
	AVLnode* findKeyAddress(AVLnode *, int);
	vector<string> vectorFindKey(AVLnode *, int, int, vector<string>&);
	int balanceFactor(AVLnode *);
	void rightRotate(AVLnode *);
	void leftRotate(AVLnode *);
	void doubleLeft(AVLnode *);
	void doubleRight(AVLnode *);
};
/**
The AVLTree constructor is a basic constructor that set the initial size of the tree to 0 and the head node to a nullptr.
*/
AVLTree::AVLTree() {
		head = nullptr;
		size = 0;
	}

/**
The insert method is used to insert nodes into the AVLTree. The insert method uses several helper methods to make sure that no duplicates are added to the tree
and the tree stayed balanced after each insert. Balance is mainted by looking at the curent height of each side of the tree or it's balance factor. Based on the 
balance factor either a leftRotate,rightRotate,doubleLeft, or doubleRight will be preformed on the tree.
*/	
	bool AVLTree::insert(int key, string value) {
		if (head == nullptr) { 
			head = new AVLnode(key, value);
			size++;
			return true; 
		}
		else {
			if (!findKeyBool(head, key)) { 
				AVLnode * currentNode = head;
				AVLnode * previousNode, *temp, *test;
				int done = 1;
				while (done) { 
					//insert into the left side of the tree
					if (key < currentNode->key) { 
						previousNode = currentNode;
						currentNode = currentNode->leftChild;
						if (!currentNode) { 
							currentNode = new AVLnode(key, value);
							currentNode->parent = previousNode; 
							previousNode->leftChild = currentNode;
							test = currentNode;
							while (test) {
								int heightLeft = balanceFactor(test->leftChild);
								int heightRight = balanceFactor(test->rightChild);
								if ((heightLeft - heightRight) == 2) {
									rightRotate(test);
								}
								else if ((heightRight - heightLeft) == 2) {
									doubleRight(test);
								}
								test = test->parent;
							}
							temp = previousNode; 
							while (temp) {
								temp->height = balanceFactor(temp);
								temp = temp->parent;
							}
							size++;
							done = 0;
						}
					}
					//insert into the the right side of the tree
					else if (key > currentNode->key) { 
						previousNode = currentNode;
						currentNode = currentNode->rightChild;
						if (!currentNode) { 
							currentNode = new AVLnode(key, value);
							currentNode->parent = previousNode; 
							previousNode->rightChild = currentNode;
							test = currentNode;
							while (test) {
								int heightRight = balanceFactor(test->rightChild);
								int heightLeft = balanceFactor(test->leftChild);
								if ((heightRight - heightLeft) == 2) {
									leftRotate(test);
								}
								else if ((heightLeft - heightRight) == 2) {
									doubleLeft(test);
								}
								test = test->parent;
							}
							temp = previousNode;
							while (temp) {
								temp->height = balanceFactor(temp);
								temp = temp->parent;
							}
							size++;
							done = 0;
						}
					}
				}
				return true; 
			}
			else {
				return false; 
			}
		}
	}

/**
The findKeyBool is a helper method that is used to check if the node is already in the tree to not insert duplicates. The method recursrively checks the tree if it is found returns
true and the insert method will not add the node or if findKeyBool does not find the key it will return false and insert will add the node to tree.
*/
	bool AVLTree::findKeyBool(AVLnode * currentNode, int keyToFind) {
		if (!currentNode) {
			return false;
		}
		if (currentNode->key == keyToFind) {
			return true;
		}
		else {
			bool returner = findKeyBool(currentNode->leftChild, keyToFind);
			if (returner) {
				return returner;
			}
			return findKeyBool(currentNode->rightChild, keyToFind);
		}
	}
	/*
	The recursivePrint method is a helper method that traverses the AVLTree and prints out the contents of each node to the screen as well as formats the output to appear 
	to be in a tree structure if you turn your head sideways.
	*/
	void AVLTree::recursivePrint(AVLnode * head, int count) {
		if (!head) {
			return;
		}
		else {
			count++;
			recursivePrint(head->rightChild, count);
			for (int i = 0; i < count; i++) {
				cout << "      ";
			}
			cout << head->key << "," << head->value << endl;
			recursivePrint(head->leftChild, count);

		}
	}
	/**
	The operator << is overloard to call the recursivePrint helper method to print out the current contents of the tree.
	*/
	ostream& operator<<(ostream& os,const AVLTree& me) {
		AVLTree tempTree = me;
		
		AVLnode* temp = tempTree.head;
		tempTree.recursivePrint(temp, -1);

		return cout<<"";
	}
	
	/**
	The getSize method is used to return the current size of the AVLTree
	*/
	int AVLTree::getSize() {
		return size;
	}

	/**
	The getHeight method is used to return the current height of the tree which is being updated and store in the avlnode 
	*/
	int AVLTree::getHeight() {
		return head->height;
	}

	/**
	The Find method uses the returns true if the given value is in the AVLTree and false if it is not.
	*/
	bool AVLTree::find(int key, string& value) {
		AVLnode * temp = findKeyAddress(head, key);
		if (temp != NULL) {
			temp->value = value;
			return true; 
		}
		return false;
	}
	
	/**
	The findKeyAddress method is a helper method for the find method. findKeyAddress uses recursion to traverse the tree and return the node if it is located within the
	tree or will return null if it is not.
	*/
	AVLnode* AVLTree::findKeyAddress(AVLnode * currentNode, int keyToFind) {
		if (!currentNode) {
			return NULL;
		}
		if (currentNode->key == keyToFind) {
			return currentNode;
		}
		else {
			AVLnode * temp = findKeyAddress(currentNode->leftChild, keyToFind);
			if (temp) {
				return temp;
			}
			return findKeyAddress(currentNode->rightChild, keyToFind);
		}
	}

	/**
	The findRange method is used to add every node that is in the tree within the given node and put them into a vector that is returned. 
	*/
	vector<string> AVLTree::findRange(int lowKey, int highKey) {
		vector<string> list;
		return vectorFindKey(head, lowKey, highKey, list); 
	}
	
	/**
	The vectorFindKey method is a helper method that uses recursion to traverse the tree and add any node within the given range into a vector that is 
	returned.
	*/
	vector<string> AVLTree::vectorFindKey(AVLnode * currentNode, int lowKey, int highKey, vector<string> &list) {
		if (!currentNode) {
			return list;
		}
		if ((currentNode->key >= lowKey) && (currentNode->key <= highKey)) {
			list.push_back(currentNode->value);
		}
		vectorFindKey(currentNode->leftChild, lowKey, highKey, list);
		vectorFindKey(currentNode->rightChild, lowKey, highKey, list);
		return list;
	}

	/**
	The balanceFactor method is a helper method that is used in the insert method to determine which nodes in the tree need to 
	be rotated in order to maintain a balance tree. The balanceFactor method works by check the current height of each side of the tree
	and returning whichever height is currently causing the imbalance.
	*/
	int AVLTree::balanceFactor(AVLnode * currentNode) {
		if (!currentNode) { 
			return 0;
		}
		int heightLeft = balanceFactor(currentNode->leftChild);
		int heightRight = balanceFactor(currentNode->rightChild);
		if (heightLeft > heightRight) { 
			currentNode->height = heightLeft + 1;
			return heightLeft + 1;
		}
		currentNode->height = heightRight + 1;
		return heightRight + 1;
	}

	/**
	The rightRotate method is used to rotate the nodes in the AVLTree when the tree is out of balance to the left.
	*/
	void AVLTree::rightRotate(AVLnode * currentNode) {
		AVLnode * tempNode;
		//rotation occurs
		tempNode = currentNode->leftChild;
		currentNode->leftChild = tempNode->rightChild;
		tempNode->rightChild = currentNode;
		tempNode->parent = currentNode->parent;
		if (currentNode->leftChild) {
			currentNode->leftChild->parent = currentNode;
		}
		//error checking and assigning the correct pointers
		if (currentNode == head) { 
			tempNode->parent = nullptr;
			head = tempNode;
		}
		else if (currentNode->parent->leftChild == currentNode) { 
			currentNode->parent->leftChild = tempNode;
		}
		else {
			currentNode->parent->rightChild = tempNode;
		}
		currentNode->parent = tempNode;
	}

	/**
	The leftRotate method is used to rotate the nodes in the AVLTree when the tree is out of balance to the right.
	*/
	void AVLTree::leftRotate(AVLnode * currentNode) {
		AVLnode * tempNode;
		//rotation occurs
		tempNode = currentNode->rightChild;
		currentNode->rightChild = tempNode->leftChild;
		tempNode->leftChild = currentNode;
		tempNode->parent = currentNode->parent;
		if (currentNode->leftChild) {
			currentNode->leftChild->parent = currentNode;
		}
		//error checking and assigning the correct pointers
		if (currentNode == head) {
			tempNode->parent = nullptr;
			head = tempNode;
		}
		else if (currentNode->parent->rightChild == currentNode) {
			currentNode->parent->rightChild = tempNode;
		}
		else {
			currentNode->parent->leftChild = tempNode;
		}
		currentNode->parent = tempNode;
	}

	/**
	The doubleLeft method first will preform a right rotate on the problem node followed by a left rotate.
	*/
	void AVLTree::doubleLeft(AVLnode * currentNode) {
		AVLnode * tempNode;
		//rotation occurs
		tempNode = currentNode->leftChild->rightChild;
		tempNode->leftChild = currentNode->leftChild;
		tempNode->rightChild = currentNode;
		tempNode->leftChild->parent = tempNode;
		tempNode->leftChild->rightChild = nullptr;
		tempNode->rightChild->leftChild = nullptr;
		tempNode->parent = currentNode->parent;

		//error checking and assigning the correct pointers
		if (currentNode == head) {
			tempNode->parent = nullptr;
			head = tempNode;
		}
		else if (currentNode->parent->rightChild == currentNode) {
			currentNode->parent->rightChild = tempNode;
		}
		else {
			currentNode->parent->leftChild = tempNode;
		}
		currentNode->parent = tempNode;
	}

	/**
	The doubleRight method first will preform a left rotate on the problem node followed by a right rotate.
	*/
	void AVLTree::doubleRight(AVLnode * currentNode) {
		AVLnode * tempNode;
		//rotation occurs
		tempNode = currentNode->rightChild->leftChild;
		tempNode->rightChild = currentNode->rightChild;
		tempNode->leftChild = currentNode;
		tempNode->rightChild->parent = tempNode;
		tempNode->rightChild->leftChild = nullptr;
		tempNode->leftChild->rightChild = nullptr;
		tempNode->parent = currentNode->parent;
		
		//error checking and assigning the correct pointers
		if (currentNode == head) {
			tempNode->parent = nullptr;
			head = tempNode;
		}
		else if (currentNode->parent->rightChild == currentNode) {
			currentNode->parent->rightChild = tempNode;
		}
		else {
			currentNode->parent->leftChild = tempNode;
		}
		currentNode->parent = tempNode;
	}

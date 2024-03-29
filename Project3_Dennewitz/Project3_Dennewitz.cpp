/*
Ethan Dennewitz
CS 3100-01
Project 3 : AVL Tree
*/

/**
Modified version of the test harness that was provided on pilot. Changes include fixing a few typos from the original and printing out the contents of the find range vectors so I didn't have to check in 
the local variables. Also overload tree test is commented out because after it is run the previous test no longer show in the output display.
*/

#include "stdafx.h"
#include "AVLTree.h"
#include <iostream>
#include <algorithm> // for copy
#include <iterator>// for ostream_iterator
#include <vector>
using namespace std;

// Basic tests
void printEmptyTree();
void insertTest();
void insertDuplicates();

// Functions to test rotations at root
void singleLeftRoot();
void singleRightRoot();
void doubleLeftRoot();
void doubleRightRoot();

// Functions to test rotations within tree
void singleLeftNested();
void singleRightNested();
void doubleLeftNested();
void doubleRightNested();

// Other functions
vector<string> getFullRange();
vector<string> getLowerRange();
vector<string> getUpperRange();
void overloadTree();

int main() {
	printEmptyTree();
	insertTest();
	insertDuplicates();

	singleLeftRoot();
	singleRightRoot();
	doubleLeftRoot();
	doubleRightRoot();

	singleLeftNested();
	singleRightNested();
	doubleLeftNested();
	doubleRightNested();

	vector<string> full, lower, upper;
	full = getFullRange();
	lower = getLowerRange();
	upper = getUpperRange();

	//print out the contents of each range vector
	cout << "full print" << endl;
	copy(full.begin(), full.end(), ostream_iterator<string>(std::cout, " "));
	cout << endl;
	cout << "lower print" << endl;
	copy(lower.begin(), lower.end(), ostream_iterator<string>(std::cout, " "));
	cout << endl;
	cout << "upper print" << endl;
	copy(upper.begin(), upper.end(), ostream_iterator<string>(std::cout, " "));

	
	//overloadTree();

	system("pause");
	return 0;
}

void printEmptyTree() {
	try {
		AVLTree testTree;
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in printEmptyTree: " << e.what() << endl;
	}
}

void insertTest() {
	try {
		AVLTree testTree;
		cout << "insertTest - no rotate." << endl;
		testTree.insert(4, "four");
		testTree.insert(5, "five");
		testTree.insert(3, "three");
		testTree.insert(7, "seven");

		
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in insertTest: " << e.what() << endl;
	}
}

void insertDuplicates() {
	try {
		cout << "insertDuplicates: " << endl;

		AVLTree testTree;

		testTree.insert(2, "two");
		testTree.insert(1, "one");
		testTree.insert(3, "three");
		testTree.insert(1, "one");

	
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in insertDuplicates: " << e.what() << endl;

	}
}

void singleLeftRoot() {
	try {
		cout << "singleLeftRoot: " << endl;

		AVLTree testTree;
		testTree.insert(1, "one");
		testTree.insert(3, "three");
		testTree.insert(5, "five");

		
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in singleLeftRoot: " << e.what() << endl;
	}
}

void singleRightRoot() {
	try {
		cout << "singleRightRoot: " << endl;

		AVLTree testTree;
		testTree.insert(5, "five");
		testTree.insert(3, "three");
		testTree.insert(1, "one");

		
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in singleRightRoot: " << e.what() << endl;
	}
}

void doubleLeftRoot() {
	try {
		cout << "doubleLeftRoot: " << endl;

		AVLTree testTree;
		testTree.insert(5, "five");
		testTree.insert(1, "one");
		testTree.insert(3, "three");

	
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in doubleLeftRoot: " << e.what() << endl;
	}
}

void doubleRightRoot() {
	try {
		cout << "doubleLeftRoot: " << endl;

		AVLTree testTree;
		testTree.insert(1, "one");
		testTree.insert(5, "five");
		testTree.insert(3, "three");

		
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in doubleRightRoot: " << e.what() << endl;
	}
}

void singleLeftNested() {
	try {
		cout << "singleLeftNested: " << endl;

		AVLTree testTree;

		testTree.insert(5, "five");
		testTree.insert(4, "four");
		testTree.insert(6, "six");
		testTree.insert(7, "seventh");
		testTree.insert(8, "eight");

	
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in singleLeftNested: " << e.what() << endl;
	}
}

void singleRightNested() {
	cout << "singleRightNested: " << endl;
	try {
		AVLTree testTree;
		testTree.insert(5, "five");
		testTree.insert(8, "eight");
		testTree.insert(3, "three");
		testTree.insert(2, "two");
		testTree.insert(1, "one");

	
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in singleRightNested: " << e.what() << endl;
	}
}

void doubleLeftNested() {
	try
	{
		cout << "doubleLeftNested: " << endl;

		AVLTree testTree;

		testTree.insert(4, "four");
		testTree.insert(1, "one");
		testTree.insert(5, "five");
		testTree.insert(3, "three");
		testTree.insert(2, "two");

		
		cout << testTree << endl;
	}
	catch (exception e)
	{
		cout << "Error in doubleLeftNested: " << e.what() << endl;
	}
}

void doubleRightNested() {
	try
	{
		cout << "doubleRightNested: " << endl;

		AVLTree testTree;

		testTree.insert(2, "two");
		testTree.insert(1, "one");
		testTree.insert(5, "five");
		testTree.insert(3, "three");
		testTree.insert(4, "four");

	
		cout << testTree << endl;
	}
	catch (exception e)
	{
		cout << "Error in doubleRightNested: " << e.what() << endl;
	}
}

vector<string> getFullRange() {
	vector<string> vec;

	try {
		AVLTree testTree;

		testTree.insert(2, "two");
		testTree.insert(1, "one");
		testTree.insert(5, "five");
		testTree.insert(8, "eight");
		testTree.insert(3, "three");

		vec = testTree.findRange(0, 8);
	}
	catch (exception e) {
		cout << "Error getRange: " << e.what() << endl;
	}

	return vec;
}

vector<string> getLowerRange() {
	vector<string> vec;

	try {
		AVLTree testTree;

		testTree.insert(2, "two");
		testTree.insert(1, "one");
		testTree.insert(5, "five");
		testTree.insert(8, "eight");
		testTree.insert(3, "three");

		vec = testTree.findRange(0, 4);
		
	}
	catch (exception e) {
		cout << "Error getRange: " << e.what() << endl;
	}

	return vec;
}

vector<string> getUpperRange() {
	vector<string> vec;

	try {
		AVLTree testTree;

		testTree.insert(2, "two");
		testTree.insert(1, "one");
		testTree.insert(5, "five");
		testTree.insert(8, "eight");
		testTree.insert(3, "three");

		vec = testTree.findRange(4, 10);
	}
	catch (exception e) {
		cout << "Error getRange: " << e.what() << endl;
	}

	return vec;
}

void overloadTree() {
	try {
		AVLTree testTree;

		cout << "overloadTree:" << endl;
		int N = 300;

		for (int i = 0; i < N; i++)
		{
			testTree.insert(i, "a");
		}

		
		cout << testTree << endl;
	}
	catch (exception e) {
		cout << "Error in overloadTree: " << e.what() << endl;
	}
}
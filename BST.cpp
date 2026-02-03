#include <iostream>
#include <string>
#include <queue>

#include "Node.h"

using namespace std;

string toLower(string str);
void addNum(Node* &node, int num);
void printTree(Node* tree);
void print(Node* node, int depth);
void parseNumbers(Node* &tree, string input);
void deleteTree(Node* &tree);
bool searchTree(Node* node, int num);

int main() {

	Node* tree = nullptr;
	string input = "";
	
	do {
		//get user input
		cout << endl << endl;
		cout << "Enter numbers or a command (FILE, PRINT, SEARCH, DELETE, QUIT): " << endl;
		getline(cin, input);
		input = toLower(input);	
		
		//check if the input matches any commands, if not see if it's numbers
		
		if (input == "file") {
			continue;
		}
		
		if (input == "print") {
			printTree(tree);
			continue;
		}
	
		if (input == "search") {
			//get input and make sure it is valid
			cout << "Enter a number to search for: " << endl;
			getline(cin, input);

			int num = 0;

			try {
				num = stoi(input);
			}
			catch(...) {
				cout << "Invalid input." << endl;
				continue;
			}

			//search the tree for this value
			bool found = searchTree(tree, num);

			cout << "Value" << (found ? " " : " not ") << "found in tree." << endl;

			continue;
		}

		if (input == "delete") {
			continue;
		}

		if (input == "quit") {
			continue;
		}

		//try to procces as a series of numbers
		parseNumbers(tree, input);

	} while(input != "quit");

	deleteTree(tree);
	
	return 0;
}

string toLower(string str) {
	for (char& c : str) {
		c = (char)tolower(c);
	}

	return str;
}

void addNum(Node* &node, int num) {

	//if the node is null, set as the new root
	if (node == nullptr) {
		node = new Node(num);
		return;
	}

	//if lower than the node, go left, if higher, go right
	
	if (num < node -> getNum()) {
		
		//check if the left child exists
		if (node -> getLeft() != nullptr) {
			addNum(node -> getLeft(), num);
		}
		//otherwise add this as the new left node
		else {
			cout << "Adding node to the left..." << endl;
			node -> setLeft(new Node(num));
		}
	}

	else {
		
		//check if the right child exists
		if (node -> getRight() != nullptr) {
			addNum(node -> getRight(), num);
		}
		//otherwise add this as the new right node
		else {
			cout << "Adding node to the right..." << endl;
			node -> setRight(new Node(num));
		}
	}	
}

void printTree(Node* tree) {
	cout << "Tree: " << endl;
	print(tree, 0);
	cout << endl;
}

void print(Node* node, int depth) {
	//if node is null, output that
	if (node == nullptr) {
		cout << "The tree is empty." << endl;
		return;
	}
	
	//prints everything to the right first
	if (node -> getRight() != nullptr) {
		print(node -> getRight(), depth + 1);
	}

	//adds appropriate indentation
	for (int i = 0; i < depth; i++) {
		cout << "\t";
	}

	//prints value
	cout << node -> getNum() << endl;

	//prints everything to the left
	if (node -> getLeft() != nullptr) {
		print(node -> getLeft(), depth + 1);
	}
}

void parseNumbers(Node* &tree, string input) {
	queue<int> numbers;

	string substring = "";

	for (char c : input) {

		//if there is a space, try parsing the substring to int
		if (c == ' ') {
			try {
				int num = stoi(substring);
				numbers.push(num);
				substring = "";
			}
			catch(...) {
				cout << "Invalid input." << endl;
				return;
			}
		}
		//otherwise, add the character to the substring
		else {
			substring += c;
		}
	}

	try {
		int num = stoi(substring);
		numbers.push(num);
		substring = "";
	}
	catch(...) {
		cout << "Invalid input." << endl;
		return;
	}

	//if the input was fully parsed, now just add the queue to the tree
	while (!numbers.empty()) {
		addNum(tree, numbers.front());
		numbers.pop();
	}
}

void deleteTree(Node* &tree) {
	//null node case
	if (tree == nullptr) {
		return;
	}

	//delete all children first
	if (tree -> getLeft() != nullptr) {
		deleteTree(tree -> getLeft());
	}
	
	if (tree -> getRight() != nullptr) {
		deleteTree(tree -> getRight());
	}

	delete tree;
}

bool searchTree(Node* node, int num) {
	//if there is no node, return null
	if (node == nullptr) {
		return false;
	}
	
	//if the node matches the value, return true
	if (node -> getNum() == num) {
		return true;
	}

	//if the number is less than the current node, go left, otherwise go right
	if (num < node -> getNum()) {
		
		if (node -> getLeft() != nullptr) {
			return searchTree(node -> getLeft(), num);
		}
		//if there is no further left, return false
		else {
			return false;
		}
	}
	else {

		if (node -> getRight() != nullptr) {
			return searchTree(node -> getRight(), num);
		}
		//if there is no further right, return false
		else {
			return false;
		}
	}
}

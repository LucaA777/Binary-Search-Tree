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
Node* searchTree(Node* node, int num);
void removeFromTree(Node* &node, Node* &parent, int num);

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
			bool found = searchTree(tree, num) != nullptr;

			cout << "Value" << (found ? " " : " not ") << "found in tree." << endl;

			continue;
		}

		if (input == "delete") {
			//get input and make sure it is valid
			cout << "Enter a number to remove: " << endl;
			getline(cin, input);

			int num = 0;
			try {
				num = stoi(input);
			}
			catch(...) {
				cout << "Invalid input." << endl;
				continue;
			}

			//delete the number from the tree
			removeFromTree(tree, tree, num);

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

Node* searchTree(Node* node, int num) {
	//if there is no node, return null
	if (node == nullptr) {
		return nullptr;
	}
	
	//if the node matches the value, return true
	if (node -> getNum() == num) {
		return node;
	}

	//if the number is less than the current node, go left, otherwise go right
	if (num < node -> getNum()) {
		
		if (node -> getLeft() != nullptr) {
			return searchTree(node -> getLeft(), num);
		}
		//if there is no further left, return false
		else {
			return nullptr;
		}
	}
	else {

		if (node -> getRight() != nullptr) {
			return searchTree(node -> getRight(), num);
		}
		//if there is no further right, return false
		else {
			return nullptr;
		}
	}
}

void removeFromTree(Node* &node, Node* &parent, int num) {
	
	//make sure that the node is not null
	if (searchTree(node, num) == nullptr) {
		cout << "Value not found in tree." << endl;
		return;
	}

	//get the chosen node and parent node
	
	if (num < node -> getNum()) {
		if (node -> getLeft() != nullptr) {
			removeFromTree(node -> getLeft(), node, num);
		}
		return;
	}
	else if (num > node -> getNum()) {
		if (node -> getRight() != nullptr) {
			removeFromTree(node -> getRight(), node, num);
		}
		return;
	}

	cout << "Found node and parent." << endl;
	//figure out how to handle deletion
	
	//if no children, then simply delete
	if (node -> getLeft() == nullptr && node -> getRight() == nullptr) {
		cout << "No-child deletion." << endl;
		//figure out which side of the parent to delete
		if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {

			//if it is the root, set that to null rather than the parent
			if (node == parent) {
				delete node;
				node = nullptr;
				return;
			}
			else {
				delete node;
				parent -> setLeft(nullptr);
				return;
			}
		}
		else {
			
			//if this is the root, set that to null rather than the parent
			if (node == parent) {
				delete node;
				node = nullptr;
				return;
			}
			else {
				delete node;
				parent -> setRight(nullptr);
				return;
			}
		}
	}

	//if only has a left child
	if (node -> getLeft() != nullptr && node -> getRight() == nullptr) {
		cout << "Single child deletion." << endl;

		//figure out which side of the parent to delete
		if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {
		
			Node* replacement = node -> getLeft();
			
			//if the node has a parent, handle that
			if (parent != node) {
				parent -> setLeft(replacement);
			}
			
			delete node;
			node = replacement;
			
			return;
		}
		
		//delete the other side instead
		else {

			Node* replacement = node -> getLeft();
			
			//if the node has a parent, handle that
			if (parent != node) {
				parent -> setRight(replacement);
			}
			
			delete node;
			node = replacement;
			
			return;

		}
	}	
	
	//if only has a right child
	if (node -> getRight() != nullptr && node -> getLeft() == nullptr) {
		cout << "Single child deletion." << endl;

		//figure out which side of the parent to delete
		if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {
		
			Node* replacement = node -> getRight();
			
			//if the node has a parent, handle that
			if (parent != node) {
				parent -> setLeft(replacement);
			}
			
			delete node;
			node = replacement;
			
			return;
		}
		
		//delete the other side instead
		else {

			Node* replacement = node -> getRight();
			
			//if the node has a parent, handle that
			if (parent != node) {
				parent -> setRight(replacement);
			}
			
			delete node;
			node = replacement;
			
			return;
		}
	}	

	//if has two children
	if (node -> getRight() != nullptr && node -> getLeft() != nullptr) {
		cout << "Two-child deletion." << endl;

		//save the children
		Node* leftChild = node -> getLeft();
		Node* rightChild = node -> getRight();

		//find the successor
		//go one to the right and then go to the left until reaching the end
		Node* current = node -> getRight();
		Node* previous = nullptr;

		//get to the successor
		while (current -> getLeft() != nullptr) {
			previous = current;
			current = current -> getLeft();
		}

		//its ok if the replacement is null
		Node* replacement;
		if (current -> getRight() != nullptr) {
			replacement = current -> getRight();
		}
		else {
			replacement = nullptr;
		}

		//if its the root, do nothing
		if (parent == node) {
				
		}

		//indentify which side of the parent to delete, if it is not the root
		else if (parent -> getLeft() != nullptr && parent -> getLeft() -> getNum() == num) {
			parent -> setLeft(current);
		}
		else {
			parent -> setRight(current);
		}



		cout << "Node: " << node -> getNum() << endl;
		cout << "Left: " << leftChild -> getNum() << endl;
		cout << "Right: " << rightChild -> getNum() << endl;
		cout << "Current: " << current -> getNum() << endl;
		cout << "Previous: " << previous -> getNum() << endl;

		if (replacement != nullptr) {
			cout << "Replacement: " << replacement -> getNum() << endl;
		}
		else {
			cout << "Replacement: n/a" << endl;
		}
		
		//shift the nodes and delete
		delete node;
		node = current;

		if (leftChild != current) {
			node -> setLeft(leftChild);
		}

		if (rightChild != current) {
			node -> setRight(rightChild);
		}

		if (previous != nullptr) {
			previous -> setLeft(replacement);
		}




	}

	cout << "Node deleted." << endl;
}

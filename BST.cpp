#inlcude <iostream>
#include <string>

#include "Node.h"

using namespace std;

string toLower(string str);

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
		
		if (input == "FILE") {
			continue;
		}
		
		if (input == "PRINT") {
			continue;
		}
	
		if (input == "SEARCH") {
			continue;
		}

		if (input == "DELETE") {
			continue;
		}

		if (input == "QUIT") {
			continue;
		}

		//try to procces as a series of numbers


	} while(input != "quit");
	
	return 0;
}

string toLower(string str) {
	for (char& c : str) {
		c = (char)tolower(c);
	}

	return str;
}

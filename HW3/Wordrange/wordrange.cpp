#include <stdexcept>
#include <fstream>
#include <iostream>
#include "string.h"
#include "BST.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		throw invalid_argument("Too few arguments");
	} else if (3 < argc) {
		throw invalid_argument("Too many arguments");
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);

	string commandStr;
	char *comChar;

	BST bst;

	while(getline(input, commandStr))
	{
		comChar = strdup(commandStr.c_str());
		string com = strtok(comChar, " \t");

		if (com == "i")
		{
			string to_insert = strtok(NULL, " \t");
			bst.insert(to_insert);
		}
		else if (com == "r")
		{
			string lowerBound = strtok(NULL, " \t");
			string upperBound = strtok(NULL, " \t");
			output << bst.rangeSize(lowerBound, upperBound) << endl;
		}
	}
}
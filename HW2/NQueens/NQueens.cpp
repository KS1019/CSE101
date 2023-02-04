#include <stdexcept>
#include <fstream>
#include <stack>
#include <set>
#include <string.h>

using namespace std;

bool isBoardCorrect(stack<int> board);
bool doesBoardHaveMatch(stack<int> first, stack<int> second);
void solve(int n, stack<int> pre, ofstream &output);
void reverseStack(stack<int> * s);

int main(int argc, char** argv) {
	if (argc < 3) {
		throw invalid_argument("Too few arguments");
	} else if (3 < argc) {
		throw invalid_argument("Too many arguments");
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);

	string command;
	char *com;
	int boardSize;
	stack<int> usedPlace, tmp;

	while(getline(input, command)) {
		usedPlace = stack<int>();
		tmp = stack<int>();
		com = strdup(command.c_str());
		boardSize = stoi(strtok(com, " \t"));

		if (boardSize == 2 || boardSize == 3) {
			// When the size of the board is 2 or 3, it is known that no solution exists.
			output << "No solution" << endl;
			continue;
		}

		for (int i = 0; i < boardSize; i++) {
			usedPlace.push(0);
		}

		int col = stoi(strtok(NULL, " \t"));
		int row = stoi(strtok(NULL, " \t"));
		while(col && row) {
			for (int i = 0; i < boardSize - col; i++) {
				tmp.push(usedPlace.top());
				usedPlace.pop();
			}
			usedPlace.pop();
			usedPlace.push(row);

			while(!tmp.empty()) {
				usedPlace.push(tmp.top());
				tmp.pop();
			}

			char * c = strtok(NULL, " \t");
			char * r = strtok(NULL, " \t");
			col = (c && r) ? stoi(c) : NULL;
			row = (c && r) ? stoi(r) : NULL;
		}

		solve(boardSize, usedPlace, output);
	}
	
	input.close();
	output.close();
}

// Checks if queens are not attacking each other
bool isBoardCorrect(stack<int> board) {
	int size = board.size();
	set<int> usedRow;
	set<int> usedDiagonalRight;
	set<int> usedDiagonalLeft;
	for (int i = 0; i < size; i++) {
		int row = board.top();
		if (row < 1)
			return false;

		if (usedRow.count(row) ||
				usedDiagonalRight.count(row + i + 1) ||
				usedDiagonalLeft.count(row - i - 1)
		) 
		{
			return false;
		} else {
			usedRow.insert(row);
			usedDiagonalRight.insert(row + i + 1);
			usedDiagonalLeft.insert(row - i - 1);
			board.pop();
		}
	}

	return true;
}

bool doesBoardHaveMatch(stack<int> first, stack<int> second) {
	if (first.size() != second.size())
		return false;

	while(!first.empty() && !second.empty()) {
		if (first.top() != second.top() && first.top() != 0 && second.top() != 0)
			return false;

		first.pop();
		second.pop();
	}

	return true;
}

void solve(int n, stack<int> pre, ofstream &output) {
	int current = 1;
	stack<int> s = stack<int>();

	while(true) {
		while(current <= n) {
			s.push(current);
			if (isBoardCorrect(s)) {
				current = 1;
			} else {
				current = s.top() + 1;
				s.pop();
			}

			if (s.size() == n)
				break;
		}

		if (s.size() == n) {
			if (doesBoardHaveMatch(s, pre)) {
				reverseStack(&s);
				int colCount = 1;
				while(!s.empty()) {
					int rowCount = s.top();
					s.pop();
					output << colCount << " " << rowCount << " ";
					colCount++;
				}
				output << endl;
				return;
			} else {
				current = s.top() + 1;
				s.pop();
			}
		}

		if (s.empty())
			break;

		if (s.top() > n)
			s.pop();

		current = s.top() + 1;
		s.pop();
	}
	output << "No solution" <<  endl;
}

void reverseStack(stack<int> * s) {
	stack<int> tmp;
	while(!s->empty()) {
		tmp.push(s->top());
		s->pop();
	}

	*s = tmp;
}
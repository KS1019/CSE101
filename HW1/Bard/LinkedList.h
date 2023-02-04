#include <string>

using namespace std;

struct Node {
    string word;
	int frequency;
    Node* next;
};

class LinkedList {
    private:
        Node* head;
        Node* find(string, Node*);
    public:
        LinkedList();
        void insert(string, int);
        Node* find(string);
        Node* find(int);
		void printList();
        void sort();
};


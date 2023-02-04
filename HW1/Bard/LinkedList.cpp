#include <string>
#include <iostream>
#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() {
    head = NULL;
}

void LinkedList::insert(string s, int i) {
    Node* to_add = new Node;
    to_add->word = s;
    to_add->frequency = i;
    to_add->next = head;
    head = to_add;
}

Node* LinkedList::find(string str) {
    return find(str, head);
}

Node* LinkedList::find(string str, Node* cur) {
    // find the first occurance of str
    if (!cur)
        return NULL;
    if (cur->word == str)
        return cur;
    else
        return find(str, cur->next);
}

Node* LinkedList::find(int kth) {
    if (kth < 0) 
        return NULL;
    // find kth node of linked list
    Node* cur = head;
    int i = 0;
    while(i <= kth && cur){
        if (i == kth)
            return cur;
        cur = cur->next;
        i++;
    }

    return NULL;
}

void LinkedList::printList() {
    if (!head) {
        std::cout << "head is NULL" << std::endl;
        return;
    }
	Node* cur = head;
	while(cur != NULL){
		std::cout << cur->word << " " << cur->frequency << std::endl;
		cur = cur->next;
	}
}

void LinkedList::sort() {
    // Run bubble sort on linked list
    Node* cur = head;

    while(cur && cur->next){
        Node*next = cur->next;
        while(next) {
            if (cur->frequency < next->frequency
            || (cur->frequency == next->frequency && 
                cur->word > next->word)){
                    std::swap(next->frequency, cur->frequency);
                    std::swap(next->word, cur->word);
                }
            next = next->next;
        }
        if (cur->next)
            cur = cur->next;
        else {
            delete(cur);
            cur = NULL;
        }
    }
}
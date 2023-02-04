#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

#include "LinkedList.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        throw invalid_argument("Too few arguments");
    }
    // get the longest word and use that as the size of the array
    // store all words into array of linkedlists
    // sort each list in the array by the frequency
    ifstream shakespeare_file("shakespeare-cleaned5.txt");
    unsigned int array_size = 0;
    string str;

    // get the longest word and use the lengh of it as the size of the array
    while (getline(shakespeare_file, str)) {
        if (str.length() > array_size)
            array_size = str.length();
    }
    // Since the array is 0 indexed, array_size needs to be incremented once.
    array_size++;

    // Reset buffer of ifstream to reset
    shakespeare_file.clear();
    shakespeare_file.seekg(0);

    // Create the size of the array
    LinkedList lists[array_size];
    for (unsigned int i=0; i < array_size; i++){
        lists[i] = LinkedList();
    }
    // Read the words into the linked list.
    while (getline(shakespeare_file, str)) {
        Node* node_for_str = lists[str.length()].find(str);
        if (node_for_str != NULL)
            node_for_str->frequency++;
        else {
            (lists[str.length()]).insert(str, 1);
        }
    }
    shakespeare_file.close();
    // Iterate over the array of linked list and sort each list.
    for (unsigned int i=0; i < array_size; i++){
        lists[i].sort();
    }
    // dealing with query
    // declare ifstream and ofstream
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    if (!input.is_open() || !output.is_open())
        throw invalid_argument("File could not be opened");

    string command;
    char *com;
    unsigned int length, rank;
    // Read command
    while(getline(input, command)){
        com = strdup(command.c_str());
        length = stoi(strtok(com, " \t"));
        rank = stoi(strtok(NULL, " \t"));

        if (5 > length || length >= array_size || rank < 0){
            output << "-" << endl;
            continue;
        }

        Node* targetNode = lists[length].find(rank);
        if (targetNode) {
            output << targetNode->word << endl;
            delete(targetNode);
            targetNode = NULL;
        } else {
            output << "-" << endl;
        }

        command = "";
        length = 0;
        rank = 0;
    }

    input.close();
    output.close();
}
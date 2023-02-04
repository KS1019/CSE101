#include <stdexcept>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "string.h"

using namespace std;

struct edge {
	string movie;
	string neighbor;

	edge(string m, string n) : movie(m), neighbor(n) {}
};

using graph = map<string, vector<edge>>;

string shortestPath(graph g, string src, string dest) {
	queue<string> q;
	map<string, bool> visited;
	map<string, string> path;

	q.push(src);
	visited[src] = true;
	path[src] = src;

	while(!q.empty())
	{
		string s = q.front();
		q.pop();
		
		for (unsigned int i = 0; i < g[s].size(); i++)
		{
			edge e = g[s].at(i);
			if (visited[e.neighbor] != true)
			{
				visited[e.neighbor] = true;
				path[e.neighbor] = path[s] + " -(" + e.movie + ")- " + e.neighbor;
				q.push(e.neighbor);
			}

			if (e.neighbor == dest)
				return path[e.neighbor];
		}
	}

	return "";
}

int main(int argc, char** argv) {
	if (argc < 3) {
		throw invalid_argument("Too few arguments");
	} else if (3 < argc) {
		throw invalid_argument("Too many arguments");
	}

	ifstream movieList("cleaned_movielist.txt");

	string comString;
	char *comChar;

	graph g;

	while (getline(movieList, comString))
	{
		comChar = strdup(comString.c_str());
		string movieTitle = strtok(comChar, " \t");
		char* name = strtok(NULL, " \t");
		vector<string> actors;
		while (name)
		{
			string n(name);
			// add n to graph
			actors.push_back(n);
			name = strtok(NULL, " \t");
		}

		for (auto a : actors)
		{
			vector<string> tmp = actors;
			tmp.erase(remove(tmp.begin(), tmp.end(), a), tmp.end());
			for (auto t: tmp)
				g[a].push_back(edge(movieTitle, t));
		}
	}
	
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	string names;
	char* namesChar;
	while (getline(input, names))
	{
		namesChar = strdup(names.c_str());
		string firstName = strtok(namesChar, " \t");
		string secondName = strtok(NULL, " \t");

		if (g.find(firstName) == g.end() || g.find(secondName) == g.end())
			output << "Not present" << endl;
		else if (firstName == secondName)
			output << firstName << endl;
		else
		{
			string s = shortestPath(g, firstName, secondName);
			if (s.length() > 0)
				output << s << endl;
			else
				output << "Not present" << endl;
		}
	}
}
// ---------------------------------------------------
// Name: Poulomi Ganguly
// ID: 1598887
//
// CMPUT 275 , Winter 2020
//
// Weekly 5: Graph Concepts
// ---------------------------------------------------

#include <iostream>
#include "digraph.h"
#include <queue>
#include <fstream>
#include <sstream> 

using namespace std;

// Global Variable for Task 2
Digraph answer;

// BFS Code from eClass (UNMODIFIED)
unordered_map<int, int> breadthFirstSearch(const Digraph& graph, int startVertex) {
  unordered_map<int, int> searchTree; // map each vertex to its predecessor

  searchTree[startVertex] = -1;

  queue<int> q;
  q.push(startVertex);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++) {
      if (searchTree.find(*iter) == searchTree.end()) {
        searchTree[*iter] = v;
        q.push(*iter);
      }
    }
  }

  return searchTree;
}

// Task 1: Counts components in given graph (MODIFIED)
int count_components(Digraph* g) {

    vector<int> vertexList = g->vertices(); // vector containing all vertices of graph

    unordered_set<int> unchecked; // A set that will contain all of unordered uncheked vertices
    unordered_map<int, int> searchTree;

    // Inserts all vertices into an unordered set that contains unchecked vertices
    // Helps with linear look up time: 
    for (auto &iter : vertexList){
        unchecked.insert(iter); 
    }

    int numComponents = 0;

    while (true){
        if (!unchecked.empty()){ // If there's still vertices to be checked
            searchTree = breadthFirstSearch(*g, *(unchecked.begin()));

            for(auto searches : searchTree){ 
                unchecked.erase(searches.first); // If the search exists in unchecked, then it is erased.
            }

            numComponents++;
        }
        else return numComponents;
    }
}

vector<string> split(string data){ // Reference from https://stackoverflow.com/a/10861816
    stringstream ss(data); // Makes a string object that can be treated as a file

    vector<string> splittedData;

    while(!ss.eof()){
        string subString;
        getline(ss, subString, ',');
        splittedData.push_back(subString);
    }

    return splittedData;
}

// Task 2: Reads given file input and makes a graph accordingly (MODIFIED)
Digraph* read_city_graph_undirected(char filename[]) {
    ifstream file(filename); // Opens file for reading

    while (!file.eof()) {
        string data; // Holds ONE line of file
        getline(file, data);
        vector<string> splittedData = split(data); // Splitted string vector passed in

        if (splittedData[0].compare("V") == 0){ // When vertex is given
            int newVertex = stoi(splittedData[1]);
            answer.addVertex(newVertex);
        }

        else if (splittedData[0].compare("E") == 0){ // When edge is given
            int firstEdge = stoi(splittedData[1]);
            int secondEdge = stoi(splittedData[2]);

            // Since we need undirected graph
            answer.addEdge(firstEdge, secondEdge);
            answer.addEdge(secondEdge, firstEdge);
        }
    }

    file.close();

    return &answer;
}


int main(int argc, char *argv[]) {

    // Task 3 Output: 
    cout << count_components(read_city_graph_undirected(argv[1])) << endl;

    return 0;
}
#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Vertex { // Define a vertex
    private:
        string city;
        bool inPath, selected; // Used for printing vertices to window

    public:
        // Constructors
        Vertex() : city("Roadtrip"), inPath(false), selected(false) {}
        Vertex(string City) : city(City), inPath(false), selected(false) {}

        // Getter functions 
        string& GetName() { return city; }
        bool& GetPathState() { return inPath; }
        bool& GetSelectedState() { return selected; }
};

class Graph {
    private:
        // Define graph structure
        unordered_map<string, pair<Vertex, unordered_map<string, pair<Vertex, int>>>> adjList;

    public:
        // Constructor 
        Graph(){}
        
        // Insert functions
        void InsertEdge(string from, string to, int weight); // Insert edge between vertices (cities)
        void Insert(string city); // Insert new vertex (city) into the graph

        // Getter functions
        int GetWeight(string from, string to); // Get weight between to vertices (miles between cities)
        vector<string> GetAdjacent(string city); // Get all vertices directly connected to the given vertex
        unordered_map& GetGraph() { return adjList; }

        // Print function
        void PrintGraph(); // Print all vertices
};

void Graph::InsertEdge(string from, string to, int weight) {    // Insert edge between vertices (cities)
    adjList[from].second.insert(make_pair(to, make_pair(adjList[to].first, weight)));
}

void Graph::Insert(string city) {  // Insert new vertex (city) into the graph
    adjList[city].first.GetName() = city;
}

int Graph::GetWeight(string from, string to) {  // Get weight between to vertices (miles between cities)
    return adjList[from].second[to].second;
}

vector<string> Graph::GetAdjacent(string city) {  // Get all vertices directly connected to the given vertex
    vector<string> adjacent;
    for (auto i : adjList[city].second) { // Iterate through adjacent vertices
        adjacent.push_back(i.second.first.GetName()); 
    }
    return adjacent;
}

void Graph::PrintGraph() {  // Print all vertices
    for (auto i : adjList) { // Iterate through graph
        cout << i.first << endl; // Print city names
    }
}
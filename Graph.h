#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;
using namespace sf;

class Node { // Define a node
private:
    string city;
    pair<int, int> xy;
    bool inPath, selected; // Used for printing vertices to window

public:
    // Constructors
    Node() : city("Roadtrip"), inPath(false), selected(false), xy(make_pair(0, 0)) {}
    Node(string City) : city(City), inPath(false), selected(false), xy(make_pair(0, 0)) {}

    // Getter functions 
    string& GetName() { return city; }
    bool& GetPathState() { return inPath; }
    bool& GetSelectedState() { return selected; }
    pair<int, int>& GetXY() { return xy; }
};

class Graph {
private:
    // Define graph structure
    unordered_map<string, pair<Node, vector<pair<string, double>>>> adjList;
    int edges;

public:
    // Constructor 
    Graph() : edges(0) {}

    // Insert functions
    void InsertEdge(string from, string to, double weight); // Insert edge between vertices (cities)
    void Insert(string city, int x, int y); // Insert new node (city) into the graph

    // Getter functions
    double GetWeight(string from, string to); // Get weight between to vertices (miles between cities)
    vector<pair<string, double>> GetAdjacent(string city); // Get all vertices directly connected to the given node
    unordered_map<string, pair<Node, vector<pair<string, double>>>>& GetGraph() { return adjList; }
    int& GetEdges() { return edges; }

    // Print function
    void Print(); // Print all vertices

    // Algorithms
    set<string> bfs(string start, string end);
    set<string> dfs(string start, string end);
    pair<vector<string>, double> dijkstra(string start, string end);

    // Helper functions
    void LoadData(string file, RenderWindow& window, unordered_map<string, Sprite>& sprites);
};

void Graph::InsertEdge(string from, string to, double weight) {    // Insert edge between vertices (cities)
    adjList[from].second.push_back(make_pair(to, weight));
}

void Graph::Insert(string city, int x, int y) {  // Insert new node (city) into the graph
    adjList[city].first.GetName() = city;
    adjList[city].first.GetXY() = make_pair(x, y);
}

double Graph::GetWeight(string from, string to) {  // Get weight between to vertices (miles between cities)
    for (auto i : adjList[from].second) {
        if (i.first == to) {
            return i.second;
        }
    }
    return 0;
}

vector<pair<string, double>> Graph::GetAdjacent(string city) {  // Get all vertices directly connected to the given node
    return adjList[city].second;
}

void Graph::Print() {  // Print all vertices
    int j = 0;
    for (auto i : adjList) {
        cout << j << " " << i.first << endl;
        ++j;
    }
}

pair<vector<string>, double> Graph::dijkstra(string start, string end) { // Adapted from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
    unordered_map<string, double> dist;
    unordered_map<string, bool> path;
    vector<string> inPath;
    ofstream out;
    out.open("debug.txt");

    for (auto i : adjList) { // Set all distances to infinite
        dist[i.first] = INT_MAX;
        path[i.first] = false;
    }
    // Distance of source is o
    dist[start] = 0;

    // Find shortest path for all vertices
    for (int i = 0; i < adjList.size() - 1; i++) {
        int min = INT_MAX;
        string u;
        for (auto i : adjList) {
            if (path[i.first] == false && dist[i.first] <= min) {
                min = dist[i.first], u = i.first;
            }
        }

        path[u] = true;
        inPath.push_back(u);
        int pos = u.find(",");
        string temp = u.substr(pos + 1);
        if (temp != "FL") {
            break;
        }
        if (temp == "GA" || temp == "AL") {
            out << u << endl;
        }
        int edge_index = 0;
        for (auto j : this->GetAdjacent(u)) {
            if (!path[j.first] && dist[u] != INT_MAX && dist[u] + adjList[u].second[edge_index].second < dist[j.first]) {
                dist[j.first] = dist[u] + adjList[u].second[edge_index].second;
            }
            ++edge_index;
        }
    }
    return make_pair(inPath, dist[end]);
}

set<string> Graph::bfs(string start, string end) { // Adapted from Graph Traversals and Algorithm slides
    set<string> visited;
    queue<string> s;
    visited.insert(start);
    s.push(start);
    while (!s.empty()) {
        string u = s.front();
        s.pop();
        for (auto v : adjList[u].second) {
            if (v.first == end) {
                return visited;
            }
            if ((visited.find(v.first) == visited.end())) {
                visited.insert(v.first);
                s.push(v.first);
            }
        }
    }
}

set<string> Graph::dfs(string start, string end) {  // Adapted from Graph Traversals and Algorithm slides
    set<string> visited;
    stack<string> s;
    visited.insert(start);
    s.push(start);
    while (!s.empty()) {
        string u = s.top();
        s.pop();
        for (auto v : adjList[u].second) {
            if (v.first == end) {
                return visited;
            }
            if ((visited.find(v.first) == visited.end())) {
                visited.insert(v.first);
                s.push(v.first);
            }
        }
    }
}

void Graph::LoadData(string file, RenderWindow& window, unordered_map<string, Sprite>& sprites) { //Loads a file

    ifstream inFile(file);	//Input file stream

    if (inFile.is_open()) { // Checks if the file is open

        string line;
        int count = 0;

        while (getline(inFile, line)) { // Loops through CSV file 

            istringstream stream(line);

            string city, state, x, y, dist, temp;
            int xPos, yPos;
            count = 0;

            // Get information from file for each variable 
            getline(stream, city, ',');
            getline(stream, state, ',');
            getline(stream, x, ',');
            getline(stream, y);
            getline(inFile, temp);

            // Converts to appropriate data type
            xPos = stoi(x);
            yPos = stoi(y);

            city = city + ',' + state; // City name is defined by "name,state"
            temp = city;
            this->Insert(city, xPos, yPos); // Insert new city into the graph


            while (1) {	// Get all adjacent cities
                getline(inFile, line);
                istringstream stream(line);

                getline(stream, city, ',');
                if (city == "}") {
                    if (count == 0) {
                        adjList.erase(temp);
                    }
                    break;
                }
                getline(stream, state, ',');
                getline(stream, dist);

                city = city + ',' + state;

                this->InsertEdge(temp, city, stod(dist)); // Insert edge between connected cities
                ++count;

                for (auto a : this->GetAdjacent(city)) {
                    if (a.first == temp) {
                        this->GetEdges()--;
                    }
                }
                this->GetEdges()++;
            }

            // Loading screen updating
            window.clear(Color::White);
            window.draw(sprites["loadscreen"]);
            window.draw(sprites["line"]);
            window.display();

            if (adjList.size() == 5518) {
                sprites["line"].setTextureRect(IntRect(0, 0, 194, 24));
            }
            else if (adjList.size() == 11036) {
                sprites["line"].setTextureRect(IntRect(0, 0, 388, 24));
            }
            else if (adjList.size() == 16554) {
                sprites["line"].setTextureRect(IntRect(0, 0, 582, 24));
            }
            else if (adjList.size() == 22072) {
                sprites["line"].setTextureRect(IntRect(0, 0, 776, 24));
            }
            else if (adjList.size() == 27000) {
                sprites["line"].setTextureRect(IntRect(0, 0, 968, 24));
            }
        }
    }
}


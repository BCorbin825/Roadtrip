#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "Graph.h"
#include "Graphics.h"
#include "EventCheck.h"
#include <sstream>
#include <fstream>

using namespace std;
using namespace sf;


int main() {
    RenderWindow window(VideoMode(1600, 870), "Roadtrip");
    Graph graph;
    Font font;
    if (!font.loadFromFile("Dependencies/times_new_roman.ttf")) {
        cout << "Font not loaded" << endl;
        return -1;
    }
    WindowEvent wEvent = WindowEvent(font);
    unordered_map<string, Texture> textures;
    unordered_map<string, Sprite> sprites;

    LoadImages(textures, sprites); // Load sprites and textures
    graph.LoadData("Dependencies/adjList.txt", window, sprites); // Create graph structure

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            wEvent.CheckEvent(window, event, graph); // Update all relevant code based on event type
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        wEvent.UpdateWindow(window, graph, sprites); // Print current program state to window
        window.display();
    }
    return 0;
}







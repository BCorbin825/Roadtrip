#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "Graph.h"
#include "Graphics.h"

using namespace std;
using namespace sf;


int main() {
    RenderWindow window(VideoMode(1600, 1000), "Roadtrip")
    Graph graph;
    unordered_map<string, Texture> textures;
    unordered_map<string, Sprite> sprites;
    LoadImages(textures, sprites);
    // added comment
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            //CheckEvent(window);
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        window.draw(sprites["map"]);
        window.draw(sprites["ping"]);
        window.draw(sprites["inPath"]);
        window.display();
    }
    return 0;
}







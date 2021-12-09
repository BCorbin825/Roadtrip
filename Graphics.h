#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Graph.h"

using namespace std;
using namespace sf;

void LoadImages(unordered_map<string, Texture>& textures, unordered_map<string, Sprite>& sprites) { // Load all relevant textures and sprites 
	// Load textures from file
	textures["map"].loadFromFile("Images/US4.png");
	textures["inPath"].loadFromFile("Images/dot.png");
	textures["ping"].loadFromFile("Images/MapIconsTransparent.png", IntRect(83, 3, 24, 40));
	textures["menu"].loadFromFile("Images/Menu2.png");
	textures["menu_closed"].loadFromFile("Images/MenuIconClosed.png");
	textures["menu_open"].loadFromFile("Images/MenuIconOpen.png");
	textures["selection"].loadFromFile("Images/Selection.png");
	textures["loadscreen"].loadFromFile("Images/LoadScreen.png");
	textures["line"].loadFromFile("Images/Line.png");
	textures["textbar"].loadFromFile("Images/TextBar.png");

	// Map sprite
	sprites["map"].setTexture(textures["map"]);

	// In path sprite
	sprites["inPath"].setTexture(textures["inPath"]);

	// Ping sprite
	sprites["ping"].setTexture(textures["ping"]);

	// Menu icon sprite
	sprites["menu"].setTexture(textures["menu"]);
	sprites["menu"].setPosition(1335, 52);
	sprites["menu_closed"].setTexture(textures["menu_closed"]);
	sprites["menu_closed"].setPosition(1550, 0);
	sprites["menu_open"].setTexture(textures["menu_open"]);
	sprites["menu_open"].setPosition(1550, 0);
	sprites["selection"].setTexture(textures["selection"]);
	sprites["selection"].setPosition(1349, 68);
	sprites["textbar"].setTexture(textures["textbar"]);
	sprites["textbar"].setPosition(1356, 177);

	// Load screen
	sprites["loadscreen"].setTexture(textures["loadscreen"]);
	sprites["line"].setTexture(textures["line"]);
	sprites["line"].setPosition(332, 454);
	sprites["line"].setTextureRect(IntRect(0, 0, 0, 24));
}



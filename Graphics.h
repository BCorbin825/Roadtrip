#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;
using namespace sf;

void LoadImages(unordered_map<string, Texture>& textures, unordered_map<string, Sprite>& sprites) {
    // Load all required textures from file
    textures["map"].loadFromFile("Images/US2.png");
    textures["inPath"].loadFromFile("Images/dot.png");
    textures["ping"].loadFromFile("Images/MapIconsTransparent.png");

    // Map sprite
    sprites["map"].setTexture(textures["map"]);

    // In path sprite
    sprites["inPath"].setTexture(textures["inPath"]);
    sprites["inPath"].setPosition(150, 100);

    // Ping sprite
    sprites["ping"].setTexture(textures["ping"]);
    sprites["ping"].setTextureRect(IntRect(83, 3, 24, 40));
    sprites["ping"].setPosition(100, 100);
}


// Adapted from COP3502 lab 7
void LoadData(string file, Graph& graph, unordered_map<string, Texture>& textures, unordered_map<string, Sprite>& sprites) { //Loads a file

	ifstream inFile(file);	//Input file stream

	if (inFile.is_open()) { //Checks if the file is open

		string line;
		getline(inFile, line);

		while (getline(inFile, line)) { //Loops through CSV file 

			istringstream stream(line);

			string city, x, y;
			int xPos, yPos;

			//Get information from file for each variable 
			getline(stream, city, ',');
			getline(stream, x, ',');
			getline(stream, y, ',');

			//Converts to appropriate data type
			xPos = stoi(x);
			yPos = stoi(y);

			graph.GetGraph()[city].first.GetName() = city;
			textures[city].loadFromFile("Images/" + city + ".png");
			sprites[city].setTexture(textures[city]);
			sprites[city].setPosition(xPos, yPos);
		}
	}
}
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Graph.h"
#include <chrono>

using namespace std;
using namespace sf;

class WindowEvent {
private:
	bool menu_open, menu_closed, from, to;
	bool dijkstra, bfs, run, clear;
	int delay;
	string start, end;
	sf::String user_input_start, user_input_end;
	sf::Text user_text_start, user_text_end;

	chrono::time_point<chrono::high_resolution_clock> start_time, end_time;
	chrono::duration<double, micro> time_taken;
	sf::String time, distance, dist_const, time_const;
	sf::Text time_out, dist, dist_const_out, time_const_out;

	pair<vector<string>, double> inPath;
	set<string> path;

public:
	WindowEvent(Font& font);
	void CheckEvent(RenderWindow& window, Event& event, Graph& graph);
	void UpdateWindow(RenderWindow& window, Graph& graph, unordered_map<string, Sprite>& sprites);

	// Helper Functions
	void CheckState(RenderWindow& window, Graph& graph, unordered_map<string, Sprite>& sprites);
	void PrintToScreen(RenderWindow& window, Graph& graph, unordered_map<string, Sprite>& sprites);
};

WindowEvent::WindowEvent(Font& font) {
	menu_open = false;
	menu_closed = true;
	from = true;
	to = false;
	dijkstra = false;
	bfs = true;
	run = false;
	clear = false;
	delay = 0;
	start = "";
	end = "";
	user_input_start = "";
	user_input_end = "";
	time = "";
	distance = "";
	dist_const = "Distance:";
	time_const = "Time:";

	user_text_start = Text(user_input_start, font, 20);
	user_text_start.setPosition(1356, 177);
	user_text_start.setFillColor(Color::Black);

	user_text_end = Text(user_input_end, font, 20);
	user_text_end.setPosition(1358, 261);
	user_text_end.setFillColor(Color::Black);

	time_out = Text(time, font, 20);
	time_out.setPosition(1420, 835);
	time_out.setFillColor(Color::Black);

	dist = Text(distance, font, 20);
	dist.setPosition(1450, 815);
	dist.setFillColor(Color::Black);

	dist_const_out = Text(dist_const, font, 20);
	dist_const_out.setPosition(1360, 815);
	dist_const_out.setFillColor(Color::Black);

	time_const_out = Text(time_const, font, 20);
	time_const_out.setPosition(1360, 835);
	time_const_out.setFillColor(Color::Black);
}

void WindowEvent::CheckEvent(RenderWindow& window, Event& event, Graph& graph) {
	int x = 0, y = 0;

	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2i localPostion = Mouse::getPosition(window);
		x = localPostion.x;
		y = localPostion.y;

		if (x >= 1550 && x <= 1600 && y >= 0 && y <= 50) {
			if (menu_closed == true) {
				menu_closed = false;
				menu_open = true;
			}
			else {
				menu_closed = true;
				menu_open = false;
			}
		}
		else if (menu_open == true) {
			if (x >= 1346 && x <= 1365 && y >= 65 && y <= 84) {
				bfs = true;
				dijkstra = false;
			}
			else if (x >= 1346 && x <= 1365 && y >= 99 && y <= 118) {
				dijkstra = true;
				bfs = false;
			}
			else if (x >= 1354 && x <= 1590 && y >= 175 && y <= 216) {
				from = true;
				to = false;
			}
			else if (x >= 1357 && x <= 1590 && y >= 261 && y <= 302) {
				to = true;
				from = false;
			}
			else if (x >= 1423 && x <= 1513 && y >= 314 && y <= 350) {
				clear = true;
				from = true;
				to = false;
				dijkstra = false;
				bfs = true;

				user_input_start = "";
				user_input_end = "";
				user_text_start.setString(user_input_start);
				user_text_end.setString(user_input_end);

				time = "";
				distance = "";
				time_out.setString(time);
				dist.setString(distance);

				path.clear();
				inPath.first.clear();

				graph.GetGraph()[start].first.GetSelectedState() = false;
				graph.GetGraph()[end].first.GetSelectedState() = false;
			}
		}
	}	
	if (event.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::Enter)) {
		if (from == true) {
			from = false;
			to = true;
			start = user_input_start;
		}
		else if (to == true) {
			to = false;
			from = true;
			run = true;
			end = user_input_end;
		}
	}
	if (event.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Enter)) {
		if (from == true) {
			user_input_start += event.text.unicode;
			user_text_start.setString(user_input_start);
		}
		else if (to == true) {
			user_input_end += event.text.unicode;
			user_text_end.setString(user_input_end);
		}
	}
	else if (event.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::BackSpace)) {
		if (from == true) {
			user_input_start.erase(user_input_start.getSize() - 1);
			user_text_start.setString(user_input_start);
		}
		else if (to == true) {
			user_input_end.erase(user_input_end.getSize() - 1);
			user_text_end.setString(user_input_end);
		}
	}
}

void WindowEvent::UpdateWindow(RenderWindow& window, Graph& graph, unordered_map<string, Sprite>& sprites) {
	window.draw(sprites["map"]); // Always draw map
	PrintToScreen(window, graph, sprites);

	if (menu_closed == true) {
		window.draw(sprites["menu_closed"]); // Draw menu closed icon
	}
	else if (menu_open == true) {	
		CheckState(window, graph, sprites);
	}
	window.draw(dist_const_out);
	window.draw(time_const_out);
	window.draw(dist);
	window.draw(time_out);
}

void WindowEvent::CheckState(RenderWindow& window, Graph& graph, unordered_map<string, Sprite>& sprites) {
	window.draw(sprites["menu_open"]);	// Draw menu open icon
	window.draw(sprites["menu"]);	// Draw the menu

	if (bfs == true) {	// Show selected algorithm
		sprites["selection"].setPosition(1349, 68);
		window.draw(sprites["selection"]);
	}
	else {
		sprites["selection"].setPosition(1349, 102);
		window.draw(sprites["selection"]);
	}
	window.draw(user_text_start);	// Draw start and end cities
	window.draw(user_text_end);

	if (run == true) {
		graph.GetGraph()[start].first.GetSelectedState() = true;
		graph.GetGraph()[end].first.GetSelectedState() = true;
		if (dijkstra == true) {
			start_time = chrono::high_resolution_clock::now();

			path = graph.dfs(start, end);

			end_time = chrono::high_resolution_clock::now();
			time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
			time = to_string(time_taken.count()) + "us";
			time_out.setString(time);
			run = false;
			distance = to_string(inPath.second) + " miles";
			dist.setString(distance);
		}
		else if (bfs == true) {
			start_time = chrono::high_resolution_clock::now();

			path = graph.bfs(start, end);

			end_time = chrono::high_resolution_clock::now();
			time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
			time = to_string(time_taken.count()) + "us";
			time_out.setString(time);
			run = false;
			distance = "";
			dist.setString(distance);
		}
	}
}

void WindowEvent::PrintToScreen(RenderWindow& window, Graph& graph, unordered_map<string, Sprite>& sprites) {
	for (auto i : path) {
		auto xy = graph.GetGraph()[i].first.GetXY();
		sprites["inPath"].setPosition(xy.first - 135, xy.second - 80);
		window.draw(sprites["inPath"]);
	}
}
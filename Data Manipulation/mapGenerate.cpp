#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <set>

using std::string;

int mapMake() {
	std::ifstream in("cities_stateAlphabetical.csv", std::ios_base::in);
	std::ofstream out("map.txt", std::ios_base::out);
	string junk;
	string state;
	std::set <string> states;
	while (getline(in, junk, ',')) {
		getline(in, state, ',');
		getline(in, junk);
		states.insert(state);
	}
	int i = 0;
	for (auto iter = states.begin(); iter != states.end(); ++iter) {
		out << "states.emplace(\"" << *iter << "\", " << std::to_string(i++) << ");" << '\n';
	}
	return 0;
}
//generated map of states for switch case
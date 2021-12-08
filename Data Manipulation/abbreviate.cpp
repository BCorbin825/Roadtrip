#include <map>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

void generateAbbrevMap(map<string, string>& states);

int abbreviate() {
	ifstream in("adjListFull.txt", ios_base::in);
	ofstream out("adjList.txt", ios_base::out);
	string line;
	string city;
	string state;
	string remaining;
	map<string, string> states;
	generateAbbrevMap(states);
	while (getline(in, line)) {
		if (line == "{" || line == "}") {
			out << line << endl;
			continue;
		}
		else {
			istringstream stream(line, ios_base::in);
			getline(stream, city, ',');
			getline(stream, state, ',');
			getline(stream, remaining);
			state = states[state];
			out << city << ',' << state << ',' << remaining << endl;
		}
	}
	return 0;
}
//takes in the adjacency list and replaces state names with their aabbreviations
//was faster than changing it and generating the list again

void generateAbbrevMap(map<string, string>& states) {
	states.emplace("Alabama", "AL");
	states.emplace("Arizona", "AZ");
	states.emplace("Arkansas", "AR");
	states.emplace("California", "CA");
	states.emplace("Colorado", "CO");
	states.emplace("Connecticut", "CT");
	states.emplace("Delaware", "DE");
	states.emplace("District of Columbia", "DC");
	states.emplace("Florida", "FL");
	states.emplace("Georgia", "GA");
	states.emplace("Idaho", "ID");
	states.emplace("Illinois", "IL");
	states.emplace("Indiana", "IN");
	states.emplace("Iowa", "IA");
	states.emplace("Kansas", "KS");
	states.emplace("Kentucky", "KY");
	states.emplace("Louisiana", "LA");
	states.emplace("Maine", "ME");
	states.emplace("Maryland", "MD");
	states.emplace("Massachusetts", "MA");
	states.emplace("Michigan", "MI");
	states.emplace("Minnesota", "MN");
	states.emplace("Mississippi", "MS");
	states.emplace("Missouri", "MO");
	states.emplace("Montana", "MT");
	states.emplace("Nebraska", "NE");
	states.emplace("Nevada", "NV");
	states.emplace("New Hampshire", "NH");
	states.emplace("New Jersey", "NJ");
	states.emplace("New Mexico", "NM");
	states.emplace("New York", "NY");
	states.emplace("North Carolina", "NC");
	states.emplace("North Dakota", "ND");
	states.emplace("Ohio", "OH");
	states.emplace("Oklahoma", "OK");
	states.emplace("Oregon", "OR");
	states.emplace("Pennsylvania", "PA");
	states.emplace("Rhode Island", "RI");
	states.emplace("South Carolina", "SC");
	states.emplace("South Dakota", "SD");
	states.emplace("Tennessee", "TN");
	states.emplace("Texas", "TX");
	states.emplace("Utah", "UT");
	states.emplace("Vermont", "VT");
	states.emplace("Virginia", "VA");
	states.emplace("Washington", "WA");
	states.emplace("West Virginia", "WV");
	states.emplace("Wisconsin", "WI");
	states.emplace("Wyoming", "WY");
}
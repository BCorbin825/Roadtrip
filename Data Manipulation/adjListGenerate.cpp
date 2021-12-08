#include <cmath>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#define RADIANS  0.01745329251

using std::vector;
using std::string;
using std::map;

struct Edge {
	string name;
	double distance;
	double angle;

	Edge(string n, double d, double a) {
		name = n;
		distance = d;
		angle = a;
	}

	string print() {
		return name + "," + std::to_string(distance) + "\n";
	}
};


void generateMap(map<string, int>& states);
double haversineDistance(double latBase, double lonBase, double latOut, double lonOut);
double getAngle(double x1, double y1, double x2, double y2);
void findNearbyCities(vector<Edge>& nearbyCities, double latBase, double lonBase, int XBase, int YBase, string state, double threshold, double angleThreshold);
void output(vector<Edge>& nearbyCities, string edge);


int adjListGenerate() {
	std::ifstream in("cities_out_continental_DistortionCorrected.csv", std::ios_base::in);
	map<string, int> stateMap;
	generateMap(stateMap);
	string city;
	string state;
	string lat;
	string lon;
	string X;
	string Y;
	string edge;
	double cityLat;
	double cityLon;
	int cityX;
	int cityY;
	int switchIndex;
	double threshold = 20;
	double angleThreshold = 10;
	while(getline(in, city, ',')){
		getline(in, state, ',');
		getline(in, lat, ',');
		getline(in, lon, ',');
		getline(in, X, ',');
		getline(in, Y);
		cityLat = stod(lat);
		cityLon = stod(lon);
		cityX = stoi(X);
		cityY = stoi(Y);
		edge = city + "," + state + "," + std::to_string(cityX) + "," + std::to_string(cityY) + "\n";
		//it seems backward to get integers for X and Y and then convert them back to strings for this, but this stores them as integers instead of floats, removing a lot of unecessary ".000000" in the final list
		switchIndex = stateMap[state];
		vector<Edge> nearby;
		//this switch case optimizes functionality
		//instead of checking a city's distance to every other city in the country, it checks only cities in its state and neighboring states
		//while there's still a lot of unecessary checks, it's around a 10x speedup (most states have around 5 neighbors) for not a lot of work
		switch (switchIndex) {
		case 0:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Alabama", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Georgia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Florida", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Mississippi", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 1:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arizona", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "California", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nevada", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Utah", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Mexico", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 2:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Mississippi", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Louisiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Texas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 3:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "California", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oregon", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nevada", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arizona", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 4:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Mexico", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Utah", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 5:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Connecticut", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Massachusetts", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Rhode Island", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 6:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Delaware", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Jersey", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maryland", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 7:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "District of Columbia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maryland", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 8:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Florida", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Georgia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Alabama", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 9:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Georgia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Florida", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Alabama", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Carolina", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Carolina", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 10:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Washington", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oregon", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nevada", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Utah", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Montana", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 11:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Illinois", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wisconsin", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Indiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 12:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Indiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Illinois", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Michigan", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Ohio", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 13:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Minnesota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wisconsin", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Illinois", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 14:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 15:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "West Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missorui", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Illinois", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Indiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Ohio", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 16:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Louisiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Mississippi", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Texas", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 17:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maine", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Hampshire", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 18:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maryland", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "West Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "District of Columbia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Delaware", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 19:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Massachusetts", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Vermont", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Hampshire", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Rhode Island", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Connecticut", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 20:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Michigan", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Ohio", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Indiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wisconsin", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 21:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Minnesota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wisconsin", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 22:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Mississippi", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Alabama", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Louisiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 23:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Illinois", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 24:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Montana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 25:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 26:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nevada", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oregon", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Utah", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arizona", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "California", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 27:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Hampshire", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Vermont", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maine", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Massachusetts", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 28:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Jersey", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Delaware", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 29:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Mexico", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Texas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arizona", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 30:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Jersey", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Connecticut", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Massachusetts", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Vermont", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Rhode Island", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 31:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Carolina", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Georgia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Carolina", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 32:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Minnesota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Montana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 33:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Ohio", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "West Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Indiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Michigan", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 34:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Texas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Mexico", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 35:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oregon", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Washington", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nevada", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "California", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 36:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Jersey", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Delaware", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maryland", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "West Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Ohio", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 37:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Rhode Island", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Connecticut", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Massachusetts", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 38:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Carolina", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Carolina", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Georgia", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 39:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Minnesota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Montana", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 40:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Carolina", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Georgia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Alabama", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Mississippi", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Missouri", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 41:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Texas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Louisiana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arkansas", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oklahoma", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Mexico", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 42:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Utah", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nevada", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Mexico", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Arizona", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 43:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Vermont", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New Hampshire", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Massachusetts", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "New York", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 44:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maryland", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "North Carolina", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Tennessee", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "West Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "District of Columbia", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 45:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Washington", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Oregon", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 46:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "West Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Pennsylvania", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Maryland", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Virginia", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Kentucky", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Ohio", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 47:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wisconsin", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Minnesota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Michigan", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Illinois", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Iowa", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Minnesota", threshold, angleThreshold);
			output(nearby, edge);
			break;
		case 48:
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Wyoming", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Montana", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "South Dakota", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Nebraska", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Colorado", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Utah", threshold, angleThreshold);
			findNearbyCities(nearby, cityLat, cityLon, cityX, cityY, "Idaho", threshold, angleThreshold);
			output(nearby, edge);
			break;
		defaut:
			break;
		}
	}
	return 0;
}

void generateMap(map<string, int>& states) {
	states.emplace("Alabama", 0);
	states.emplace("Arizona", 1);
	states.emplace("Arkansas", 2);
	states.emplace("California", 3);
	states.emplace("Colorado", 4);
	states.emplace("Connecticut", 5);
	states.emplace("Delaware", 6);
	states.emplace("District of Columbia", 7);
	states.emplace("Florida", 8);
	states.emplace("Georgia", 9);
	states.emplace("Idaho", 10);
	states.emplace("Illinois", 11);
	states.emplace("Indiana", 12);
	states.emplace("Iowa", 13);
	states.emplace("Kansas", 14);
	states.emplace("Kentucky", 15);
	states.emplace("Louisiana", 16);
	states.emplace("Maine", 17);
	states.emplace("Maryland", 18);
	states.emplace("Massachusetts", 19);
	states.emplace("Michigan", 20);
	states.emplace("Minnesota", 21);
	states.emplace("Mississippi", 22);
	states.emplace("Missouri", 23);
	states.emplace("Montana", 24);
	states.emplace("Nebraska", 25);
	states.emplace("Nevada", 26);
	states.emplace("New Hampshire", 27);
	states.emplace("New Jersey", 28);
	states.emplace("New Mexico", 29);
	states.emplace("New York", 30);
	states.emplace("North Carolina", 31);
	states.emplace("North Dakota", 32);
	states.emplace("Ohio", 33);
	states.emplace("Oklahoma", 34);
	states.emplace("Oregon", 35);
	states.emplace("Pennsylvania", 36);
	states.emplace("Rhode Island", 37);
	states.emplace("South Carolina", 38);
	states.emplace("South Dakota", 39);
	states.emplace("Tennessee", 40);
	states.emplace("Texas", 41);
	states.emplace("Utah", 42);
	states.emplace("Vermont", 43);
	states.emplace("Virginia", 44);
	states.emplace("Washington", 45);
	states.emplace("West Virginia", 46);
	states.emplace("Wisconsin", 47);
	states.emplace("Wyoming", 48);
}
//map for state switch cases

double haversineDistance(double latBase, double lonBase, double latOut, double lonOut) {
	double distanceLat = (latBase - latOut) * RADIANS;
	double distanceLon = (lonBase - lonOut) * RADIANS;
	latBase = latBase * RADIANS;
	latOut = latOut * RADIANS;
	//convert to radians by multiplying by a constant to save time
	double haversineTheta = ((1 - cos(distanceLat)) / 2) + cos(latBase) * cos(latOut) * ((1 - cos(distanceLon)) / 2);
	//1 - cos / 2 used instead of sin ^ 2 because it should be faster?
	haversineTheta = sqrt(haversineTheta);
	haversineTheta = asin(haversineTheta);
	double distance = 7917.6 * haversineTheta;
	//7917.6 is 2 * earth's radius in miles
	//would have used a define like with radians, but it was giving an error for some reason
	return distance;
}

double getAngle(double x1, double y1, double x2, double y2) {
	double deltaY = y2 - y1;
	double deltaX = x2 - x1;
	return -57.2957795131 * atan2(deltaX, deltaY);
}
//computes the standing angle between two points in degrees
//if the origin was located at point 1, this angle is the second city's angle from the x axis

void findNearbyCities(vector<Edge>& nearbyCities, double latBase, double lonBase, int XBase, int YBase, string state, double threshold, double angleThreshold) {
	string filename = "./States/" + state + ".csv";
	std::ifstream in(filename, std::ios_base::in);
	string city;
	string lat;
	string lon;
	string X;
	string Y;
	while (getline(in, city, ',')) {
		getline(in, lat, ',');
		getline(in, lon, ',');
		getline(in, X, ',');
		getline(in, Y);
		double latD = stod(lat);
		double lonD = stod(lon);
		int XI = stoi(X);
		int YI = stoi(Y);
		double distance = haversineDistance(latBase, lonBase, latD, lonD);
		if (distance < threshold && distance != 0) {	//if the distance is within the threshold and isn't the city we're checking (distance 0)
			double angle = getAngle(XBase, YBase, XI, YI);
			if (angle < 0) angle += 360;	//standing angle returns from (-180, 180), alter to (0, 360)
			string name = city + "," + state;
			Edge newCity(name, distance, angle);
			bool collision = false;
			for (int i = 0; i < nearbyCities.size(); i++) {
				if (abs(newCity.angle - nearbyCities[i].angle) < angleThreshold) {
					collision = true;
					if (newCity.distance < nearbyCities[i].distance) {
						nearbyCities[i] = newCity;
					}
				}
			} 
			//checks already adjacent cities
			//if there's one within the angle threshold, take the closer of the two
			if (!collision) {
				nearbyCities.push_back(newCity);
			}
			//if the city wasn't in range of any others, it still needs to be added. do that
		}
	}
	return;
}

void output(vector<Edge>& nearbyCities, string edge) {
	std::ofstream out("adjList.txt", std::ios_base::app);
	out << edge << '{' << "\n";
	for (int i = 0; i < nearbyCities.size(); i++) {
		out << nearbyCities[i].print();
	}
	out << '}' << "\n";
	nearbyCities.clear();
}
//prints a vector to the file and prepares the vector for the next city
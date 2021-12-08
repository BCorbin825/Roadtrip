#include "UTM.h"
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>

using std::string;

float map(float x, float in_min, float in_max, float out_min, float out_max);

int XYGenerate(){
	/* std::ifstream fileIn("uscities_continental.csv", std::ios_base::in);
	std::ofstream fileOut("cities_out_continental_nokeys.csv", std::ios_base::out);
	string city;
	string state;
	string lat;
	string lon;
	float zone;
	float east;
	float north;
	string out;
	while(getline(fileIn, city, ',')) {
		getline(fileIn, state, ',');
		getline(fileIn, lat, ',');
		getline(fileIn, lon, ',');
		float fLat = std::stof(lat);
		float fLon = std::stof(lon);
		zone = LatLonToUTMXY(fLat, fLon, 0, east, north);
		out = city + ',' + state + ',' + lat + ',' + lon + ',' + std::to_string(zone) + ',' + std::to_string(east) + ',' + std::to_string(north) + '\n';
		if(state != "Hawaii" && state != "Alaska" && state != "Puerto Rico") fileOut << out;
		//remove cities not in the continental US
	} */
	//version to compute easting and northing

	std::ifstream fileIn("cities_out_continental_nokeys.csv", std::ios_base::in);
	std::ofstream fileOut("cities_out_continental_DistortionCorrected.csv", std::ios_base::out);
	string city;
	string state;
	string lat;
	string lon;
	string zone;
	string east;
	string north;
	string out;
	while (getline(fileIn, city, ',')) {
		getline(fileIn, state, ',');
		getline(fileIn, lat, ',');
		getline(fileIn, lon, ',');
		getline(fileIn, zone, ',');
		getline(fileIn, east, ',');
		getline(fileIn, north);
		float fZone = std::stof(zone);
		float fEast = std::stof(east);
		float fNorth = std::stof(north);

		float Y = (map(fNorth, 2819745.25, 5429764, 31, 596));
		float YProportion = (Y - 31) / (596 - 31);
		//gets how high up the Y values is on a scale of 0 - 1.0
		Y = 615 - Y;
		//adjust for y0 being at the top of the screen
		float XScale = (YProportion * (1.0 / 3)) + 1;
		//due to the curvature of the earth, there's less total area at the top of the map than at the bottom. it's about a third difference
		//therefore, this parameter adjusts the city's screen position based on how high up it is to remove distortion
		float X = 56.5;
		float distance = fEast - 500000;
		float distanceScaled = map(distance, 210135.5469 - 500000, 790905.875 - 500000, -56.5, 56.5);
		distanceScaled *= XScale;
		X += distanceScaled;
		//UTM works by measuring distance from the central meridian of a zone, with the central meridian located at 500000
		//we start x at this central meridian, and find its offset from it
		//we scale that offset by the distortion factor and add it to x
		X += (113 * (fZone - 10));
		//puts x in the correct zone, as easting only measures distance within the zone
		Y = round( Y * 1.41);
		X = round(X * 1.41);
		//image was scaled later, implementing scale factor and rounding to integer coordinates
		out = city + ',' + state + ',' + lat + ',' + lon + ',' + std::to_string(X) + ',' + std::to_string(Y) + '\n';
		fileOut << out;
	}
	//computing x and y
	return 0;
}

float map(float x, float oldLow, float oldHigh, float newLow, float newHigh)
{
	return (x - oldLow) * (newHigh - newLow) / (oldHigh - oldLow) + newLow;
}
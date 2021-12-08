#include <math.h>
#include <iostream>
#include <string>
#include <fstream>

using std::string;

int fileSplit() {
	std::ifstream in("cities_out_continental_DistortionCorrected.csv", std::ios_base::in);
	std::ofstream out;
	string city;
	string state;
	string rest;
	while (getline(in, city, ',')) {
		getline(in, state, ',');
		getline(in, rest);
		string filename = "./States/" + state + ".csv";
		out.open(filename, std::ios_base::app);
		out << city << ',' << rest << std::endl;
		out.close();
	}
	return 0;
} 

//split one big state csv into multiple, making it so less total operations were done
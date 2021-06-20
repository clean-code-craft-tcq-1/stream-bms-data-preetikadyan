#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef struct
{
	string json_string;
	double SOC;
	double Temperrature;
}Parameters;


class Battery_Parameter_Receiver
{
	vector<Parameters> parameter_list;
	public:	
	void receive_data_from_console();
	//bool parse_data(string data, Parameters &parameter);
};


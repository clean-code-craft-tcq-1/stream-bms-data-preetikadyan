#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Battery_Parameter_Receiver
{
	vector<int> temperature_values;
	vector<int> soc_values;
	
	public:
	void get_data_from_console();
	void get_temperature_values(string sender_data);
	void get_soc_values(string sender_data);
	int calculate_parameter_max(vector<int> parameter_values, string parameter_type);
	int calculate_parameter_min(vector<int> parameter_values, string parameter_type);
	int calculate_parameter_avg(vector<int> parameter_values, string parameter_type);
};

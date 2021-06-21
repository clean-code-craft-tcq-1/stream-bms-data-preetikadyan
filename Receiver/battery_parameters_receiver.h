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
	// get data via pipe from console which is written by Sender
	void get_data_from_console();
	
	//Extract Temperature values from Sender data
	void get_temperature_values(string sender_data);
	
	// Extract SOC Values from Sender data
	void get_soc_values(string sender_data);
	
	// Calculate maximum value for a parameter of input stream
	int calculate_parameter_max(vector<int> parameter_values, string parameter_type);
	
	// Calculate minimum value for a parameter of input stream
	int calculate_parameter_min(vector<int> parameter_values, string parameter_type);
	
	// Calculate Simple moving average value for last 5 values in the input stream of a parameter
	int calculate_parameter_sma(vector<int> parameter_values, string parameter_type);
};

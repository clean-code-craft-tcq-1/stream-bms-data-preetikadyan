#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BMS_Receiver
{
	vector<int> temperature_values;
	vector<int> soc_values;
	int min_temp;
	int max_temp;
	int temp_moving_avg;
	
	public:
	void get_data_from_console();
	void get_temperature_values(string sender_data);
	void get_soc_values(string sender_data);
	int calculate_parameter_max(vector<int> parameter_values);
	int calculate_parameter_min(vector<int> parameter_values);
	int calculate_parameter_avg(vector<int> parameter_values);
	
	//double calculate_simple_moving_average(vector<Parameters> parameter_list);
};

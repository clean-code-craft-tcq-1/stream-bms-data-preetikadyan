#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "battery_parameters_receiver.h"
using namespace std;

TEST_CASE(" Received Parameter values statistics")
{
	// Temperature values from Sender data
     	vector<int> parameter_values = {10,15,89,2,56,68};
	string parameter_type = "Temperature";
	
	// Object creation of Class Battery_Parameter_Receiver
	Battery_Parameter_Receiver obj_Battery_Parameter_Receiver;
	
	// Check for Temperature minimum value
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_min(parameter_values,parameter_type) == 2);
	// Check for Temperature maximum value
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_max(parameter_values,parameter_type) == 89);
	// Check for Simple moving average value for last 5 values of input stream
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_sma(parameter_values,parameter_type) == 46);
	
	
	// SOC values from Sender data
     	parameter_values = {45,3,99,84,66,18};
	parameter_type = "SOC";
	
	// Check for Temperature minimum value
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_min(parameter_values,parameter_type) == 3);
	// Check for Temperature maximum value
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_max(parameter_values,parameter_type) == 99);
	// Check for Simple moving average value for last 5 values of input stream
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_sma(parameter_values,parameter_type) == 54);
 
}





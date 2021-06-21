#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "battery_parameters_receiver.h"
using namespace std;

TEST_CASE(" Received Parameter values statistics")
{
     	vector<int> parameter_values = {10,15,89,2,56,67};
	string parameter_type = "Temperature";
	Battery_Parameter_Receiver obj_Battery_Parameter_Receiver;
	assert(obj_Battery_Parameter_Receiver.calculate_parameter_min(parameter_values,parameter_type) == 2);
 
}



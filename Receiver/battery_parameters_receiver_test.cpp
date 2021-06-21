#include <iostream>
#include "battery_parameters_receiver.h"
#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
using namespace std;

TEST_CASE(" Received Parameter values statistics")
{
     	vector<int> parameter_values = {10,15,89,2,56,67};
	string parameter_type = "Temperature";
	Battery_Parameter_Receiver obj_Battery_Parameter_Receiver;
	EXPECT_EQ(2, obj_Battery_Parameter_Receiver.calculate_parameter_min(parameter_values,parameter_type));
 
}



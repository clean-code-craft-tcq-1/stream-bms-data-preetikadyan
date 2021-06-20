#include <iostream>
#include "battery_parameters_receiver.h"
using namespace std;

int main()
{
	Battery_Parameter_Receiver bp_receiver;
	
	bp_receiver.receive_data_from_console();

	return 0;
}


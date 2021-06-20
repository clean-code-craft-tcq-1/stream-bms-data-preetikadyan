#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "battery_parameters_receiver.h"

using boost::property_tree::ptree;

void Battery_Parameter_Receiver::receive_data_from_console()
{
	string sender_data;
	
	for (int i = 0; i < 15;i++)
	{
		Parameters parameter;
		std::getline(std::cin, sender_data);

		if (parse_data(sender_data, parameter))
			parameter_list.push_back(parameter);
	}	
}

bool Battery_Parameter_Receiver::parse_data(string data, Parameters &parameter)
{
	std::stringstream ss;
	ss.str(data);

	try
	{
		ptree pt;
		boost::property_tree::read_json(ss, pt);

		parameter.json_string = data;
		parameter.Temperrature = pt.get<float>("Temperature");
		parameter.SOC = pt.get<float>("SOC");
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

}


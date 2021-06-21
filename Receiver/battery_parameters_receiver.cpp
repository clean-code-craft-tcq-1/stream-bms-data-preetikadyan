#include "battery_parameters_receiver.h"
using namespace std;
#include <string>
#include <sstream>
#include <cctype> 

void Battery_Parameter_Receiver::get_data_from_console()
{
    string sender_data_heading; 
    string sender_data;
    
    std::getline(std::cin, sender_data_heading);
    std::getline(std::cin, sender_data);
    get_temperature_values(sender_data);
    get_soc_values(sender_data);
}

void Battery_Parameter_Receiver::get_temperature_values(string sender_data)
{
    string temp_data;
    int data_length = sender_data.length() ;
    
    for(int string_index=0; string_index < data_length; string_index++)
    {
        if((sender_data[string_index] == 't') && (sender_data[string_index+2] == 'm'))
        {
              string_index=string_index+16;
              temp_data[0] =sender_data[string_index];
              temp_data[1] =sender_data[string_index+1];
	      temperature_values.push_back(std::stoi(temp_data)); 
        }
       
    }
    calculate_parameter_max(temperature_values);
    calculate_parameter_min(temperature_values);
    calculate_parameter_avg(temperature_values);
}

void Battery_Parameter_Receiver::get_soc_values(string data)
{
    string soc_data;
    int data_length = data.length() ;
    
    for(int string_index=0; string_index < data_length; string_index++)
    {
        if((data[string_index] == 's') && (data[string_index+1] == 't'))
        {
              i=i+20;
              soc_data[0] = data[string_index];
              soc_data[1] = data[string_index+1];
	      soc_values.push_back(std::stoi(soc_data));
        }
    }
    calculate_parameter_max(soc_values);
    calculate_parameter_min(soc_values);
    calculate_parameter_avg(soc_values);
}

int Battery_Parameter_Receiver::calculate_parameter_max(vector<int> parameter_values)
{
    int max = parameter_values[0];
    for(int noOfParams =0; noOfParams<6;noOfParams++)
    {
        if(parameter_values[noOfParams] > max)
        {
            max = parameter_values[noOfParams];
            
        }
    }
    std::cout << "Max value in the upcoming stream "<< max  << std::endl;
    return max;
}

int Battery_Parameter_Receiver::calculate_parameter_min(vector<int> parameter_values)
{
    int min = parameter_values[0] ;
    for(int noOfParams =0; noOfParams<6;noOfParams++)
    {
        if(parameter_values[noOfParams] < min)
        {
            min = parameter_values[noOfParams];
            
        }
    }
 
    std::cout << "Min value in the upcoming stream"<< min  << std::endl;
    return min;
}

int Battery_Parameter_Receiver::calculate_parameter_avg(vector<int> parameter_values)
{
    int size = sizeof(parameter_values)/sizeof(parameter_values[0]);
    int sum; int avg;
    sum = parameter_values[size-1]+ parameter_values[size-2]+parameter_values[size-3]+parameter_values[size-4]+parameter_values[size-5];   
   
    avg = sum/5; // Simple moving avearge for Last 5 readings.
    std::cout << "Simple moving average of Last 5 values "<< avg  << std::endl;
    return avg;
}



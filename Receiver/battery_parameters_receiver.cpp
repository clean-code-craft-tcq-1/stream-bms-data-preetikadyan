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
    int count_temp=0;
    int n = sender_data.length() ;
    
    for(int i=0; i < n; i++)
    {
        if((sender_data[i] == 't') && (sender_data[i+2] == 'm'))
        {
              i=i+16;
              temp_data[0] =sender_data[i];
              temp_data[1] =sender_data[i+1];
	          temperature_values.push_back(std::stoi(temp_data)); 
              count_temp++;
        }
       
    }
   std::cout << "temp values are: "<<temperature_values[0] << ',' << temperature_values[1] << ',' << temperature_values[2] << ',' << temperature_values[3] << ',' << temperature_values[4] << ',' << temperature_values[5] << std::endl;
    calculate_parameter_max(temperature_values);
    calculate_parameter_min(temperature_values);
    calculate_parameter_avg(temperature_values);
}

void Battery_Parameter_Receiver::get_soc_values(string data)
{
    string soc_data;
    int count_soc=0;
    int n = data.length() ;
    
    for(int i=0; i < n; i++)
    {
        if((data[i] == 's') && (data[i+1] == 't'))
        {
              i=i+20;
              soc_data[0] = data[i];
              soc_data[1] = data[i+1];
	          soc_values.push_back(std::stoi(soc_data)); 
              count_soc++;
        }
       
    }
   std::cout << "SOC values are: "<<soc_values[0] << ',' << soc_values[1] << ',' << soc_values[2] << ',' << soc_values[3] << ',' << soc_values[4] << ',' << soc_values[5] << std::endl;
    calculate_parameter_max(soc_values);
    calculate_parameter_min(soc_values);
    calculate_parameter_avg(soc_values);
}

int Battery_Parameter_Receiver::calculate_parameter_max(vector<int> parameter_values)
{
    int max = parameter_values[0];
    for(int i =0; i<6;i++)
    {
        if(parameter_values[i] > max)
        {
            max = parameter_values[i];
            
        }
    }
    std::cout << "Max value "<< max  << std::endl;
    return max;
}

int Battery_Parameter_Receiver::calculate_parameter_min(vector<int> parameter_values)
{
    int min = parameter_values[0] ;
    for(int i =0; i<6;i++)
    {
        if(parameter_values[i] < min)
        {
            min = parameter_values[i];
            
        }
    }
 
    std::cout << "Min value "<< min  << std::endl;
    return min;
}

int Battery_Parameter_Receiver::calculate_parameter_avg(vector<int> parameter_values)
{
    int size = sizeof(parameter_values)/sizeof(parameter_values[0]);
    int sum; int avg;
    sum = parameter_values[size-1]+ parameter_values[size-2]+parameter_values[size-3]+parameter_values[size-4]+parameter_values[size-5];   
   
    avg = sum/5; // Simple moving avearge for Last 5 readings.
    std::cout << "Simple moving average for Last 5 values "<< avg  << std::endl;
    return avg;
}



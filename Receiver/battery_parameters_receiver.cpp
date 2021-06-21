#include "battery_parameters_receiver.h"
using namespace std;
#include <string>
#include <sstream>
#include <cctype> 

// Function to receive the sender data from Console via pipe. 
bool Battery_Parameter_Receiver::get_data_from_console()
{
    string sender_data_heading; // To store Sender data heading
    string sender_data; // To store the Actual data after heading
    
    std::getline(std::cin, sender_data_heading); // Get Heading from Console
    std::getline(std::cin, sender_data); // Get Actual sender data from console
    std::cout << (sender_data_heading+sender_data) << std::endl;
   
    if(!(sender_data.empty()))
      {
	   // Function call to extract the temperature data from Sender data
	    get_temperature_values(sender_data); 

	   // Function call to extract the SOC data from Sender data
	    get_soc_values(sender_data);
	    
	    return true;
      }
    else
    {	
	    return false;
    }
	
}

//Function to Extract the temperature value from complete sender data
void Battery_Parameter_Receiver::get_temperature_values(string sender_data)
{
    string temp_data;
    string parameter_type; // To Store parameter type (Temperature or SOC)
    int data_length = sender_data.length() ; // Length of Sender data string
    
    for(int string_index=0; string_index < data_length; string_index++)
    {
        if((sender_data[string_index] == 't') && (sender_data[string_index+2] == 'm'))
        {
              string_index=string_index+16;
              temp_data[0] =sender_data[string_index];
              temp_data[1] =sender_data[string_index+1];
	      temperature_values.push_back(std::stoi(temp_data)); 
	      parameter_type = "Temperature";
        }
       
    }
    // Print all the Temperature values from Sender data
    std::cout << "Temperature values are: "<<temperature_values[0] << ',' << temperature_values[1] << ',' << temperature_values[2] << ',' << temperature_values[3] << ',' << temperature_values[4] << ',' << temperature_values[5] << std::endl;
    
    // Function call to calculate the maximum value of parameter
    calculate_parameter_max(temperature_values, parameter_type);
    
    // Function call to calculate the minimum value of parameter
    calculate_parameter_min(temperature_values, parameter_type);

    // Function call to calculate the Simple moving average of last 5 values value of parameter
    calculate_parameter_sma(temperature_values, parameter_type);
}

//Function to Extract the SOC value from complete sender data
void Battery_Parameter_Receiver::get_soc_values(string data)
{
    string soc_data;
    string parameter_type; // To Store parameter type (Temperature or SOC)
    int data_length = data.length() ; // Length of Sender data string
    
    for(int string_index=0; string_index < data_length; string_index++)
    {
        if((data[string_index] == 's') && (data[string_index+1] == 't'))
        {
              string_index=string_index+20;
              soc_data[0] = data[string_index];
              soc_data[1] = data[string_index+1];
	      soc_values.push_back(std::stoi(soc_data));
	      parameter_type = "SOC";
        }
    }
    // Print all the SOC values from Sender data
    std::cout << "SOC values are: "<<soc_values[0] << ',' << soc_values[1] << ',' << soc_values[2] << ',' << soc_values[3] << ',' << soc_values[4] << ',' << soc_values[5] << std::endl;

     // Function call to calculate the maximum value of parameter
    calculate_parameter_max(soc_values, parameter_type);
    
    // Function call to calculate the minimum value of parameter
    calculate_parameter_min(soc_values, parameter_type);

    // Function call to calculate the Simple moving average of last 5 values value of parameter
    calculate_parameter_sma(soc_values, parameter_type);
}


// Function to calculate the maximum value of parameter
int Battery_Parameter_Receiver::calculate_parameter_max(vector<int> parameter_values, string parameter_type)
{
    int max = parameter_values[0];
    for(int noOfParams =0; noOfParams<6;noOfParams++)
    {
        if(parameter_values[noOfParams] > max)
        {
            max = parameter_values[noOfParams];
            
        }
    }
    // Print Maximum value of parameter
    std::cout << "Maximum value of "<< parameter_type << " in the upcoming stream is : "<< max  << std::endl;
    return max;
}

// Function to calculate the minimum value of parameter
int Battery_Parameter_Receiver::calculate_parameter_min(vector<int> parameter_values, string parameter_type)
{
    int min = parameter_values[0] ;
    for(int noOfParams =0; noOfParams<6;noOfParams++)
    {
        if(parameter_values[noOfParams] < min)
        {
            min = parameter_values[noOfParams];
            
        }
    }
    // Print Minimum value of parameter
    std::cout << "Minimum value of "<< parameter_type <<" in the upcoming stream is : "<< min  << std::endl;
    return min;
}

// Function to calculate the Simple moving average of last 5 values value of parameter
int Battery_Parameter_Receiver::calculate_parameter_sma(vector<int> parameter_values, string parameter_type)
{
    int size = sizeof(parameter_values)/sizeof(parameter_values[0]);
    int sum; int avg;
    sum = parameter_values[size-1]+ parameter_values[size-2]+parameter_values[size-3]+parameter_values[size-4]+parameter_values[size-5];   
   
    avg = sum/5; // Simple moving avearge for Last 5 readings.
	
    // Print SMA of last 5 values
    std::cout << "Simple moving average for parameter "<< parameter_type <<" of Last 5 values is : "<< avg  << std::endl;
    return avg;
}



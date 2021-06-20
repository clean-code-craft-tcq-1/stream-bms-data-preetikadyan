#include "battery_parameters_receiver.h"
using namespace std;
#include <string>
#include <sstream>
#include <cctype> 

void Battery_Parameter_Receiver::receive_data_from_console()
{
    string sender_data_heading; 
    string sender_data;
    Parameters parameter;
    
     std::getline(std::cin, sender_data_heading);
     std::getline(std::cin, sender_data);

    string temp_data,temp_data1,temp_data2;
    

    int temp_arr[6],soc_arr[6];
    int count_temp,count_soc= 0;
    int i;
    int n = sender_data.length() ;
    std::cout <<"sender data is" <<sender_data << std::endl;
    std::cout << "length of data is "<< sender_data.length() << std::endl;
    std::cout << "first char of data is "<< sender_data[0] << std::endl;	
    for( i=0; i < n; i++)
    {
        if((sender_data[i] == 't') && (sender_data[i+1] == 'e'))
        {
           std::cout << "first t is "<< i << std::endl;
            if(i < (n-16))
            {
              i=i+15;
              temp_data1 = sender_data[i];
              temp_data2 = sender_data[i+1];
              temp_data = temp_data1 + temp_data2;
	      std::cout << "temp_data is "<< temp_data << std::endl;
	     // printf("temp value is %s \n", temp_data.c_str());
             // temp_arr[count_temp] = std::stoi(temp_data);
	      //parameter.Temperrature = temp_arr[count_temp]; 
	     // printf("temp value in parameter is %f \n", parameter.Temperrature);
              count_temp++;
            }
        }
     //   else if(sender_data[i] == 'S')
     //   {
       //     if(i < (n-8))
         //   {
           //   i=i+7;
            //  temp_data1 = sender_data[i];
              //temp_data2 = sender_data[i+1];
              //temp_data = temp_data1 + temp_data2;
             // soc_arr[count_soc] = std::stoi(temp_data);
              //count_soc++;
           // }
       // }
    }
     // for(int i =0;i<count_temp;i++)
     //   {
          //  std::cout << "temperature " << i << " value: " << temp_arr[i] << std::endl;
	   // parameter.Temperrature = temp_arr[i];
	    
      //  }
      //   for(int i =0;i<count_soc;i++)
     //   {
          //  std::cout << "SOC " << i << " value: " << soc_arr[i] << std::endl;
           // parameter.SOC = soc_arr[i];
      //  }
	
}



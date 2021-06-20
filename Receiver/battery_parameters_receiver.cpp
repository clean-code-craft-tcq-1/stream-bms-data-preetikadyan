#include "battery_parameters_receiver.h"
using namespace std;


void Battery_Parameter_Receiver::receive_data_from_console()
{
	string sender_data;
	
	for (int i = 0; i < 15;i++)
	{
		Parameters parameter;
		std::getline(std::cin, sender_data);
	}
	
	    string temp_data,temp_data1,temp_data2;

    int temp_arr[3],soc_arr[3];
    int count_temp,count_soc= 0;
    int i;
    int n = sender_data.length() ;
    std::cout << sender_data << std::endl;
    std::cout << sender_data.length() << std::endl;
    for( i=0; i < n; i++)
    {
        if((sender_data[i] == 't') && (sender_data[i+1] == 'e'))
        {
            if(i < (n-16))
            {
              i=i+15;
              temp_data1 = sender_data[i];
              temp_data2 = sender_data[i+1];
              //if(sender_data[i+2] != ',')
              //{
                  //temp_data3 = sender_data[i+2];
              //}
              temp_data = temp_data1 + temp_data2;
              temp_arr[count_temp] = stoi(temp_data);
              count_temp++;
            }
        }
        else if(sender_data[i] == 'S')
        {
            if(i < (n-8))
            {
              i=i+7;
              temp_data1 = sender_data[i];
              temp_data2 = sender_data[i+1];
              temp_data = temp_data1 + temp_data2;
              soc_arr[count_soc] = stoi(temp_data);
              count_soc++;
            }
        }
    }
      for(int i =0;i<count_temp;i++)
        {
            std::cout << "temperature " << i << " value: " << temp_arr[i] << std::endl;
        }
         for(int i =0;i<count_soc;i++)
        {
            std::cout << "SOC " << i << " value: " << soc_arr[i] << std::endl;
        }
}



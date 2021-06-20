# -*- coding: utf-8 -*-
"""
Created on Tue May 25 22:06:16 2021

@author: EPA5COB[[],[],[]]

"""
import random
from Predefined_values import limit,NumOfItteration


#randomly generating (#NumOfitteration) values for the battery parameter 'temperature' and 'state_of_charge' 
def RandomGenerateParameter(NumOfItteration):
    BatteryParam = []
    if NumOfItteration > 5: #to make sure atleast more than 5 random values are generated for the Battery Parameters
        
        for i in range(1, NumOfItteration + 1):
            temp = random.randint(0,100) #Alwaus integer value will be generated within the desired range
            soc = random.randint(0,100)#so no need to check or test 'temp or 'soc' if they are null or not
        
            itterationCount = i # to store the random value count
        
            BatteryParam.append(CheckLimitOfBatteryParam(itterationCount,{'temperature' : temp, 'state_of_charge' : soc}))
    
        
        Sent_or_not = SenderOutputOrReceiverInput(BatteryParam)
        
        return SenderOutputGeneratedOrNot(Sent_or_not)
        
    else:
        return 'Minimum itteration should be more than 5'
    
    
#check if the battery parameter is in the key of the prdefined list "limit" - on temeprature and state_of_chare considered
def CheckLimitOfBatteryParam(itterationCount,Battery_Life_Parameters):

    BatteryParam = []
    for battery_parameter in Battery_Life_Parameters:
        BatteryParam.append(FormBatteryParamList(itterationCount,battery_parameter,Battery_Life_Parameters[battery_parameter],limit[battery_parameter]))
         
    return BatteryParam

#My intention is to keep track of the no. of random values generated so to do so I will concatenate the count with the battery parameter 
def ConvertItterationCountToString(itterationCount):
    
     if type(itterationCount) != 'str':
         itterationCount = str(itterationCount)
     return itterationCount 

#To form the battery parameter list by checking the min max limit(append 'check_limit'in case not with range else append 'limit_OK') 
def FormBatteryParamList(itterationCount,battery_parameter,parameter_value,parameter_limit):
     BatteryParam = []
     
     ##print(type(itterationCount))
     itterationCount = ConvertItterationCountToString(itterationCount)
     
     
     if battery_parameter in limit.keys():
         if parameter_value < parameter_limit['min'] or parameter_value > parameter_limit['max']:
             BatteryParam.append(battery_parameter+ ' ' +itterationCount)
             BatteryParam.append(parameter_value)
             BatteryParam.append('check_limit')
         else:
             BatteryParam.append(battery_parameter+ ' ' + itterationCount)
             BatteryParam.append(parameter_value)
             BatteryParam.append('Limit OK')
             
     else:
         return 'Battery Parameter Not Valid'
             
     return BatteryParam        
             

#to print the sender output and to set the value 'true' if generated or printed else 'false'
def SenderOutputOrReceiverInput(BatteryParam): 
   
    if len(BatteryParam) != 0: #to make sure battery parameter is not empty
        print("--------------------------------SENDER OUTPUT------------------------")
        print(f' {BatteryParam}')
        print("--------------------------------SENDER OUTPUT END---------------------")
        return True
    else:
        return False
 
#to give information to the user if battery parameter generated or not
def SenderOutputGeneratedOrNot(Sent_or_not):    
    
    if Sent_or_not == True :
        return 'Battery parameter generated for Receiver'
    else:
        return 'Battery parameter not generated for Receiver'

if __name__ == "__main__":
    RandomGenerateParameter(10)

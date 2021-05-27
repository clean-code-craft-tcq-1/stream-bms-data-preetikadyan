# -*- coding: utf-8 -*-
"""
Created on Tue May 25 22:06:16 2021

@author: EPA5COB[[],[],[]]

"""
import random
from Predefined_values import limit,NumOfItteration


def RandomGenerateParameter(NumOfItteration):
    BatteryParam = []
    if NumOfItteration > 5: #to make sure atleast more than 5 random values are generated for the Battery Parameters
        
        for i in range(0, NumOfItteration + 1):
            temp = random.randint(0,100) #Alwaus integer value will be generated within the desired range
            soc = random.randint(0,100)#so no need to check or test 'temp or 'soc' if they are null or not
        
            itterationCount = i # to store the random value count
        
            BatteryParam.append(CheckLimitOfBatteryParam(itterationCount,{'temperature' : temp, 'state_of_charge' : soc}))
    
        
        Sent_or_not = SenderOutputOrReceiverInput(BatteryParam)
        
        return SenderOutputGeneratedOrNot(Sent_or_not)
        
    else:
        return 'Minimum itteration should be more than 5'
        
def CheckLimitOfBatteryParam(itterationCount,Battery_Life_Parameters):

    BatteryParam = []
    for battery_parameter in Battery_Life_Parameters:
        BatteryParam.append(FormBatteryParamList(itterationCount,battery_parameter,Battery_Life_Parameters[battery_parameter],limit[battery_parameter]))
         
    return BatteryParam

def ConvertItterationCountToString(itterationCount):
    
     if type(itterationCount) != 'str':
         itterationCount = str(itterationCount)
     return itterationCount 
   
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
             
             
def SenderOutputOrReceiverInput(BatteryParam): 
   
    if len(BatteryParam) != 0: #to make sure battery parameter is not empty
        print(BatteryParam)
        return True
    else:
        return False
    
def SenderOutputGeneratedOrNot(Sent_or_not):    
    
    if Sent_or_not == True :
        return 'Battery parameter generated for Receiver'
    else:
        return 'Battery parameter not generated for Receiver'

#if __name__ == '__main__':
   #RandomGenerateParameter(NumOfItteration)    
     
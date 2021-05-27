# -*- coding: utf-8 -*-
"""
Created on Wed May 26 16:00:42 2021

@author: EPA5COB
"""
#import unittest
from Predefined_values import NumOfItteration, limit
from GenerateSenderOutput import RandomGenerateParameter,CheckLimitOfBatteryParam,FormBatteryParamList,SenderOutputOrReceiverInput,ConvertItterationCountToString,SenderOutputGeneratedOrNot 

#class RandomGeneratorTest(unittest.TestCase):
    
    #def TestNoOfItterationValue(self):
         


if __name__ == '__main__':
    #unittest.main()
    
    print("-----Randomly generating value for battery parameter 'temperature' and 'state of charge'----- ")  
   
    assert(RandomGenerateParameter(NumOfItteration) == 'Minimum itteration should be more than 5')
    assert(RandomGenerateParameter(NumOfItteration) == 'Battery parameter generated for Receiver')
   
    assert(SenderOutputOrReceiverInput([[['temperature 0', 76, 'check_limit'], ['state_of_charge 0', 22, 'Limit OK']]]) == True)
    assert(SenderOutputOrReceiverInput([]) == False)
    
    assert(SenderOutputGeneratedOrNot(True) == 'Battery parameter generated for Receiver' )
    assert(SenderOutputGeneratedOrNot(False) == 'Battery parameter not generated for Receiver' )
    
    assert(ConvertItterationCountToString(2) == '2')
    assert(ConvertItterationCountToString('2') == '2')
    
    assert(FormBatteryParamList(3,'temperature', 56, limit['temperature']) == ['temperature 3', 56, 'check_limit'])
    assert(FormBatteryParamList(1,'state_of_charge', 71, limit['state_of_charge']) == ['state_of_charge 1', 71, 'Limit OK'])
    assert(FormBatteryParamList(2,'charge_rate', 35, limit['charge_rate']) == 'Battery Parameter Not Valid')
    
    assert(CheckLimitOfBatteryParam(10,{'temperature' : 20, 'state_of_charge' : 40}) == [['temperature 10', 20, 'Limit OK'], ['state_of_charge 10', 40, 'Limit OK']])
    
    
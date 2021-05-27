import unittest
from Predefined_values import NumOfItteration, limit
import GenerateSenderOutput

class RandomGeneratorTest(unittest.TestCase):
    def TestItterationCountType(self):
        self.assertTrue(GenerateSenderOutput.ConvertItterationCountToString(2) == '2')
        self.assertTrue(GenerateSenderOutput.ConvertItterationCountToString('2') == '2')
     
    def TestNoOfItterationMorethanMin(self):
        self.assertTrue(GenerateSenderOutput.RandomGenerateParameter(4) == 'Minimum itteration should be more than 5')
        self.assertTrue(GenerateSenderOutput.RandomGenerateParameter(10) == 'Battery parameter generated for Receiver')
        
    def TestSenderOutputCorrectlyGenerated(self):
        self.assertTrue(GenerateSenderOutput.SenderOutputOrReceiverInput([[['temperature 0', 76, 'check_limit'], ['state_of_charge 0', 22, 'Limit OK']]]) == True)
        self.assertTrue(GenerateSenderOutput.SenderOutputOrReceiverInput([]) == False)
        
    def TestSenderOutputGeneratedOrNot(self):
        self.assertTrue(GenerateSenderOutput.SenderOutputGeneratedOrNot(True) == 'Battery parameter generated for Receiver')
        self.assertTrue(GenerateSenderOutput.SenderOutputGeneratedOrNot(False) == 'Battery parameter not generated for Receiver')
        
    def TestLimitOfBatteryParam(self):
        self.assertTrue(GenerateSenderOutput.CheckLimitOfBatteryParam(10,{'temperature' : 20, 'state_of_charge' : 40}) == [['temperature 10', 20, 'Limit OK'], ['state_of_charge 10', 40, 'Limit OK']])
    
    def TestFormationOfBatteryParamList(self):
        self.assertTrue(GenerateSenderOutput.FormBatteryParamList(3,'temperature', 56, limit['temperature']) == ['temperature 3', 56, 'check_limit'])
        self.assertTrue(GenerateSenderOutput.FormBatteryParamList(1,'state_of_charge', 71, limit['state_of_charge']) == ['state_of_charge 1', 71, 'Limit OK'])
        self.assertTrue(GenerateSenderOutput.FormBatteryParamList(2,'charge_rate', 35, limit['charge_rate']) == 'Battery Parameter Not Valid')
         
if __name__ == '__main__':
    unittest.main()
     

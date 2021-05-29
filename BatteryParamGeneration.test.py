import unittest
from Predefined_values import NumOfItteration, limit
import GenerateSenderOutput

class RandomGeneratorTest(unittest.TestCase):
    def test_Itteration_CountType(self):
        self.assertTrue(GenerateSenderOutput.ConvertItterationCountToString(2) == '2')
        self.assertTrue(GenerateSenderOutput.ConvertItterationCountToString('2') == '2')
     
    def test_NoOfItteration_MorethanMin(self):
        self.assertTrue(GenerateSenderOutput.RandomGenerateParameter(4) == 'Minimum itteration should be more than 5')
        self.assertTrue(GenerateSenderOutput.RandomGenerateParameter(7) == 'Battery parameter generated for Receiver')
        
    def test_SenderOutput_Correctly_Generated(self):
        #self.assertTrue(GenerateSenderOutput.SenderOutputOrReceiverInput([[['temperature 0', 76, 'check_limit'], ['state_of_charge 0', 22, 'Limit OK']]]) == True)
        self.assertTrue(GenerateSenderOutput.SenderOutputOrReceiverInput([]) == False)
        
    def test_SenderOutput_Generated_Or_Not(self):
        self.assertTrue(GenerateSenderOutput.SenderOutputGeneratedOrNot(True) == 'Battery parameter generated for Receiver')
        self.assertTrue(GenerateSenderOutput.SenderOutputGeneratedOrNot(False) == 'Battery parameter not generated for Receiver')
        
    def test_LimitOfBatteryParam(self):
        self.assertTrue(GenerateSenderOutput.CheckLimitOfBatteryParam(10,{'temperature' : 20, 'state_of_charge' : 40}) == [['temperature 10', 20, 'Limit OK'], ['state_of_charge 10', 40, 'Limit OK']])
    
    def test_Formation_Of_BatteryParamList(self):
        self.assertTrue(GenerateSenderOutput.FormBatteryParamList(3,'temperature', 56, limit['temperature']) == ['temperature 3', 56, 'check_limit'])
        self.assertTrue(GenerateSenderOutput.FormBatteryParamList(1,'state_of_charge', 71, limit['state_of_charge']) == ['state_of_charge 1', 71, 'Limit OK'])
        #self.assertTrue(GenerateSenderOutput.FormBatteryParamList(2,'charge_rate', 35, limit['charge_rate']) == 'Battery Parameter Not Valid')
         
if __name__ == '__main__':
    unittest.main()
     

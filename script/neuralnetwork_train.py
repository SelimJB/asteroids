from neuralnetwork import NeuralNetwork, InputManager
import random
import time

networkFile1 = "C:/Users/selim/Projet/0_Projets/Asteroid/misc/NeuralNetwork_NotManyMobile.txt"
dataFile1 = "C:/Users/selim/Projet/0_Projets/Asteroid/Misc/CLEAN_Inputs_NotMany_NotMobile.txt"
testResultFile = "C:/Users/selim/Projet/0_Projets/Asteroid/Misc/TRAININGRESULTS_Inputs_NotMany_NotMobile.txt"
iterationNbr = 300

class NeuralNetworkTrainer():

    TestResults = []

    def __init__(self, dataFile, networkFile, trainingRangeSize = 3000):
        # self.dataFile = dataFile
        # self.networkFile = networkFile
        self.neuralnetwork = NeuralNetwork(networkFile)
        file = open(dataFile)
        self.inputs = file.readlines()
        file.close()
        self.inputNbr = len(self.inputs)
        self.trainingRangeSize = trainingRangeSize if trainingRangeSize < self.inputNbr else self.inputNbr

    def train(self, n):
        if n < 100 :
            n = 100
        n = int(round(float(n)/100)*100)
        for x in range(0, n):
            # print x
            if x % (float(n)/100) == 0 :
                print x/(float(n)/100),"%"
                # InputManager(self.dataFile).iterate(self.neuralnetwork.Test)
                self.neuralnetwork.WriteNeuralNetwork()
                self.iterateAllDatas(self.neuralnetwork.Test)
                self.TestResults.append(self.neuralnetwork.CheckTest())
                self.writeTestResults()
            self.iteratePartial(self.neuralnetwork.Train)    
            # InputManager(self.dataFile).iterate(self.neuralnetwork.Train)    

    def iteratePartial(self, function):
        t1 = round(time.clock()*1000,2)
        rand = self.GetTrainingSetFirstLineNbr()
        for i in range (rand, rand + self.trainingRangeSize):
            values = [float(x) for x in self.inputs[i].split("\t")]
            function(values)
        t2 = round(time.clock()*1000,2)
        print "t : ", (t2-t1)            

    def iterateAllDatas(self, function):
        t1 = round(time.clock()*1000,2)
        for line in self.inputs:
            values = [float(x) for x in line.split("\t")]
            function(values)
        t2 = round(time.clock()*1000,2)
        print "t : ", (t2-t1)

    def writeTestResults(self):
        file = open(testResultFile, "w")
        for a,b in self.TestResults :
            file.write(str(a)+"\t"+str(b)+"\n")
        file.close()


    def GetTrainingSetFirstLineNbr(self):
        rand = random.randint(0, self.inputNbr - self.trainingRangeSize)
        # print self.inputNbr - self.trainingRangeSize, rand
        # print rand
        return rand
        # for i in range (rand, rand + self.trainingRangeSize):
            # print "\t",i,"\t",self.inputs[i]

    def monitoringLogs_header(self):
        print "a"

    def monitoringLogs(self):
        print "a"


    
n = NeuralNetworkTrainer(dataFile1, networkFile1, 1000)
n.train(iterationNbr)

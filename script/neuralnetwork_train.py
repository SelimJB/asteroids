from neuralnetwork import NeuralNetwork
import random
import time
import matplotlib.pyplot as plt
from sklearn import linear_model
import numpy as np

networkFile1 = "C:/Users/selim/Projet/0_Projets/Asteroid/misc/NeuralNetwork_FOUROUTPUTS.txt"
dataFile1 = "C:/Users/selim/Projet/0_Projets/Asteroid/Misc/CLEAN_Inputs_3_NN4_correctedSpeed2andcorrectedDir.txt"
testResultFile = "C:/Users/selim/Projet/0_Projets/Asteroid/Misc/TRAININGRESULTS_Inputs_FOURINPUTS.txt"
iterationNbr = 2000

class NeuralNetworkTrainer():

    TestResults = []

    def __init__(self, dataFile, networkFile, trainingRangeSize = 1000):
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
        # t1 = round(time.clock()*1000,2)
        rand = self.GetTrainingSetFirstLineNbr()
        for i in range (rand, rand + self.trainingRangeSize):
            values = [float(x) for x in self.inputs[i].split("\t")]
            function(values)
        # t2 = round(time.clock()*1000,2)
        # print "t : ", (t2-t1)            

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
        # plt.plot([a for a,b in self.TestResults])
        # plt.savefig('books_read.png')
        
        y = np.array([a for a,b in self.TestResults])
        x = np.array(range(0,len(y)))
        # plt.scatter(x,y)
        regr = linear_model.LinearRegression()
        regr.fit(x[:,np.newaxis], y)
        # plt.plot(x_test, regr.predict(x_test[:,np.newaxis]), color='blue', linewidth=1)
        plt.plot(x,y, color='blue', linewidth=1)
        plt.plot(x,np.array([regr.intercept_ + i* regr.coef_ for i in x]), color='red', linewidth=0.5)
        print "Reg coef : ", regr.coef_
        plt.savefig('books_read.png')
        plt.close('all')


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
# n.GetTrainingSetFirstLineNbr()
n.train(iterationNbr)


# n = NeuralNetwork(networkFile1)


# for x in range(1,1000):
#     InputManager(dataFile1).iterate(n.Train)
#     if x % 10 == 0 :
#         print x/10,"%"
#         InputManager(dataFile1).iterate(n.Test)
#         n.CheckTest()
#         n.WriteNeuralNetwork()


# # TODO
# 	# function (choose repetition number)
# 	# args
# 	# random inputs (train datas selected in a random range of the dataset, same for test datas)
#  Comparer temps :
            # self.iterate(self.neuralnetwork.Train)    
            # InputManager(self.dataFile).iterate(self.neuralnetwork.Train)  
    
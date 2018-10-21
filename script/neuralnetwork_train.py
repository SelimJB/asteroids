from neuralnetwork import NeuralNetwork
import random, yaml, time, ntpath
import matplotlib.pyplot as plt
from sklearn import linear_model
import numpy as np


with open("./config.yaml", "r") as stream:
	try:
		configuration = yaml.load(stream)
	except yaml.YAMLError as exc:
		print(exc)
		exit()

path = configuration["neural_network"]["path"] 
networkFile = ntpath.join(path, configuration["neural_network"]["neural_network_name"])+".txt"
dataFile = ntpath.join(path, configuration["neural_network"]["cleaned_input_file_name"])
testResultGraphName = configuration["neural_network"]["neural_network_name"] + "_TrainingRes"
iterationNbr = configuration["neural_network"]["neural_network_training"]["iteration_nbr"]
trainingRangeSize = configuration["neural_network"]["neural_network_training"]["training_range_size"]
learningRate = configuration["neural_network"]["neural_network_training"]["learning_rate"]
inertiaParameter = configuration["neural_network"]["neural_network_training"]["inertia_parameter"]
testResultGraphFile = ntpath.join(path, testResultGraphName+str(configuration["neural_network"]["neural_network_training"]["test_result_graph_file_num"])+".png")


class NeuralNetworkTrainer():

    TestResults = []

    def __init__(self, dataFile, networkFile, trainingRangeSize = 1000):
        # self.dataFile = dataFile
        # self.networkFile = networkFile
        self.neuralnetwork = NeuralNetwork(networkFile, learningRate, inertiaParameter)
        file = open(dataFile)
        self.inputs = file.readlines()
        file.close()
        self.inputNbr = len(self.inputs)
        self.trainingRangeSize = trainingRangeSize if trainingRangeSize < self.inputNbr else self.inputNbr

    def train(self, n):
        if n < 100 :
            n = 100
        # n : plus proche multple de 100 de n
        n = int(round(float(n)/100)*100)
        for x in range(0, n):
            if x % (float(n)/100) == 0 :
                print x/(float(n)/100),"%"
            if x % (5*float(n)/100) == 0 :
                print "\n",x/(float(n)/100),"%"
                print iterationNbr
                print trainingRangeSize
                # InputManager(self.dataFile).iterate(self.neuralnetwork.Test)
                self.neuralnetwork.WriteNeuralNetwork()
                self.iterateAllDatas(self.neuralnetwork.Test)
                self.TestResults.append(self.neuralnetwork.CheckTest())
                # self.writeTestResults()
                self.drawTestResults()
                print "\n"
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

    def drawTestResults(self):
        values = [a for a,b in self.TestResults]
        y = np.array(values)
        x = np.array(range(0,len(y)))
        regr = linear_model.LinearRegression()
        regr.fit(x[:,np.newaxis], y)
        plt.plot(y)
        plt.plot(np.array([regr.intercept_ + i * regr.coef_ for i in x]))
        yTextPos = [max(y) - (max(y) - min(y))*i/30 for i in range(6)]
        xTextPos = min(x) + (max(x) - min(x))*3/4
        plt.text(xTextPos,yTextPos[0],"Mean : " +  str(values[-1]), fontsize="7", color=(1,0,0))
        plt.text(xTextPos,yTextPos[1],"Learning rate : " +  str(learningRate), fontsize="7", color=(0,0,1))
        plt.text(xTextPos,yTextPos[2],"Inertia : " +  str(inertiaParameter), fontsize="7", color=(0,0,1))
        plt.text(xTextPos,yTextPos[3],"Test file size : " +  str(self.inputNbr), fontsize="7", color=(0,1,0))
        plt.text(xTextPos,yTextPos[4],"It nbr :"  +  str(iterationNbr), fontsize="7", color=(0,1,0))
        plt.text(xTextPos,yTextPos[5],"Rng size :"  +  str(trainingRangeSize), fontsize="7", color=(0,1,0))
        plt.title(testResultGraphName)
        plt.savefig(testResultGraphFile)
        plt.close('all')

    def GetTrainingSetFirstLineNbr(self):
        rand = random.randint(0, self.inputNbr - self.trainingRangeSize)
        return rand



    
n = NeuralNetworkTrainer(dataFile, networkFile, trainingRangeSize)
n.train(iterationNbr)

from numpy import exp, array, random, dot, transpose, matrix

class NeuralNetwork():

    FileName = None
    InputLayer = None
    HiddenLayer = None
    OutputLayer = None
    Dimensions = None
    SynapseMatrix1 = []
    SynapseMatrix2 = []

    
    

    def __init__(self,fileName):
        self.FileName = fileName
        file = open(fileName)
        # Dimensions
        line = file.readline()
        self.Dimensions = [int(x) for x in line.split("\t")]
        file.readline()
        # Synapse Matrix 1
        line = file.readline()
        while line[0] != '#':
            self.SynapseMatrix1.append([float(x) for x in line.split("\t")])
            line = file.readline()
        assert len(self.SynapseMatrix1) == self.Dimensions[1], "Incorrect length for Synapse Matrix 1 in : " + self.FileName
        # Synapse Matrix 2
        line = file.readline()
        while line:
            self.SynapseMatrix2.append([float(x) for x in line.split("\t")])
            line = file.readline()
        assert len(self.SynapseMatrix2) == self.Dimensions[2], "Incorrect length for Synapse Matrix 2 in : " + self.FileName
        file.close()

    
    def Propagate(self, inputs):
        assert len(inputs) == self.Dimensions[0], "Wrong input array size"
        self.HiddenLayer = dot(inputs, transpose(self.SynapseMatrix1))
        self.OutputLayer = dot(self.HiddenLayer, transpose(self.SynapseMatrix2))

    def BackPropagate(self, outputTest):
        sig = self.__sigmoid_der(sum([sum(x) for x in self.SynapseMatrix2]))
        print [ sig*(out - a) for out, a in zip(outputTest, self.OutputLayer)]

    def WriteNeuralNetwork(self):
        file = open(self.FileName, "w")
        file.write('\t'.join(str(e) for e in self.Dimensions)+'\n')
        for synapseArray in self.SynapseMatrix1:
            file.write('\t'.join(str(e) for e in synapseArray))
            file.write('\n')
        for synapseArray in self.SynapseMatrix2:            
            file.write('\t'.join(str(e) for e in synapseArray))
        file.close

    def Toto(self):
        print [ [i+y+z for i,z in zip(x,range(0,4)) ] for x,y in zip(self.SynapseMatrix1,range(1,8))]

    def PrintNeuralNetwork(self):
        print self.FileName, self.Dimensions
        print "\t Synapse Matrix 1 : "
        print "\t", self.SynapseMatrix1
        print "\n\t Synapse Matrix 2 : "
        print "\t", self.SynapseMatrix2        

    def __sigmoid(self, x):
        return 1 / (1 + exp(-x))

    def __sigmoid_der(self, x):
        return self.__sigmoid(x) * (1 - self.__sigmoid(x))

    def printDer(self, x):
        print "SIGMO", self.__sigmoid(x)



class InputManager():
    def __init__(self, fileName):
        self.file = open(fileName)

    def iterate(self, function):
        for line in self.file:
            values = line.split("\t")
            function(float(values[1]))


n = NeuralNetwork("neuralnetwork_4_7_1.txt")
n.Propagate([2,0,1,3])
n.BackPropagate([1,2])
# n.WriteNeuralNetwork()
# InputManager("Inputs.txt").iterate(n.printDer)
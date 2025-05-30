from numpy import exp, array, random, dot, transpose, matrix


class NeuralNetwork():

    FileName = None
    LearningRate = 0
    InertiaParameter = 0
    InputLayer = None
    HiddenLayer = None
    OutputLayer = None
    Dimensions = None
    SynapseMatrix1 = []
    SynapseMatrix2 = []
    ErrorOutput = None
    ErrorHidden = None
    ErrorInput = None

    OutputTest = None
    Tests = []
    Costs = []

    OldSynapseMatrix1 = None
    OldSynapseMatrix2 = None

    NormaliseOutputFunc = None
    GetOutputFunc = None

    I = 0

    def __init__(self, fileName, learningRate = 0.00001, inertiaParameter = 0.79):
        self.FileName = fileName
        self.LearningRate = learningRate
        self.InertiaParameter = inertiaParameter
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
        assert len(
            self.SynapseMatrix1) == self.Dimensions[1], "Incorrect length for Synapse Matrix 1 in : " + self.FileName
        # Synapse Matrix 2
        line = file.readline()
        while line:
            self.SynapseMatrix2.append([float(x) for x in line.split("\t")])
            line = file.readline()
        assert len(
            self.SynapseMatrix2) == self.Dimensions[2], "Incorrect length for Synapse Matrix 2 in : " + self.FileName
        file.close()
        self.OldSynapseMatrix1 = self.SynapseMatrix1
        self.OldSynapseMatrix2 = self.SynapseMatrix2
        # Function Initialisation
        self.NormaliseOutputFunc = self.NormaliseOutput_3
        self.GetOutputFunc = self.GetOutput_3

    def Use(self, inputs):
        self.Propagate(inputs)
        # print self.OutputLayer
        # VRAI LIGNE
        return [self.GetOutputFunc(o) for o in self.OutputLayer]
        # A MODIFIER
        # return [self.GetOutput_2(self.OutputLayer[0]), self.GetOutput_3(self.OutputLayer[1])]

    def CheckTest(self):
        cost = round(sum(self.Costs)/len(self.Costs),10)
        test = round((self.Tests.count(True))/float(len(self.Tests))*100,2)
        print "Nbr Iterations : ", self.I
        print "Moyenne cout : ", cost
        print "Moyenne testes : ", test
        self.Tests = []
        self.Costs = []
        self.I = 0
        return [cost, test]        

    # With Sigmo
    def Propagate(self, inputs):
        assert len(inputs) == self.Dimensions[0], "Wrong input array size"
        self.InputLayer = inputs
        # BIAS
        self.InputLayer.append(1)
        hiddenLayer = self.__RELU(dot(self.InputLayer, transpose(self.SynapseMatrix1)))
        self.HiddenLayer = hiddenLayer.tolist()
        self.HiddenLayer.append(1)
        # print self.HiddenLayer, len(self.HiddenLayer)
        self.OutputLayer = self.__sigmoid(dot(self.HiddenLayer, transpose(
            self.SynapseMatrix2))).tolist()

    # def Propagate(self, inputs):
    #     assert len(inputs) == self.Dimensions[0], "Wrong input array size"
    #     self.InputLayer = inputs
    #     hiddenLayer = dot(inputs, transpose(self.SynapseMatrix1))
    #     self.OutputLayer = dot(hiddenLayer, transpose(
    #         self.SynapseMatrix2)).tolist()
    #     self.HiddenLayer = hiddenLayer.tolist()

    def BackPropagate(self, outputTest):
        self.OutputTest = outputTest
        sig = self.__sigmoid_der(
            dot(self.HiddenLayer, transpose(self.SynapseMatrix2)))
        err = [x-y for x, y in zip(outputTest, self.OutputLayer)]
        self.ErrorOutput = [x*y for x, y in zip(sig, err)]
        sig = self.__RELU_der(
            dot(self.InputLayer, transpose(self.SynapseMatrix1)))
        err = [dot(x, self.ErrorOutput)
               for x in transpose(self.SynapseMatrix2).tolist()]
        self.ErrorHidden = [x*y for x, y in zip(sig, err)]

    def WeightUpdate(self):
        self.SynapseMatrix2 = transpose([
            [j+self.LearningRate*e*a for j, e in zip(i, self.ErrorOutput)]
            for i, a in zip(transpose(self.SynapseMatrix2), self.HiddenLayer)
        ]).tolist()
        self.SynapseMatrix1 = transpose([
            [j+self.LearningRate*e*a for j, e in zip(i, self.ErrorHidden)]
            for i, a in zip(transpose(self.SynapseMatrix1), self.InputLayer)
        ]).tolist()   

    def WeightUpdateInertia(self):
        # s2
        newSynapseMatrix = []
        for i, a, di  in zip(transpose(self.SynapseMatrix2), self.HiddenLayer, transpose(self.OldSynapseMatrix2)):
            newSynapseMatrixColumn = []
            for j, e, dj in zip(i, self.ErrorOutput, di):
                delta = j- dj # delta = old Weight - older Weight
                w = j+self.LearningRate*e*a*self.InertiaParameter + (1 - self.InertiaParameter)*delta
                newSynapseMatrixColumn.append(w)
            newSynapseMatrix.append(newSynapseMatrixColumn)
        self.OldSynapseMatrix2 = self.SynapseMatrix2
        self.SynapseMatrix2 = transpose(newSynapseMatrix).tolist()
        # s1
        newSynapseMatrix = []
        for i, a, di  in zip(transpose(self.SynapseMatrix1), self.InputLayer, transpose(self.OldSynapseMatrix1)):
            newSynapseMatrixColumn = []
            for j, e, dj in zip(i, self.ErrorHidden, di):
                delta = j- dj
                w = j+self.LearningRate*e*a*self.InertiaParameter + (1 - self.InertiaParameter)*delta
                newSynapseMatrixColumn.append(w)
            newSynapseMatrix.append(newSynapseMatrixColumn)
        self.OldSynapseMatrix1 = self.SynapseMatrix1
        self.SynapseMatrix1 = transpose(newSynapseMatrix).tolist()

    def GetQuadraticCost(self):
        return 0.5*sum([(a-d)**2 for a, d in zip(self.OutputLayer, self.OutputTest)])

    def WriteNeuralNetwork(self):
        file = open(self.FileName, "w")
        file.write('\t'.join(str(e) for e in self.Dimensions)+'\n')
        file.write("#\n")
        for synapseArray in self.SynapseMatrix1:
            file.write('\t'.join(str(e) for e in synapseArray))
            file.write('\n')
        file.write("#\n")
        for synapseArray in self.SynapseMatrix2:
            file.write('\t'.join(str(e) for e in synapseArray))
            file.write('\n')
        file.close

    def Toto(self):
        print [[i+y+z for i, z in zip(x, range(0, 4))]
               for x, y in zip(self.SynapseMatrix1, range(1, 8))]

    def PrintNeuralNetwork(self):
        print self.FileName, self.Dimensions
        print "\t Synapse Matrix 1 : "
        print "\t", self.SynapseMatrix1
        print "\n\t Synapse Matrix 2 : "
        print "\t", self.SynapseMatrix2

    def __RELU(self, x):
        res = array([e if e > 0 else 0 for e in x])
        return res

    def __RELU_der(self, x):
        return array([1 if e > 0 else 0 for e in x])

    def __sigmoid(self, x):
        return 1 / (1 + exp(-x))

    def __sigmoid_der(self, x):
        return self.__sigmoid(x) * (1 - self.__sigmoid(x))

    def printDer(self, x):
        print "SIGMO", self.__sigmoid(x)

    def Test(self, x):
        self.InputLayer = x[:self.Dimensions[0]]
        self.OutputTest = x[self.Dimensions[0]:]
        self.Propagate(self.InputLayer)
        self.Costs.append(self.GetQuadraticCost())
        self.Tests.append(all(self.GetOutputFunc(networkOutput) == realOutput for networkOutput,
                              realOutput in zip(self.OutputLayer, self.OutputTest)))    
        self.I += 1

    def Train(self, x):
        self.InputLayer = x[:self.Dimensions[0]]
        # self.OutputTest = [o/10 for o in x[self.Dimensions[0]:]]
        self.OutputTest = [self.NormaliseOutputFunc(o) for o in x[self.Dimensions[0]:]]
        self.Propagate(self.InputLayer)
        self.BackPropagate(self.OutputTest)
        # self.WeightUpdate(1)
        self.WeightUpdateInertia()
        # print "Input : ", inputs
        # print "Output : ", outputs
        # # print "S1 : ", n.SynapseMatrix1
        # # print "S2 : ", n.SynapseMatrix2
        # print "Res : ", round(n.OutputLayer[0]*10)



    # First NN version
    def NormaliseOutput_1(self, output):
        return output / 10
    
    def GetOutput_1(self, res):
        return round(res*10)

    # Second NN version
    def NormaliseOutput_2(self, output):
        return (output + 1)/2

    def GetOutput_2(self, res):
        temp = res*2-1
        seuil = 0.23
        if temp < seuil and temp > -seuil :
            return 0
        elif temp > seuil:
            return 1
        elif temp < -seuil:
            return -1

    def GetOutput_2bis(self, res):
        temp = res*2-1
        seuil = 0.055
        if temp < seuil and temp > -seuil :
            return 0
        elif temp > seuil:
            return 1
        elif temp < -seuil:
            return -1            

    ## Third NN version
    def NormaliseOutput_3(self, output):
        return output

    def GetOutput_3(self, res):
        return res
# n = NeuralNetwork("neuralnetwork_4_7_1.txt")

# n.Test([0,1,0,0.1],[1,2])
# n.Test([0,1,0,0.1],[5,8])
# n.CheckTest()

# n.Test([0.1, 0, 0.1, 0.4],[1,2])
# n.CheckTest()
# n.Propagate([0.1, 0, 0.1, 0.4])
# n.BackPropagate([1, 2])
# n.WeightUpdate(1)
# print "Total error : ", n.GetQuadraticCost([1, 2])


# # TODO
#     #   Enlever les parametres self.Input et self.Output
#     # Generate netwrok random
#     #   Clean code
#     #   Use method
#     # Optimisation  ne pas lire le fichier input a chaque fois
#     #  Fichier log txt avec heure 


# # # # Train
# for x in range(10000):
#     InputManager("Inputs.txt").iterate(n.Train)
#     if x % 10 == 0 :
#         print x/10,"%"
#         InputManager("Inputs.txt").iterate(n.Test)
#         n.CheckTest()
#         n.WriteNeuralNetwork()
#         print "Res : ", round(n.OutputLayer[0]*10)
    # print "\n"


# Test
# InputManager("Inputs.txt").iterate(n.Test)
# n.CheckTest()

# Check
# InputManager("Inputs.txt").iterate(n.Train)
# print n.Use([1,0,1,0])



# Todo
    # Clean code
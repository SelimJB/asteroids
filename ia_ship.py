# TODO : add a description of the inputs in the comments
import sys, yaml, ntpath
sys.path.insert(0, 'script')
import neuralnetwork

# Classement
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_FirstTrain.txt") # 1
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_Many1.txt") # 2
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_NotManyNotMobile.txt") # 0
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_NotManyMobile.txt") # PREMIER RESEAU AVEC CORRECTION
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_NotManyNotMobile_Inertia0.9.txt") # 0
# n = neuralnetwork.NeuralNetwork("./neuralnetwork.txt")
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_NotTrained.txt")

# NN 2
# n = neuralnetwork.NeuralNetwork("./Misc/NeuralNetwork_TWOOUTPUTS.txt")

# NN 4
with open("./config.yaml", "r") as stream:
	try:
		configuration = yaml.load(stream)
	except yaml.YAMLError as exc:
		print(exc)
		exit()

path = ntpath.join(
    configuration["neural_network"]["path"],
    configuration["neural_network"]["neural_network_name"])
n = neuralnetwork.NeuralNetwork(path)

def GetOutput(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    # print shipAngle, " , ", x_dirShipNearestAst, " , ", y_dirShipNearestAst, " , ", relativeSpeed
    a = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])[0]
    print a
    return a

toto = None

# NN 2
def GetOutput2(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    a = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])
    print a
    global toto
    toto = a
    return a

def GetThrustOutput():
    global toto
    return toto[0]

def GetDirOutput():
    global toto
    return toto[1]
    
# NN 3
def GetOutput3(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    a = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])
    tresholds = [
        0.51, 
        0.0915, 
        0.22, 
        0.22
    ]
    global toto
    toto = [0, 0, 0, 0]
    # print a
    if a[0] > tresholds[0] and a[1] > tresholds[1] :
        if a[0] > a[1] :
            toto[0] = 1
            toto[1] = 0
        else :
            toto[0] = 0
            toto[1] = 1
    elif a[0] > tresholds[0] :
        toto[0] = 1
    elif a[1] > tresholds[1] :
        toto[1] = 1 
    if a[2] > tresholds[2] and a[3] > tresholds[3] :
        if a[2] > a[3] :
            toto[2] = 1
            toto[3] = 0
        else :
            toto[2] = 0
            toto[3] = 1
    elif a[2] > tresholds[2] :
        toto[2] = 1
    elif a[3] > tresholds[3] :
        toto[3] = 1     
    # print toto       
    return a

def GetThrustBoolOutput():
    global toto
    return toto[0]
def GetReverseThrustBoolOutput():
    global toto
    return toto[1]
def GetLeftBoolOutput():
    global toto
    return toto[2]
def GetRightBoolOutput():
    global toto
    return toto[3]
    
# TODO
    # Un GetOutput qui retourne 2 outputs

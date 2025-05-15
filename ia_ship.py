# Interface allowing the Asteroids game to be controlled by a neural network AI: computes ship actions from game state inputs.

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
    configuration["neural_network"]["neural_network_name"]+".txt")
n = neuralnetwork.NeuralNetwork(path)

def GetOutput(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    # print shipAngle, " , ", x_dirShipNearestAst, " , ", y_dirShipNearestAst, " , ", relativeSpeed
    a = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])[0]
    print(a)
    return a

last_nn_output = None

# NN 2
def GetOutput2(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    a = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])
    print(a)
    global last_nn_output
    last_nn_output = a
    return a

def GetThrustOutput():
    global last_nn_output
    return last_nn_output[0]

def GetDirOutput():
    global last_nn_output
    return last_nn_output[1]
    
# NN 3
def GetOutput3(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    a = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])
    tresholds = [
        0.60, 
        0.0915, 
        0.16, 
        0.16
    ]
    global last_nn_output
    last_nn_output = [0, 0, 0, 0]
    print(a)
    if a[0] > tresholds[0] and a[1] > tresholds[1] :
        if a[0] > a[1] :
            last_nn_output[0] = 1
            last_nn_output[1] = 0
        else :
            last_nn_output[0] = 0
            last_nn_output[1] = 1
    elif a[0] > tresholds[0] :
        last_nn_output[0] = 1
    elif a[1] > tresholds[1] :
        last_nn_output[1] = 1 
    if a[2] > tresholds[2] and a[3] > tresholds[3] :
        if a[2] > a[3] :
            last_nn_output[2] = 1
            last_nn_output[3] = 0
        else :
            last_nn_output[2] = 0
            last_nn_output[3] = 1
    elif a[2] > tresholds[2] :
        last_nn_output[2] = 1
    elif a[3] > tresholds[3] :
        last_nn_output[3] = 1     
    # print last_nn_output       
    return a

def GetThrustBoolOutput():
    global last_nn_output
    return last_nn_output[0]
def GetReverseThrustBoolOutput():
    global last_nn_output
    return last_nn_output[1]
def GetLeftBoolOutput():
    global last_nn_output
    return last_nn_output[2]
def GetRightBoolOutput():
    global last_nn_output
    return last_nn_output[3]
    
# TODO
    # Un GetOutput qui retourne 2 outputs

def GetShipMoveState(stateArray):
    for key, val in enumerate(stateArray):
        if val == 1 :
            return key
    return -1

def GetShipMoveState2(stateArray):
    i = 0
    v = 0
    print(enumerate(stateArray))
    for key, val in enumerate(stateArray):
        if val > v :
            v = val
            i = key
    return i

def GetOutput4(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    res = n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])
    print(res)
    shipMoveState = GetShipMoveState2(res)
    print(shipMoveState)
    return shipMoveState

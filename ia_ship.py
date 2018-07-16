# TODO : add a description of the inputs in the comments
import neuralnetwork
n = neuralnetwork.NeuralNetwork("neuralnetwork_4_7_1.txt")

def GetOutput(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
    # print shipAngle, " , ", x_dirShipNearestAst, " , ", y_dirShipNearestAst, " , ", relativeSpeed
    a = abs(round(n.Use([shipAngle,x_dirShipNearestAst,y_dirShipNearestAst,relativeSpeed])[0]*10))
    print a
    return a

# def GetOutput(shipAngle, x_dirShipNearestAst=None, y_dirShipNearestAst=None, relativeSpeed=None):
#     if x_dirShipNearestAst is not None:
#         print shipAngle, " , ", x_dirShipNearestAst, " , ", y_dirShipNearestAst, " , ", relativeSpeed
#     else:
#     	print shipAngle
#     return 5



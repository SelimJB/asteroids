import neuralnetwork

n = neuralnetwork.NeuralNetwork("neuralnetwork_4_7_1.txt")
for x in range(1,10000):
    neuralnetwork.InputManager("C:/Users/selim/Desktop/Projets/asteroids/Misc/CLEAN_Inputs_Beaucoup.txt").iterate(n.Train)
    if x % 100 == 0 :
        print x/100,"%"
        neuralnetwork.InputManager("C:/Users/selim/Desktop/Projets/asteroids/Misc/CLEAN_Inputs_Beaucoup.txt").iterate(n.Test)
        n.CheckTest()
        n.WriteNeuralNetwork()
        print "Res : ", round(n.OutputLayer[0]*10)


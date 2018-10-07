import math, random, sys

argv = sys.argv[1:]
path = "./misc/nottrainedneuralnetwork.txt"
inputNeuronsNbr = 4
hiddenNeuronsNbr = 7
outputNbr = 4

def rand(minus, maximum):
	return minus + random.random()*(maximum - minus)

def Write(fileName):
	file = open(fileName, 'w')
	file.write(str(inputNeuronsNbr) + '\t' + str(hiddenNeuronsNbr) + '\t' + str(outputNbr)+ '\n')
	file.write("#\n")
	for row in synapseMatrix1:
		file.write('\t'.join([str(x) for x in row]) + '\n')
	file.write("#\n")
	for row in synapseMatrix2:
		file.write('\t'.join([str(x) for x in row]) + '\n')
	file.close()
	print "\tNN created : \t", fileName

# Arg
if len(argv) == 0 :
	print "\tWithout args default values are used"
	print "\t\tArgs : \t\tpath, inputNeuronsNbr, hiddenNeuronsNbr, outputNbr"
	print "\t\tDefault : \t", path, inputNeuronsNbr, hiddenNeuronsNbr, outputNbr
else :
	path = argv[0] if len(argv) > 0 else path
	inputNeuronsNbr = int(argv[1]) if len(argv) > 1 else inputNeuronsNbr
	hiddenNeuronsNbr = int(argv[2]) if len(argv) > 2 else hiddenNeuronsNbr
	outputNbr = int(argv[3]) if len(argv) > 3 else outputNbr

rangeLimit1 = 1/math.sqrt(inputNeuronsNbr+1)
rangeLimit2 = 1/math.sqrt(hiddenNeuronsNbr+1)

synapseMatrix1 = []
for i in range(0, hiddenNeuronsNbr) :
	synapseRow = []
	for j in range(0, inputNeuronsNbr + 1) :
		synapseRow.append(rand(0, rangeLimit1))
	synapseMatrix1.append(synapseRow)

synapseMatrix2 = []
for i in range(0, outputNbr) :
	synapseRow = []
	for j in range(0, hiddenNeuronsNbr + 1) :
		synapseRow.append(rand(0, rangeLimit2))
	synapseMatrix2.append(synapseRow)


Write(path)
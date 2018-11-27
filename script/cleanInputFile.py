from operator import itemgetter
import ntpath
import  sys

inputFileName = ""
path = "../misc/"
outputFileName = ""


# INPUTS
nbrOfFramesToDeleteBeforeAndAfterADeath = 30
maxSizeOfUniformInputSequences = 50

inputNbr = 4
columnsNbr = None
outputNbr = None
deathColumnNbr = None
# TODO: remove
neutral = '[0.0, 0.0, 0.0, 0.0]'

normalise = True
debug = False

sequencesTotalClean = 0
linesInput = []
imbricatedDeathNbr = 0
linesDeathClean = []
deathSequencesNbr = 0
linesSequenceClean = []
linesSequenceNormalized = []


def clean(i):
    beg = 0 if i < nbrOfFramesToDeleteBeforeAndAfterADeath else i - nbrOfFramesToDeleteBeforeAndAfterADeath
    for x in range(beg,i):
        linesInput[x] = None
    if i + nbrOfFramesToDeleteBeforeAndAfterADeath > len(linesInput):
        end = len(linesInput)
    else :
        end = i + nbrOfFramesToDeleteBeforeAndAfterADeath + 30
        for x in range(i, end):
            if (linesInput[x][deathColumnNbr] == 1):
                global imbricatedDeathNbr
                imbricatedDeathNbr += 1
                end = x + 30
    for x in range(i, end):
        linesInput[x] = None
    return beg

def CleanArray(l):
    res = []
    for i in l :
        if i != None :
            res.append(i)
    return res

def Write(filepath, lines):
    file = open(filepath, 'w')
    file.write('\t'.join(str(e) for e in lines[0][:deathColumnNbr]))
    for l in lines[1:] :
        file.write('\n' + '\t'.join(str(e) for e in l[:deathColumnNbr]))
    file.close()

def GetOutputProportion(lines):
    outputProportion = {}
    for i in lines:
        ind = str(i[inputNbr:deathColumnNbr])
        if ind in outputProportion:
            outputProportion[ind] += 1
        else :
            outputProportion[ind] = 0
    return outputProportion

def Normalise(value, maxV, minV):
    return (value-minV) / (maxV-minV)

def main(argv):
    if len(argv) == 0 or argv[0] == "--help" :
        print "\t\tArgs : \tInput file [,nbrOfFramesToDeleteBeforeAndAfterADeath ,[maxSizeOfUniformInputSequences]]"
        exit()
    elif len(argv) > 0 :
        global inputFileName
        global path
        global outputFileName
        inputFileName = ntpath.basename(argv[0])
        path = ntpath.dirname(argv[0])
        if normalise:
            outputFileName = "CLEAN_NORMALISED_"+inputFileName
        else:
            outputFileName = "CLEAN_"+inputFileName
    if len(argv) > 1 :
        global nbrOfFramesToDeleteBeforeAndAfterADeath
        nbrOfFramesToDeleteBeforeAndAfterADeath =  int(argv[1])
    if len(argv) > 2 :
        global maxSizeOfUniformInputSequences
        maxSizeOfUniformInputSequences = int(argv[2])


if __name__ == "__main__":
    main(sys.argv[1:])



# Open and parse
file = open(ntpath.join(path, inputFileName))
for line in file:
    linesInput.append([float(x) for x in line.split("\t")])
file.close()

# Initialise global var
columnsNbr = len(linesInput[0])
deathColumnNbr = columnsNbr - 1
outputNbr = columnsNbr - inputNbr - 1

# Death nbr
deathNbr = 0
for i in linesInput :
    if i[deathColumnNbr] == 1 :
        deathNbr += 1

# Clean death linesInput
i = 0
while i<len(linesInput):
    v = linesInput[i]
    if (v != None):
        if v[deathColumnNbr] == 1:
            deathSequencesNbr += 1
            i = clean(i)
    i += 1
linesDeathClean = CleanArray(linesInput)

#  Get Output Proportion
outputProportion = GetOutputProportion(linesDeathClean)

# Get biggest 0 sequences
zeroSequences = {}
switch = False
currentIndex = 0
for i,l in enumerate(linesDeathClean):
    output = str(l[inputNbr:deathColumnNbr])
    # Boucler dans le tableau outputProportion
    # NN 2
    # if output == '[0.0, 0.0]' :
    # NN 4 Outputs
    # if output == '[0.0, 0.0, 0.0, 0.0]' or output == '[1.0, 0.0, 0.0, 0.0]' :
    # if output == '[0.0, 0.0, 0.0, 0.0]' : # Pour inputMode 3
    if output == '[1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]' : 
        if switch == False :
            switch = True
            currentIndex = i
            zeroSequences[currentIndex] = 1
        else :
            zeroSequences[currentIndex] += 1
    else :
        switch = False

# Sort sequences
sortedZeroSequences = sorted(zeroSequences.items(), key=itemgetter(1), reverse = True)

# Clean sequences
toCleanSequences = [(x,x+y) for (x,y) in sortedZeroSequences if y > maxSizeOfUniformInputSequences]
cleanedSequencesNbr = len(toCleanSequences)
for s in toCleanSequences :
    for i in range(s[0],s[1]):
        linesDeathClean[i] = None
linesSequenceClean = CleanArray(linesDeathClean)

# Get Output Proportion
outputProportion2 = GetOutputProportion(linesSequenceClean)

# Normalise
maxArray = [max([line[i] for line in linesSequenceClean]) for i in range(inputNbr)]
minArray = [min([line[i] for line in linesSequenceClean]) for i in range(inputNbr)]
for line in linesSequenceClean:
    ln = []
    for i in range(inputNbr):
        ln.append(Normalise(line[i], maxArray[i], minArray[i]))
    for j in range(inputNbr, inputNbr + outputNbr):
        ln.append(line[j])
    linesSequenceNormalized.append(ln)

# Write
if normalise :
    Write(ntpath.join(path,outputFileName), linesSequenceNormalized)
else :
    Write(ntpath.join(path,outputFileName), linesSequenceClean)


# Logs
if debug :
    print "\n\tSorted zero sequences : ", sortedZeroSequences
print "\n\tRes : ", ntpath.join(path,outputFileName)
print "\tNormalized" if normalise else "\tNot normalized"
print "\n\tInputNbr : ", inputNbr,"\tOutputNbr : ", outputNbr
print "\tbrOfFramesToDeleteBeforeAndAfterADeath = ", nbrOfFramesToDeleteBeforeAndAfterADeath, ", maxSizeOfUniformInputSequences = ", maxSizeOfUniformInputSequences
print "\tInput lines nbr : ", len(linesInput)  

print "\n\tClean death frames : "
print "\t\tDeath sequences nbr : ", deathSequencesNbr
print "\t\tDeath nbr : ", deathNbr
print "\t\tNested death nbr : ", imbricatedDeathNbr
print "\t\tNumber of cleaned lines : ", len(linesInput) - len(linesDeathClean)
print "\t\tOutput proportion : ",outputProportion
print "\t\tNumber of lines : ", len(linesDeathClean)

print "\n\tClean long sequence frames :"
print "\t\tNumber of cleaned lines : ", len(linesDeathClean) - len(linesSequenceClean)
print "\t\tNumber of cleaned sequences : ", cleanedSequencesNbr
print "\t\tOutput proportion 2 : ", outputProportion2
print "\t\tNumber of lines : ", len(linesSequenceClean)
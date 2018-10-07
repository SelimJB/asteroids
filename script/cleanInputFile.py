from operator import itemgetter
import ntpath
import  sys

inputFileName = ""
path = "../misc/"
outputFileName = ""


# INPUTS
frameLatitude = 30
maxSequenceLength = 50
verbose = False

sequencesTotalClean = 0
linesInput = []
imbricatedDeathNbr = 0
linesDeathClean = []
deathSequencesNbr = 0
linesSequenceClean = []

# NEW
columnsNbr = None
deathColumnNbr = None

def clean(i):
    beg = 0 if i < frameLatitude else i - frameLatitude
    for x in range(beg,i):
        linesInput[x] = None
    if i + frameLatitude > len(linesInput):
        end = len(linesInput)
    else :
        end = i + frameLatitude + 30
        for x in range(i, end):
            if (linesInput[x][deathColumnNbr] == 1):
                global imbricatedDeathNbr
                imbricatedDeathNbr += 1
                end = x + 30
    for x in range(i, end):
        linesInput[x] = None
    # print beg, " ",end
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
        ind = str(i[4:deathColumnNbr])
        if ind in outputProportion:
            outputProportion[ind] += 1
        else :
            outputProportion[ind] = 0
    return outputProportion

def main(argv):
    if len(argv) == 0 or argv[0] == "--help" :
        print "ZIBOUBABIBOU"
        exit()
    elif len(argv) > 0 :
        global inputFileName
        global path
        global outputFileName
        inputFileName = ntpath.basename(argv[0])
        path = ntpath.dirname(argv[0])
        outputFileName = "CLEAN_"+inputFileName
    if len(argv) > 1 :
        global frameLatitude
        frameLatitude =  int(argv[1])
    if len(argv) > 2 :
        global maxSequenceLength
        maxSequenceLength = int(argv[2])
    if len(argv) > 3 and argv[3] == "-v" :
        global verbose
        verbose = True


if __name__ == "__main__":
    main(sys.argv[1:])


# Open and parse
file = open(ntpath.join(path, inputFileName))
for line in file:
    linesInput.append([float(x) for x in line.split("\t")])
file.close()
columnsNbr = len(linesInput[0])
deathColumnNbr = columnsNbr - 1


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
    output = str(l[4:deathColumnNbr])
    # Boucler dans le tableau outputProportion
    # NN 2
    # if output == '[0.0, 0.0]' :
    # NN 4 Outputs
    # if output == '[0.0, 0.0, 0.0, 0.0]' or output == '[1.0, 0.0, 0.0, 0.0]' :
    if output == '[0.0, 0.0, 0.0, 0.0]' :
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
toCleanSequences = [(x,x+y) for (x,y) in sortedZeroSequences if y > maxSequenceLength]
cleanedSequencesNbr = len(toCleanSequences)
for s in toCleanSequences :
    for i in range(s[0],s[1]):
        linesDeathClean[i] = None
linesSequenceClean = CleanArray(linesDeathClean)

# Get Output Proportion
outputProportion2 = GetOutputProportion(linesSequenceClean)

# Write
Write(ntpath.join(path,outputFileName), linesSequenceClean)



# Logs
if verbose :
    print "\n", ntpath.join(path,outputFileName)
    print "\nSorted zero sequences : ", sortedZeroSequences
print "\nInput lines nbr : ", len(linesInput)  
print "First path : "
print "\tDeath sequences nbr : ", deathSequencesNbr
print "\tDeath nbr : ", deathNbr
print "\tNested death nbr : ", imbricatedDeathNbr
print "\tNumber of cleaned lines : ", len(linesInput) - len(linesDeathClean)
print "\tOutput proportion : ",outputProportion
print "\tNumber of lines : ", len(linesDeathClean)

print "Second path :"
print "\tNumber of cleaned lines : ", len(linesDeathClean) - len(linesSequenceClean)
print "\tNumber of cleaned sequences : ", cleanedSequencesNbr
print "\tOutput proportion 2 : ", outputProportion2
print "\tNumber of lines : ", len(linesSequenceClean)
print "\n"


# TODO
    # OK    Finish clean sequences
    # OK    Write
    # Other sequences than 0 sequences
    # Possibility to show stats before rightinh
    # Write Main methode
        # Arg :
            # Show sortedSequences
            # Write
    # Clean code, good names
    # Modulate

    # Clean Inputs file


# TODO
    # FONCTION HELP
    # Finir Get Biggest 0 Sequence generique

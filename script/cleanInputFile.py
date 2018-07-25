from operator import itemgetter
import ntpath
import  sys

inputFileName = "Inputs_Many.txt"
path = "../misc/"
outputFileName = "CLEAN_" + inputFileName

sequencesTotalClean = 0
linesInput = []
frameLatitude = 30
i_sequencesCleanLimit = 30
imbricatedDeathNbr = 0
linesDeathClean = []
deathSequencesNbr = 0
linesSequenceClean = []

def clean(i):
    beg = 0 if i < frameLatitude else i - frameLatitude
    for x in range(beg,i):
        linesInput[x] = None
    if i + frameLatitude > len(linesInput):
        end = len(linesInput)
    else :
        end = i + frameLatitude + 30
        for x in range(i, end):
            if (linesInput[x][5] == 1):
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
    file.write('\t'.join(str(e) for e in lines[0][:5]))
    for l in lines[1:] :
        file.write('\n' + '\t'.join(str(e) for e in l[:5]))
    file.close()

def GetOutputProportion(lines):
    outputProportion = {}
    for i in lines:
        ind = int(i[4])
        if ind in outputProportion:
            outputProportion[ind] += 1
        else :
            outputProportion[ind] = 0
    return outputProportion

def main(argv):
    if argv[0] :
        global inputFileName
        global path
        inputFileName = ntpath.basename(argv[0])
        path = ntpath.dirname(argv[0])



if __name__ == "__main__":
    main(sys.argv[1:])

# Open and parse
file = open(ntpath.join(path, inputFileName))
for line in file:
    linesInput.append([float(x) for x in line.split("\t")])
file.close()


# Death nbr
deathNbr = 0
for i in linesInput :
    if i[5] == 1 :
        deathNbr += 1


# Clean death linesInput
i = 0
while i<len(linesInput):
    v = linesInput[i]
    if (v != None):
        if v[5] == 1:
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
    output = int(l[4])
    if output == 0 :
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
toCleanSequences = [(x,x+y) for (x,y) in sortedZeroSequences if y > i_sequencesCleanLimit]
cleanedSequencesNbr = len(toCleanSequences)
for s in toCleanSequences :
    for i in range(s[0],s[1]):
        linesDeathClean[i] = None
linesSequenceClean = CleanArray(linesDeathClean)

# Get Output Proportion
outputProportion2 = GetOutputProportion(linesSequenceClean)

# Write
Write(path + outputFileName, linesSequenceClean)





print "\n\nnInput lines nbr : ", len(linesInput)  

print "First path : "
print "\tDeath sequences nbr : ", deathSequencesNbr
print "\tDeath nbr : ", deathNbr
print "\tNested death nbr : ", imbricatedDeathNbr
print "\tNumber of lines : ", len(linesDeathClean)
print "\tNumber of cleaned lines : ", len(linesInput) - len(linesDeathClean)
print "\tOutput proportion : ",outputProportion

print "Second path :"
print "\tOutput proportion 2 : ", outputProportion2
print "\tOutput linesInput 2", len(linesSequenceClean)
print "\tNumber of cleaned lines : ", len(linesDeathClean) - len(linesSequenceClean)
print "\tNumber of cleaned sequences : ", cleanedSequencesNbr
print "\n"



    # Clean Inputs file

inputFileName = "Inputs_Many.txt"

imbricatedErrorNbr = 0
path = "misc/"
outputFileName = "Clean_" + inputFileName
lines = []
frameLatitude = 30
err = 0
cleanedLinesNbr = 0
res = []

def clean(i):
    beg = 0 if i < frameLatitude else i - frameLatitude
    for x in range(beg,i):
        lines[x] = None
    if i + frameLatitude > len(lines):
        end = len(lines)
    else :
        end = i + frameLatitude + 30
        for x in range(i, end):
            if (lines[x][5] == 1):
                global imbricatedErrorNbr
                imbricatedErrorNbr += 1
                end = x + 30
    for x in range(i, end):
        lines[x] = None
    print beg, " ",end
    return beg


# Open and parse
file = open(path + inputFileName)
for line in file:
    lines.append([float(x) for x in line.split("\t")])
file.close()

# Clean
i = 0
while i<len(lines):
    v = lines[i]
    if (v != None):
        if v[5] == 1:
            err += 1
            i = clean(i)
    i += 1

# Write
file = open(path + outputFileName, 'w')
for i in lines:
    if i == None :
        cleanedLinesNbr+=1
    if i != None :
        res.append(i)
        file.write('\t'.join(str(e) for e in i[:5]) + '\n')
file.close()

# Get Output Proportion
stats = {}
for i in res:
    ind = int(i[4])
    if ind in stats:
        stats[ind] += 1
    else :
        stats[ind] = 0


print "Cleaned lines : ", cleanedLinesNbr
print "Err : ",err
print "Imbricated err : ", imbricatedErrorNbr
print "Input lines", len(lines)  
print "Output lines", len(res)
print stats
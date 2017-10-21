#!/usr/bin/python2.7
#scope 


trainX = [[1.0, 2.0], [1.0, 3.0], [2.0, 3.0], [2.0, 1.0], [3.0, 1.0], [3.0, 2.0]]
trainY = [1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0]
zipped =zip(trainX, trainY)
print zipped
for (x, y) in zipped:
    print x, y






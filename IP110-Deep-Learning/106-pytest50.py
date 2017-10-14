#!/usr/bin/python2.7
MyList = []
for i in range(10):
    MyList.append(i)
print MyList
#symmetric??
del MyList[:]   #empty a list
for i in range(-2, 2):
    MyList.append(i)
print MyList
#symmetric
del MyList[:]
for i in range(-2, 2 + 1):
    MyList.append(i)
print MyList
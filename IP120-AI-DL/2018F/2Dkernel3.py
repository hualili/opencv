#!/usr/bin/python2.7
# a 4 x 3 list
# for loop demo 
# access each entry of the kernel 

MyFirstKernel = [[1.0, 1.0, 1.0], [0., 0., 0.], [-1.0, -1.0, -1.0], [-2.0, -2.0, -2.0]]

print (range(len(MyFirstKernel)))
print ("len MyFirstKernel") 

for i in range(len(MyFirstKernel)):
    for j in range(len(MyFirstKernel[i])):
        print (MyFirstKernel[i][j]) 






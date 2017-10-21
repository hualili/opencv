#!/usr/bin/python2.7

# wx + b
def linearclassifer2x2(w, x, theta):
    return w[0] * x[0] + w[1] * x[1] + theta

#sign function
def sign(lc):
    if lc > 0:
        return 1
    else:
        return 0

w = [0.5, 0.5]
x = [1, 2]
t = 0.5
print sign(linearclassifer2x2(w,x,t))
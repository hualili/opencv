#!/usr/bin/python2.7

# wx + b
def linearclassifer2x2(w, x, theta):
    return float(w[0]) * float(x[0]) + float(w[1]) * float(x[1]) + float(theta)

#sign function
def sign(lc):
    if lc > 0:
        return 1
    else:
        return 0

def updatew(w, x, t, gain, desiredoutput):
    y = sign(linearclassifer2x2(w, x, t))
    d = desiredoutput
    w[0] = w[0] + gain * (d - y) * x[0]
    w[1] = w[1] + gain * (d - y) * x[1]



w = [0.5, 0.5]
x = [1, 2]
t = 0.5
g = 0.1
d = 1
print w
updatew(w,x,t,g,d)
print w

w = [0.5, 0.5]
x = [3, 2]
t = 0.5
g = 0.1
d = 0
print w
updatew(w,x,t,g,d)
print w
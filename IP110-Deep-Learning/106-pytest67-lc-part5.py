#!/usr/bin/python2.7
# wx + b
def linearclassifer2x2(w, x, theta):
    return float(w[0]) * float(x[0]) + float(w[1]) * float(x[1]) + float(theta)

#sign function
def sign(lc):
    if lc > 0.0:
        return 1.0
    else:
        return 0.0

def updatew(w, x, t, gain, desiredoutput):
    y = sign(linearclassifer2x2(w, x, t))
    d = desiredoutput
    w[0] = w[0] + gain * (d - y) * x[0]
    w[1] = w[1] + gain * (d - y) * x[1]


if __name__ == "__main__":
    w = [0.5, 0.5]
    X = [[1, 2],[1,3],[2,3],[2,1],[3,1],[3,2]]
    Y = [1,1,1,0,0,0]
    t = 0.5
    g = 0.1

    epoch = 5

    print "gain = .1"
    for j in range(epoch):
        print "epoch: ", j
        for i in range(len(X)):
            updatew(w,X[i],t,g,Y[i])
            print w

    x_test = [4, 2]
    output = sign(linearclassifer2x2(w, x_test, g))
    print x_test, "output", output

    x_test = [1, 4]
    output = sign(linearclassifer2x2(w, x_test, g))
    print x_test, "output", output

    print "new gain = .3"

    w = [0.5, 0.5]
    g = 0.3

    for j in range(epoch):
        print "epoch: ", j
        for i in range(len(X)):
            updatew(w,X[i],t,g,Y[i])
            print w

    x_test= [4, 2]
    output = sign(linearclassifer2x2(w,x_test,g))
    print x_test, "output", output

    x_test = [1, 4]
    output = sign(linearclassifer2x2(w, x_test, g))
    print x_test, "output", output
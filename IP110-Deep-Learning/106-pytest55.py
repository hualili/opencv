#!/usr/bin/python2.7
import math

def LoG2d(x, y, sigma):
    xyp2 = x ** 2 + y ** 2
    LoG = ((xyp2 - 2 * sigma**2) /(math.sqrt(2 * math.pi) * math.pow(sigma, 5))) * math.exp(-xyp2 / (2 * sigma**2))
    return LoG

if __name__ == "__main__":
    #try to see if position (-1, 0), (1, 0) and (0, -1), (0, 1) are all same
    print LoG2d(1, 0, 1.8)
    print LoG2d(-1, 0, 1.8)
    print LoG2d(0, 1, 1.8)
    print LoG2d(0, -1, 1.8)

    #seed
    print LoG2d(0, 0, 1.8)
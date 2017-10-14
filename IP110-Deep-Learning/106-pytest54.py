#!/usr/bin/python2.7
import math

x = 1.0
y = 1.0
sigma = 1.8

xyp2 = x**2 + y**2

power_over_e = -xyp2 / (2 * sigma**2)
print power_over_e

LoG_e = math.pow(math.e, power_over_e)
print LoG_e

#2d Laplacian of Gaussian
normalcoeff = 1/(math.sqrt(2 * math.pi) * math.pow(sigma, 5))
LoG_a = (xyp2 - 2 * sigma**2) * normalcoeff
print LoG_a

LoG = LoG_a * LoG_e

print LoG

#in one formula
LoG = ((xyp2 - 2 * sigma**2) /(math.sqrt(2 * math.pi) * math.pow(sigma, 5))) * math.exp(-xyp2 / (2 * sigma**2))

print LoG

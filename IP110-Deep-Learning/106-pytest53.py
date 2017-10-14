#!/usr/bin/python2.7
import math

x = 1.0
y = 1.0
sigma = 1.8

xyp2 = x**2 + y**2

power_over_e = -1.0 * xyp2/ (2 * sigma**2)
print power_over_e

LoG_e = math.pow(math.e, power_over_e)
print LoG_e

LoG_e = math.exp(power_over_e)
print LoG_e

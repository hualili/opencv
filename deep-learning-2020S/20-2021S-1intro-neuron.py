'''
********************************************************************
* Program: 1intro-nn.py                                            *
* Coded by:                                                        *
* Date: Jun 2019                                                   *
*                                                                  *
* Reference: https://victorzhou.com/blog/intro-to-neural-networks/ *
* Note:                                                            *
* 1. tested on python 3.6 by HL                                    *
* 2. This code is for testing of a single neuron with 2 inputs     * 
*    e.g., X = (x1, x2), W = (w1, w2)                              *  
********************************************************************
'''
import numpy as np

def sigmoid(x):
  # Our activation function: f(x) = 1 / (1 + e^(-x))
  return 1 / (1 + np.exp(-x))

class Neuron:
  def __init__(self, weights, bias):
    self.weights = weights
    self.bias = bias

  def feedforward(self, inputs):
    # Weight inputs, add bias, then use the activation function
    total = np.dot(self.weights, inputs) + self.bias
    return sigmoid(total)

weights = np.array([0, 1]) # w1 = 0, w2 = 1
bias = 4                   # b = 4
n = Neuron(weights, bias)

x = np.array([2, 3])       # x1 = 2, x2 = 3
print(n.feedforward(x))    # 0.9990889488055994

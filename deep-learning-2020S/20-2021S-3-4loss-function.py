'''
********************************************************************
* Program: 4loss-function.py                                       *
* Coded by:                                                        *
* Date: Jun 2019                                                   *
*                                                                  *
* Reference: https://victorzhou.com/blog/intro-to-neural-networks/ *
* Note:                                                            *
* 1. tested on python 3.6 by HL                                    *
* 2. This code is for testing of a feed forward nn based on the    *
*    single neuron as a basic building block with 2 inputs         * 
*    e.g., X = (x1, x2), W = (w1, w2)                              *  
********************************************************************
'''
import numpy as np

def mse_loss(y_true, y_pred):
  # y_true and y_pred are numpy arrays of the same length.
  return ((y_true - y_pred) ** 2).mean()

y_true = np.array([1, 0, 0, 1])
y_pred = np.array([0, 0, 0, 0])

print(mse_loss(y_true, y_pred)) # 0.5

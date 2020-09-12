
'''
   Program  : introNN.py; 
   Version  : 1.0;
   Date     : Sept. 10, 2020
   Coded by : (see the reference below) 
   Modified by: HL for adapative learning 
   (1) introduced a naming convention to track weights starting and ending neuron
   (2) load prior trained weights-bias file to accelerate the trainning, e.g., adaptive 
       learning 

Ref: https://github.com/vzhou842/neural-network-from-scratch/blob/master/network.py 
''' 

import numpy as np

def sigmoid(x):
  # Sigmoid activation function: f(x) = 1 / (1 + e^(-x))
  return 1 / (1 + np.exp(-x))

def deriv_sigmoid(x):
  # Derivative of sigmoid: f'(x) = f(x) * (1 - f(x))
  fx = sigmoid(x)
  return fx * (1 - fx)

def mse_loss(y_true, y_pred):
  # y_true and y_pred are numpy arrays of the same length.
  return ((y_true - y_pred) ** 2).mean()

class OurNeuralNetwork:
  '''
  A neural network with:
    - 2 inputs
    - a hidden layer with 2 neurons (h1, h2)
    - an output layer with 1 neuron (o1)

  *** DISCLAIMER ***:
  The code below is intended to be simple and educational, NOT optimal.
  Real neural net code looks nothing like this. DO NOT use this code.
  Instead, read/run it to understand how this specific network works.
  '''
  '''
  HL: Part A
  To do: (1) change the subscripts to w_i_j, e.g., w1 should be w_1_1, etc. 
       (2) change the bias to the same style notation, change it to b_i_j

  '''

  def __init__(self):
    # load prior Weights and biases from a text file
    s=[]
    with open('trained_weights_bias.txt','r') as f:
        for line in f:
            for num in line.split(','):
                s.append(float(num))
    self.w_1_1=s[0]
    self.w_1_2=s[1]
    self.b_1_1=s[2]
    
    self.w_1_3=s[3]
    self.w_1_4=s[4]
    self.b_1_2=s[5]
    
    self.w_2_1=s[6]
    self.w_2_2=s[7]
    self.b_2_1=s[8]  
    
    self.w_2_3=s[9]
    self.w_2_4=s[10]
    self.b_2_2=s[11] 
    
    self.w_3_1=s[12]
    self.w_3_2=s[13]
    self.b_3_1=s[14] 


  def feedforward(self, x):
    #HL 2020-9-10, the 1st hidden layer 
    h_1_1 = sigmoid(self.w_1_1 * x[0] + self.w_1_2 * x[1] + self.b_1_1)
    h_1_2 = sigmoid(self.w_1_3 * x[0] + self.w_1_4 * x[1] + self.b_1_2)
    #HL 2020-9-10, the 2nd hidden layer     
    h_2_1 = sigmoid(self.w_2_1 * h_1_1 + self.w_2_2 * h_1_2 + self.b_2_1)
    h_2_2 = sigmoid(self.w_2_3 * h_1_1 + self.w_2_4 * h_1_2 + self.b_2_2)
    
    o_1 = sigmoid(self.w_3_1 * h_2_1 + self.w_3_2 * h_2_2 + self.b_3_1)
    return o_1

  def train(self, data, all_y_trues):
    '''
    - data is a (n x 2) numpy array, n = # of samples in the dataset.
    - all_y_trues is a numpy array with n elements.
      Elements in all_y_trues correspond to those in data.
    '''
    learn_rate = 0.1
    epochs = 1000 # number of times to loop through the entire dataset

    for epoch in range(epochs):
      for x, y_true in zip(data, all_y_trues):
        # --- Do a feedforward (we'll need these values later)
        sum_h_1_1 = self.w_1_1 * x[0] + self.w_1_2 * x[1] + self.b_1_1
        h_1_1 = sigmoid(sum_h_1_1)

        sum_h_1_2 = self.w_1_3 * x[0] + self.w_1_4 * x[1] + self.b_1_2
        h_1_2 = sigmoid(sum_h_1_2)
        
        sum_h_2_1 = self.w_2_1 * h_1_1 + self.w_2_2 * h_1_2 + self.b_2_1
        h_2_1 = sigmoid(sum_h_2_1)

        sum_h_2_2 = self.w_2_3 * h_1_1 + self.w_2_4 * h_1_2 + self.b_2_2
        h_2_2 = sigmoid(sum_h_2_2)

        sum_o_1 = self.w_3_1 * h_2_1 + self.w_3_2 * h_2_2 + self.b_3_1
        o_1 = sigmoid(sum_o_1)
        y_pred = o_1
        
        '''
        HL, 2020-Sept-10
        (1) create multiple nodes (neurons) at the output layer 
        e.g., 
        sum_o_i_j = self.w_i_j??? * h_i_j??? + self.w_i_j??? * h_i_j??? + self.b_i_j???
        o_k = sigmoid(sum_o_i_j)
 
        '''

        '''
        HL, 2020-Sept-10 
        (1) create y_pred_k = o_k, e.g., 
        y_pred_1 
        y_pred_2 
        ... 

        '''


        '''
        HL: 2020-9-10 
        (1) Create NN architecture by creating addition hidden layer 
        (2) hidden layer naming should be consistent with w_i_j, and 
        b_i_j, e.g., h_i_j; 

        '''

        # --- Calculate partial derivatives.
        # --- Naming: d_L_d_w1 represents "partial L / partial w1"
        d_L_d_ypred = -2 * (y_true - y_pred)

        d_ypred_d_h_1_1 = self.w_2_1 * deriv_sigmoid(sum_h_2_1)
        d_ypred_d_h_1_2 = self.w_2_2 * deriv_sigmoid(sum_h_2_2) 
        
        # Neuron o1
        d_ypred_d_w_3_1 = h_2_1 * deriv_sigmoid(sum_o_1)
        d_ypred_d_w_3_2 = h_2_2 * deriv_sigmoid(sum_o_1)
        d_ypred_d_b_3_1 = deriv_sigmoid(sum_o_1)
        
        d_ypred_d_h_2_1 = self.w_3_1 * deriv_sigmoid(sum_o_1)
        d_ypred_d_h_2_2 = self.w_3_2 * deriv_sigmoid(sum_o_1)
        

        # Neuron h_1_1    h1
        d_h_1_1_d_w_1_1 = x[0] * deriv_sigmoid(sum_h_1_1)
        d_h_1_1_d_w_1_2 = x[1] * deriv_sigmoid(sum_h_1_1)
        d_h_1_1_d_b_1_1 = deriv_sigmoid(sum_h_1_1)

        # Neuron h_1_2     h2
        d_h_1_2_d_w_1_3 = x[0] * deriv_sigmoid(sum_h_1_2)
        d_h_1_2_d_w_1_4 = x[1] * deriv_sigmoid(sum_h_1_2)
        d_h_1_2_d_b_1_2 = deriv_sigmoid(sum_h_1_2)
        
        # Neuron h_2_1     h3
        d_h_2_1_d_w_2_1 = h_1_1 * deriv_sigmoid(sum_h_2_1)
        d_h_2_1_d_w_2_2 = h_1_2 * deriv_sigmoid(sum_h_2_1)
        d_h_2_1_d_b_2_1 = deriv_sigmoid(sum_h_2_1)

        # Neuron h_2_2     h4
        d_h_2_2_d_w_2_3 = h_1_1 * deriv_sigmoid(sum_h_2_2)
        d_h_2_2_d_w_2_4 = h_1_2 * deriv_sigmoid(sum_h_2_2)
        d_h_2_2_d_b_2_2 = deriv_sigmoid(sum_h_2_2)

        # --- Update weights and biases
        
        # Neuron h1
        self.w_1_1 -= learn_rate * d_L_d_ypred * d_ypred_d_h_1_1 * d_h_1_1_d_w_1_1
        self.w_1_2 -= learn_rate * d_L_d_ypred * d_ypred_d_h_1_1 * d_h_1_1_d_w_1_2
        self.b_1_1 -= learn_rate * d_L_d_ypred * d_ypred_d_h_1_1 * d_h_1_1_d_b_1_1

        # Neuron h2
        self.w_1_3 -= learn_rate * d_L_d_ypred * d_ypred_d_h_1_2 * d_h_1_2_d_w_1_3
        self.w_1_4 -= learn_rate * d_L_d_ypred * d_ypred_d_h_1_2 * d_h_1_2_d_w_1_4
        self.b_1_2 -= learn_rate * d_L_d_ypred * d_ypred_d_h_1_2 * d_h_1_2_d_b_1_2
        
        # Neuron h3
        self.w_2_1 -= learn_rate * d_L_d_ypred * d_ypred_d_h_2_1 * d_h_2_1_d_w_2_1
        self.w_2_2 -= learn_rate * d_L_d_ypred * d_ypred_d_h_2_1 * d_h_2_1_d_w_2_2
        self.b_2_1 -= learn_rate * d_L_d_ypred * d_ypred_d_h_2_1 * d_h_2_1_d_b_2_1

        # Neuron h4
        self.w_2_3 -= learn_rate * d_L_d_ypred * d_ypred_d_h_2_2 * d_h_2_2_d_w_2_3
        self.w_2_4 -= learn_rate * d_L_d_ypred * d_ypred_d_h_2_2 * d_h_2_2_d_w_2_4
        self.b_2_2 -= learn_rate * d_L_d_ypred * d_ypred_d_h_2_2 * d_h_2_2_d_b_2_2

        # Neuron o1
        self.w_3_1 -= learn_rate * d_L_d_ypred * d_ypred_d_w_3_1
        self.w_3_2 -= learn_rate * d_L_d_ypred * d_ypred_d_w_3_2
        self.b_3_1 -= learn_rate * d_L_d_ypred * d_ypred_d_b_3_1

        

      # --- Calculate total loss at the end of each epoch
      if epoch % 10 == 0:
        y_preds = np.apply_along_axis(self.feedforward, 1, data)
        loss = mse_loss(all_y_trues, y_preds)
        print("Epoch %d loss: %.3f" % (epoch, loss))
        

#-----------------------------------
# Define dataset
#-----------------------------------
data = np.array([
  [1, 2.5],     # person A
  [2, 2.3],     #person A
  [1, 3],       # person A
  [2.1, 3.4],   # Person A
  [2.1, 1], # person B
  [3, 2.1],  #person B
  [3.3, 1], # person B
  [3, 2.3] # person B
])
all_y_trues = np.array([
  1, # person A
  1, # person A
  1, # person A
  1, # person A
  0, # person B
  0, # person B
  0, # person B
  0, # person B
])

# Train our neural network!
network = OurNeuralNetwork()
network.train(data, all_y_trues)


# Detection
testperson1 = np.array([2.2, 3.5]) # A person's face 
testperson2 = np.array([3.2, 2]) # Another person's face  
print("person1 : %.3f" % network.feedforward(testperson1))    # 0.951 - F???
print("person2: %.3f" % (network.feedforward(testperson2))) # 0.039 - M???








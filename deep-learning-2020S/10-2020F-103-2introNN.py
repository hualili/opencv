'''---------------------------------------------------
   Program  : 2introNN.py; 
   Version  : 1.0;
   Date     : Sept. 8, 2020 
   Coded by : (see the reference below) 
   Modified by: Harry Li for adapative learning 
Ref: https://github.com/vzhou842/neural-network-from-scratch/blob/master/network.py 
-------------------------------------------------------''' 

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

#HL, 2020-9-8: Part A 
# (1) load the saved weights/bias from the file;
# (2) second init function which read/load from the
#     saved/trained weights/bias   

  def __init__(self):
    # Weights
    self.w1 = np.random.normal()
    self.w2 = np.random.normal()
    self.w3 = np.random.normal()
    self.w4 = np.random.normal()
    self.w5 = np.random.normal()
    self.w6 = np.random.normal()

    # Biases
    self.b1 = np.random.normal()
    self.b2 = np.random.normal()
    self.b3 = np.random.normal()

# To do: HL 2020-9-8, Part B 
#   (1) change the naming conversion from single 
#       hidden layer to multiple hidden layers 
#       e.g., from h1 -> h_11 (the 1st is for the layer
#       and 2nd is for the 1st neuron on this layer), 
#       to generalize, we have h_1i, for i=1,2,... and
#       h_ki, k=1,0, ..., 
#       k: (for the layer) the kth hidden layer
#       i: (for the neuron on that layer) the ith neuron @ h layer k

  def feedforward(self, x):
    # x is a numpy array with 2 elements.
    h1 = sigmoid(self.w1 * x[0] + self.w2 * x[1] + self.b1)
    h2 = sigmoid(self.w3 * x[0] + self.w4 * x[1] + self.b2)
    o1 = sigmoid(self.w5 * h1 + self.w6 * h2 + self.b3)
    return o1

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
        sum_h1 = self.w1 * x[0] + self.w2 * x[1] + self.b1
        h1 = sigmoid(sum_h1)

        sum_h2 = self.w3 * x[0] + self.w4 * x[1] + self.b2
        h2 = sigmoid(sum_h2)

        sum_o1 = self.w5 * h1 + self.w6 * h2 + self.b3
        o1 = sigmoid(sum_o1)
        y_pred = o1

        # --- Calculate partial derivatives.
        # --- Naming: d_L_d_w1 represents "partial L / partial w1"
        d_L_d_ypred = -2 * (y_true - y_pred)

        # Neuron o1
        d_ypred_d_w5 = h1 * deriv_sigmoid(sum_o1)
        d_ypred_d_w6 = h2 * deriv_sigmoid(sum_o1)
        d_ypred_d_b3 = deriv_sigmoid(sum_o1)

        d_ypred_d_h1 = self.w5 * deriv_sigmoid(sum_o1)
        d_ypred_d_h2 = self.w6 * deriv_sigmoid(sum_o1)

        # Neuron h1
        d_h1_d_w1 = x[0] * deriv_sigmoid(sum_h1)
        d_h1_d_w2 = x[1] * deriv_sigmoid(sum_h1)
        d_h1_d_b1 = deriv_sigmoid(sum_h1)

        # Neuron h2
        d_h2_d_w3 = x[0] * deriv_sigmoid(sum_h2)
        d_h2_d_w4 = x[1] * deriv_sigmoid(sum_h2)
        d_h2_d_b2 = deriv_sigmoid(sum_h2)

        # --- Update weights and biases
        # Neuron h1

# HL 2020-9-7: PART C 
#    (1) Save these trained weights/bias into a file
#        trained_weights_bias.txt 
#        format of the saved data: 
#        w1, w2, b1
#        w3, w4, b2
#        w5, w6, b3 
#    Note: for now just the final converged result 

# HL 2020-9-7, To do PART D 
#     (1) change the naming convension as follows to match up
#         to the hidden layer naming convension 
#       w_ij
#       i: the ith layer 
#       j: the jth neuron on the ith layer 

        self.w1 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_w1
        self.w2 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_w2
        self.b1 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_b1

        # Neuron h2
        self.w3 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_w3
        self.w4 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_w4
        self.b2 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_b2

        # Neuron o1
        self.w5 -= learn_rate * d_L_d_ypred * d_ypred_d_w5
        self.w6 -= learn_rate * d_L_d_ypred * d_ypred_d_w6
        self.b3 -= learn_rate * d_L_d_ypred * d_ypred_d_b3

      # --- Calculate total loss at the end of each epoch
      if epoch % 10 == 0:
        y_preds = np.apply_along_axis(self.feedforward, 1, data)
        loss = mse_loss(all_y_trues, y_preds)
        print("Epoch %d loss: %.3f" % (epoch, loss))

#-----------------------------------
# Define dataset and all_y_trues 
#-----------------------------------
data = np.array([
  [1, 2.5],     # person A
  [1, 3],       # person A
  [2.1, 3.4],   # Person A
  [2.1, 1], # person B
  [3.3, 1], # person B
  [3, 2.3], # person B
# HL 2020-9-7 Part E 
# for the testing of adaptive learning 
# (1) create a new program based on this one, but with init
#     function defined by loading/reading trained weights/biases
# (2) Under the same convergence criteria, NN will stop training
#     when reaching the same loss function, e.g., accuracy
# (3) record the number of EPOCHS N_new, and compare
#     a. the loss function for both programs when stopped training; 
#     b. the EPOCHS number, e.g., N vs. N_new, and hope to 
#        see N > N_new 
])
all_y_trues = np.array([
  1, # person A
  1, # person A
  1, # person A
  0, # person B
  0, # person B
  0, # person B
])

# Train our neural network!
network = OurNeuralNetwork()
network.train(data, all_y_trues)

# Detection
testperson1 = np.array([2, 2.3]) # A person's face 
testperson2 = np.array([3, 2.1]) # Another person's face  
print("person1 : %.3f" % network.feedforward(testperson1))    # 0.951 - F???
print("person2: %.3f" % (1-network.feedforward(testperson2))) # 0.039 - M???


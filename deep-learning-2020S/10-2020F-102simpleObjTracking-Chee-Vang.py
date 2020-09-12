'''
Simple Object Tracker
Coded by: Chee Vang, Sept. 10, 2020
Note: per Deep Learning Computer Vision Class by Dr. Harry Li
'''

import cv2
import numpy as np
import math
from operator import itemgetter 


# (1) Read txt file with 7x7 for first image and print
def readImage(fileName):
	frame = np.loadtxt(fileName, dtype = np.uint8)
	print('Image:', *frame, sep='\n')
	return frame

# (2) Prompt for threshold T, then binarized test image and print
def promptThreshold(frame):
	T = input('\nEnter threshold: ')
	_, B = cv2.threshold(frame, int(T)-1, 1, 0)
	print('\nBinary Image:', *B, sep='\n')
	return T, B

# (3) Compute centroid (x_bar,y_bar) and print
def findCentroid(B):
	# ---------- Finding objects ----------
	contour, _ = cv2.findContours(B, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	#--------------------------------------

	A = []
	x_t = []
	y_t = []
	centroid = []
	
	# For each object find the area and (x, y) from that equation
	for c in contour:
		(x, y, w, h) = cv2.boundingRect(c)	
		area = 0
		x_sum = 0
		y_sum = 0

		for i in range(x, x+w):
			for j in range(y, y+h):
				area = area + B[j][i]
				x_sum = x_sum + (i * B[j][i])
		A.append(area)
		x_t.append(x_sum)

		for j in range(y, y+h):
			for i in range(x, x+w):
				y_sum = y_sum + (j * B[j][i])
		y_t.append(y_sum)

	print('Area of each object = ', A)

	# Finds the centroid for each object
	for n in range(len(contour)):
		centroid.append([int(round(x_t[n]/A[n])), int(round(y_t[n]/A[n]))])
	print('\ncentroid: ', centroid)
	return centroid

# (4) Create registration table and print with time index, say time = n
def makeTable(centroid):
	regTable = []
	print('\nObject #  |\tID  | \t(x-bar, y-bar)')
	print('------------------------------------------')
	for k in range(len(centroid)):
		regTable.append([k, centroid[k]])
		print('Object ', k, ' |\t', regTable[k][0], ' |\t', regTable[k][1])
	return regTable


frame1 = readImage('frame1.txt')
T1, B1 = promptThreshold(frame1)
centroid1 = findCentroid(B1)
print('\nRegistration Table @ time = n')
regTable = makeTable(centroid1) 
print()

# (5) Read second txt file image and repeat (1)-(4)
frame2 = readImage('frame2.txt')
T2, B2 = promptThreshold(frame2)
centroid2 = findCentroid(B2)
print('\nTemporary Registration Table @ time = n+1')
regTableTemp = makeTable(centroid2)
print()

# (6) Compute distance for each object on image at time n to every object on image at n+1
dist = []
shortIndex = []
for m in range(len(regTable)):
	distTemp = []
	for n in range(len(regTableTemp)):
		x = (centroid1[m][0]-centroid2[n][0])
		y = (centroid1[m][1]-centroid2[n][1])
		distTemp.append([math.sqrt((x ** 2)+(y ** 2)), n])
	distTemp = sorted(distTemp, key=itemgetter(0)) #sort list based on distance
	#print(distTemp)

# (7) Find matching object from image at n to object at n+1 based on shortest distance	
	shortIndex.append([distTemp[distTemp.index(distTemp[0])][1], regTable[m][0]])
	dist.append(distTemp)

if (len(regTable) > len(regTableTemp)):
	smallestTableSize = len(regTableTemp)
else:
	smallestTableSize = len(regTable)

# (8) Update registration table once matching is established and print
centroidNew = []
for n in range(smallestTableSize):
	temp = regTableTemp[n]
	regTableTemp[n] = regTableTemp[shortIndex[n][0]]
	regTableTemp[shortIndex[n][0]] = temp
for n in range(len(regTableTemp)):
	centroidNew.append(regTableTemp[n][1])
print('\nRegistration Table @ time = n+1')
makeTable(centroidNew)


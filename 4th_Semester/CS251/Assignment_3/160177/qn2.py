#!/bin/python3

import numpy as np
from numpy import newaxis
import matplotlib.pyplot as plt
import re

# Getting the file to open
train_file = "train.csv"

inFile = open(train_file, 'r')
line = inFile.readline()

x_list = []
y_list = []

# Step 1

# Getting Lines from the read file and storing values of x and y
for line in inFile:
    x = float(line.split(',')[0])
    y = float(line.split(',')[1].strip())
    x_list.append(x)
    y_list.append(y)

# Generating the corresponding matrices
X_train = np.array(x_list).reshape(len(x_list),1)
Y_train = np.array(y_list).reshape(len(y_list),1)

b = np.ones((len(x_list),1))
new_X_train = np.column_stack((b[:newaxis],X_train[:newaxis]))

# Step 2

w = np.random.random((2,1))

# Step 3

#Plotting y vs x  and  w^T vs [1 x]^T
x_n = new_X_train.T
plt.figure(1)
plt.plot(x_list, y_list, 'ro', X_train.T, w.T.dot(x_n), 'bo')
plt.xlabel('features', fontsize=14, color='green')
plt.ylabel('labels', fontsize=14, color='green')
plt.show(1)

# Step 4

# Finding w_direct and plotting w_direct^T*
w_direct = (np.linalg.inv(new_X_train.T.dot(new_X_train))).dot(new_X_train.T.dot(Y_train))
plt.figure(2)
plt.plot(x_list, y_list, 'ro', X_train.T, w_direct.T.dot(x_n), 'bo')
plt.xlabel('features', fontsize=14, color='green')
plt.ylabel('labels', fontsize=14, color='green')
plt.show(2)

# Step 5 (Training)

N = 2
eta = 1e-8
for i in range(1,N+1):
    for j in range(0,len(x_list)):
        x = x_list[j]
        x_new = np.array([1, x]).reshape(1,2)
        y = y_list[j]
        w = w - eta*(x_new.dot(w)-y)*x_new.T
#        if j%100 == 0 and j != 0:
#            plt.figure(3)
#            plt.plot(X_train.T, w.T.dot(x_n),'bo')

# Step 6 (Final Plot)
plt.figure(3)
plt.plot(x_list, y_list, 'ro')
plt.plot(X_train.T, w.T.dot(x_n), 'bo')
plt.xlabel('features', fontsize=14, color='green')
plt.ylabel('labels', fontsize=14, color='green')
plt.show(3)


# Step 7 (Evaluation)

test_file = "test.csv"

inFile = open(test_file, 'r')
line = inFile.readline()

x_list = []
y_list = []

for line in inFile:
    x = float(line.split(',')[0])
    y = float(line.split(',')[1].strip())
    x_list.append(x)
    y_list.append(y)

X_test = np.array(x_list).reshape(len(x_list),1)
b = np.ones((len(x_list),1))
new_X_test = np.column_stack((b[:newaxis],X_test[:newaxis]))

y_pred1 = new_X_test.dot(w)
y_pred2 = new_X_test.dot(w_direct)

rms1 = 0
rms2 = 0

for i in range(0,len(y_list)):
    rms1 = rms1 + (y_pred1[i][0]-y_list[i])**2
    rms2 = rms2 + (y_pred2[i][0]-y_list[i])**2

rms1 = (rms1/len(y_list))**0.5
rms2 = (rms2/len(y_list))**0.5

print ("RMS from Training: " + str(rms1))
print ("RMS from w_direct: " + str(rms2))

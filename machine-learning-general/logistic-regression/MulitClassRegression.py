import numpy as np
import pandas as pd

# Load data
K = 3
data = pd.read_csv('multiclass.csv')
x = np.insert(np.array(data.iloc[:, 0:1]), 0, 1, axis=1)  # design matrix
y = np.array(data.iloc[:, 1])  # label matrix
w = np.array([*range(K)])  # weights, where k is the number of classes

epochs = 1
alpha = 0.01
m = len(data)

def softmax(xi, wk):
    total =  sum(np.array([np.exp(np.dot(w.T[i], x)) for i in range(K)]))
    return (1/total) * np.exp(np.dot(wk.T, xi))

def gradient(x,y,w,i,k,m):
    g = 0
    for i in range(m):
        g += np.dot(((1 if y[i] == k else 0) - softmax(x[i], w[k])), x[i])
    return -g

for epoch in range(epochs):
    for i in range(m):
        for k in range(K):
            print(gradient(x,y,w,i,k,m))
            #w[k] = w[k] + alpha * gradient(x,y,w,i,k,m)
    

    print(w)
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt



data = pd.read_csv('log_training.csv')

x = np.insert(np.array(data.iloc[0::, 0:15]).reshape(len(data),15), 0, 1, axis=1) # design matrix
y = np.array(data.iloc[0::, 15:16]).reshape(len(data),1) # label matrix
w = np.ones(x.shape[1]).reshape(x.shape[1], 1) # weights


x = np.nan_to_num(x)
y = np.nan_to_num(y)

epochs = 20
alpha = .01

n = 16
m = len(data)

def loss():
    pass

def gradient():
    pass

def sigmoid(z):
    np.clip(z, -500, 500)
    return (1 / (1 + np.exp(-z)))


for epoch in range(epochs):
    for i in range(m):
        index = np.random.randint(m)
        for j in range(len(w)):
            w[j] = w[j]  +  (alpha * (y[index] - sigmoid(np.dot(w.T, x[index])) * x[index][j]))

    

data2 = pd.read_csv('log_testing.csv')
x2 = np.insert(np.array(data2.iloc[0::, 0:15]).reshape(len(data2),15), 0, 1, axis=1) # design matrix
y2 = np.array(data2.iloc[0::, 15:16]).reshape(len(data2),1) # label matrix
x2 = np.nan_to_num(x2)
y2 = np.nan_to_num(y2)


predictions = []

for i in range(m):
    print(sigmoid(np.dot(w.T, x2[i])))
    if sigmoid(np.dot(w.T, x2[i])) > .5:
        predictions.append(1)
    else:
        predictions.append(0)
predictions = np.array(predictions)

print(predictions)
print(np.mean(predictions == y2))



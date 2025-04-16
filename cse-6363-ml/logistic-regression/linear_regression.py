import numpy as np
import pandas as pd
import math
import sys
import os


def get_rsme(X, Y, w, a, n, m):
    """
    Gets the root squared mean error of between the data and the linear regression model.
    Returns the rsme.

    Args:
        X (ndarray): feature vetor
        Y (ndarray): label vector
        w (ndarray): weights
        a (float): learning rate
        n (int): no of features
        m (int): no of samples

    Returns:
        float: root squared mean error
    """
    error = 0
    for i in range(len(data)):
        error += (np.dot(w.T, X[i]) - Y[i])**2
    return np.sqrt(error/m)


def sgd(X, Y, w, a, n, m):
    """
    Performs Stochastic gradient descent using linear regression. Updates weights.
    Args:
        X (ndarray): feature vetor
        Y (ndarray): label vector
        w (ndarray): weights
        a (float): learning rate
        n (int): no of features
        m (int): no of samples
    """

    for _ in range(m):

        # Get a random sample
        random_index = np.random.randint(m) 
        xi = X[random_index]
        yi = Y[random_index]

        # update weights using gradient
        for j in range(n+1):
            w[j] = w[j] - a * ((np.dot(w.T, xi) - yi) * xi[j])

def linear_regression(data):
    """
    data: input data matrix
    return: weights
    """
    n_samples = len(data)  # no of samples
    n_features = 2  # no of features
    epochs = 1 # number of rounds
    alpha = 0.0001 # learning rate

    x = np.array(data[['Math', 'Reading']]) # feature vector
    x = np.insert(x, 0, 1, axis=1)  # adding bias term
    y = np.array(data['Writing']).reshape(-1, 1) # label vector
    w = np.zeros((n_features + 1, 1))  # weight vetor

    #  Perform stochastic gradient descent until convergence
    for epoch in range(epochs):
        sgd(x, y, w, alpha, n_features, n_samples)
    
    # prediction equation with error term
    rsme = get_rsme(x, y, w, alpha, n_features, n_samples)
    print(f"Y_hat_new = {w[0]} + {w[1]} * X_1 + {w[2]} * X_2 + RSME{rsme}")

    return rsme

# do not modify this function
def load_data():
    filename = sys.argv[1]
    feature_matrix = pd.read_csv(filename)
    feature_matrix = feature_matrix.dropna()
    features = sys.argv[2:]
    #print(feature_matrix[features])
    return feature_matrix


if __name__ == "__main__":
    data = load_data()
    RMSE_SCORE = linear_regression(data)
    print("RMSE score is : ", RMSE_SCORE)

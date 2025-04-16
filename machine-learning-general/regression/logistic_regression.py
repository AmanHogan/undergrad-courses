import numpy as np
import pandas as pd
import math
import sys
import os
    

def sigmoid(z, threshold=20):
    return 1 / (1 + np.exp(-np.maximum(z, -threshold)))

def compute_gradient(x, y, w):
    """
    Calcualtes the gradient
    Args:
        x (ndarray): feature vector
        y (ndarray): label vector
        w (ndarray): weights
    Returns: float: gradient
    """

    z = np.dot(x, w)
    h = sigmoid(z)
    gradient = np.dot(x.T, (h - y))

    return gradient

def sgd(x, y, w, learning_rate):
    """
    Performs stochastic gradient descent using logistic regression.
    Args:
        x (ndarray): feature vector
        y (ndarray): label vector
        w (ndarray): weights
        learning_rate (float): alpha value

    """
    for _ in range(y.size):
        rand_ind = np.random.randint(0, y.size)
        xi = x[rand_ind:rand_ind+1]
        yi = y[rand_ind:rand_ind+1]
        gradient = compute_gradient(xi, yi, w)
        w -= learning_rate * gradient

def predict(x, w):
    """
    Returns y_hat values for data set using weights
    Args:
        x (ndarray): feature vector
        w (ndarray): weights

    Returns: ndarray: y_hat values for data set using weights
    """

    z = np.dot(x, w)
    
    return sigmoid(z)

def logistic_regression(xtrain, ytrain, xtest, ytest):
    """
    Performs classic logistic regression with stochastic gradient descent

    Args:
        xtrain (ndarry): x training data
        ytrain (ndarry): y training data
        xtest (ndarry): x test data
        ytest (ndarry): y test data

    Returns:
        float: accuray vaulue; how well the model predicted the test set
    """

    learning_rate =.01 # alpha value
    epochs = 10  # number of epochs
    n_features = xtrain.shape[1] # number of features
    w = np.ones(n_features) # weights vector

    # Perform stochastic gradient descent
    for epoch in range(epochs):
        sgd(xtrain, ytrain, w, learning_rate)
    
    y_pred = predict(xtest, w) # Make predictions on test set
    y_pred_binary = (y_pred >= 0.5).astype(int) # Convert probabilities to binary predictions
    accuracy = np.mean(y_pred_binary == ytest) # Calculate accuracy

    return accuracy

# do not modify this function
def load_data():
    train_filename = sys.argv[1]
    test_filename = sys.argv[2]
    train_feature_matrix = pd.read_csv(train_filename) 
    test_feature_matrix = pd.read_csv(test_filename)
    train_feature_matrix = train_feature_matrix.dropna()
    test_feature_matrix = test_feature_matrix.dropna()
    X_TRAIN = train_feature_matrix.iloc[:, :len(train_feature_matrix.columns)-1] 
    Y_TRAIN = train_feature_matrix.iloc[:, -1]
    X_TEST = test_feature_matrix.iloc[:, :len(test_feature_matrix.columns)-1] 
    Y_TEST = test_feature_matrix.iloc[:, -1]
    return X_TRAIN, Y_TRAIN, X_TEST, Y_TEST


if __name__ == "__main__":
    xtrain, ytrain, xtest, ytest = load_data()
    ACCURACY_SCORE = logistic_regression(xtrain, ytrain, xtest, ytest)
    print("ACCURACY score is : ", ACCURACY_SCORE)

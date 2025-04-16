import numpy as np
import argparse

def sigmoid(z):
    """
    Sigmoid function. Converts hx() value into range [0,1]
    Args:z (float): hx() value
    Returns:float: new hx() value in range [0,1]
    """
    return 1 / (1 + np.exp(-z))

def logistic_regression_newton(X, y, learning_rate=0.001, n_iterations=1000, tol=1e-6):
    """
    Performs logistic regression using newton's method. Returns the class 
    prediction of training data after training the model on the training data

    Args:
        X (ndarray): feature vectors
        y (ndarray): label vector
        learning_rate (float, optional): learning rate. Defaults to 0.001.
        n_iterations (int, optional): number of epochs. Defaults to 1000.
        tol (float, optional): regularization and sigmoid threshold. Defaults to 1e-6.

    Returns:
        ndarray: array of class predictions
    """
    
    n_samples, n_features = X.shape # number of samples and features
    weights = np.zeros(n_features+1).reshape(n_features+1, 1) # weights for lienar-reg equation
    bias = 0 # bias term

    y = y.reshape(n_samples,1) # reshaping label vector
    X = np.insert(X, 0, 1, axis=1) # converts X into a design vector


    for _ in range(n_iterations):
        
        linear_model = np.dot(X, weights) 
        y_predicted = sigmoid(linear_model) 

        print("--------------------------------------------------")
        print(f"Y_hat = {y_predicted.flatten()}")
        print("--------------------------------------------------")

        # Compute gradient
        gradient = (np.dot((y_predicted - y).T, X) / n_samples).reshape(n_features+1,1)
        print(f"gradient = {gradient.flatten()}")
        print("--------------------------------------------------")

        # Compute Hessian matrix
        hessian = np.dot(X.T, X * y_predicted * (1 - y_predicted))
        print("hessian = ")
        print(hessian)
        print("--------------------------------------------------")
        
        # Compute Hessian inverse matrix
        hessian_inv = 0
        try:
            hessian_inv = np.linalg.inv(hessian)

        # If matrix is non invertible, regularize the array
        except np.linalg.LinAlgError:
            reg = tol  
            hessian_inv = np.linalg.inv(hessian + reg * np.eye(hessian.shape[0]))

        print("hessian_inv = ")
        print(hessian_inv)
        print("--------------------------------------------------")

        # Multiply Hesian inverse by the gradient
        hess_mult_gradient = np.dot(hessian_inv, gradient)
        print("hess_mult_gradient = ")
        print(hess_mult_gradient)
        print("--------------------------------------------------")

        # Update the weights
        weights = weights - hess_mult_gradient
        print(f"weights = {weights.flatten()}")
        print("--------------------------------------------------")


    linear_model = np.dot(X, weights) + bias
    y_predicted = sigmoid(linear_model)
    print(f"y_predicted = {y_predicted.flatten()}")
    print("--------------------------------------------------")
    y_predicted_cls = [1 if i > 0.5 else 0 for i in y_predicted]
    return np.array(y_predicted_cls)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Logistic Regression with Newton's Method")
    parser.add_argument("--data", type=str, help="Path to data file (CSV format)")
    args = parser.parse_args()

    if args.data:
        data = np.genfromtxt(args.data, delimiter=',')
        X = data[:, :-1]
        y = data[:, -1]
        print(y)

        predictions = logistic_regression_newton(X, y)
        print("Predictions:", predictions)
    else:
        print("Please provide the path to the data file using the '--data' argument.")

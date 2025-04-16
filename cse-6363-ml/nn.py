
import numpy as np
from tabulate import tabulate

# Neural Network Class
class NeuralNetwork:
    
    def __init__(self, input_size, hidden_size, output_size, activation='relu', learning_rate=0.01, regression=False):
        
        # Initialize network parameters
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.activation = activation
        self.learning_rate = learning_rate
        self.regression = regression

        # Initialize weights and biases
        self.weights_input_hidden = np.random.randn(input_size, hidden_size)
        self.biases_hidden = np.zeros((1, hidden_size))
        self.weights_hidden_output = np.random.randn(hidden_size, output_size)
        self.biases_output = np.zeros((1, output_size))


    # Complete activation functions and their derivatives
    def relu(self, x):
        return np.maximum(0, x)

    def relu_derivative(self, x):
        return (x > 0).astype(float)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return self.sigmoid(x) * (1 - self.sigmoid(x))

    def tanh(self, x):
        return np.tanh(x)

    def tanh_derivative(self, x):
        return 1 - np.tanh(x)**2

    def identity(self, x):
        return x

    def identity_derivative(self, x):
        return np.ones_like(x)

    def leaky_relu(self, x, alpha=0.01):
        return np.where(x > 0, x, x * alpha)

    def leaky_relu_derivative(self, x, alpha=0.01):
        return np.where(x > 0, 1, alpha)

    def softmax(self, x):
        exp_values = np.exp(x - np.max(x, axis=1, keepdims=True))
        return exp_values / np.sum(exp_values, axis=1, keepdims=True)

    # Complete the forward method
    def forward(self, inputs):
        # Forward pass through the network
        self.hidden_layer_inputs = np.dot(inputs, self.weights_input_hidden) + self.biases_hidden

        if self.activation == 'relu':
            self.hidden_layer_outputs = self.relu(self.hidden_layer_inputs)
        elif self.activation == 'sigmoid':
            self.hidden_layer_outputs = self.sigmoid(self.hidden_layer_inputs)
        elif self.activation == 'tanh':
            self.hidden_layer_outputs = self.tanh(self.hidden_layer_inputs)
        elif self.activation == 'leaky_relu':
            self.hidden_layer_outputs = self.leaky_relu(self.hidden_layer_inputs)

        self.output_layer_inputs = np.dot(self.hidden_layer_outputs, self.weights_hidden_output) + self.biases_output
        
        if self.regression:
            self.output_layer_outputs = self.identity(self.output_layer_inputs)
        else:
            self.output_layer_outputs = self.softmax(self.output_layer_inputs)
        return self.output_layer_outputs


    # Complete the backward method
    def backward(self, inputs, targets):

        output_error = self.output_layer_outputs - targets

        if self.regression:
            output_delta = output_error * self.identity_derivative(self.output_layer_inputs)
        else:
            output_delta = output_error

        hidden_error = np.dot(output_delta, self.weights_hidden_output.T)

        if self.activation == 'relu':
            hidden_delta = hidden_error * self.relu_derivative(self.hidden_layer_inputs)
        elif self.activation == 'sigmoid':
            hidden_delta = hidden_error * self.sigmoid_derivative(self.hidden_layer_inputs)
        elif self.activation == 'tanh':
            hidden_delta = hidden_error * self.tanh_derivative(self.hidden_layer_inputs)
        elif self.activation == 'leaky_relu':
            hidden_delta = hidden_error * self.leaky_relu_derivative(self.hidden_layer_inputs)

        # Update weights and biases
        self.weights_hidden_output -= self.learning_rate * np.dot(self.hidden_layer_outputs.T, output_delta)
        self.biases_output -= self.learning_rate * np.sum(output_delta, axis=0, keepdims=True)
        self.weights_input_hidden -= self.learning_rate * np.dot(inputs.T, hidden_delta)
        self.biases_hidden -= self.learning_rate * np.sum(hidden_delta, axis=0, keepdims=True)

    # Complete the train method
    def train(self, inputs, targets, epochs):
        
        for epoch in range(epochs):
            
            # Forward propagation
            predictions = self.forward(inputs)

            # Backward propagation
            self.backward(inputs, targets)

            # Compute loss
            if self.regression:
                loss = np.mean((predictions - targets) ** 2)
            else:
                loss = -np.mean(targets * np.log(predictions + 1e-9))

            if epoch % 10 == 0:
                print(f'Epoch {epoch}, Loss: {loss}')


    # Complete the test method
    def test(self, inputs, targets):
        # Test the network on a separate dataset
        predictions = self.forward(inputs)
        
        if self.regression:
            mse = np.mean((predictions - targets)**2)
            print(f'Mean Squared Error: {mse}')

        else:
            predicted_classes = np.argmax(predictions, axis=1)
            true_classes = np.argmax(targets, axis=1)
            accuracy = np.mean(predicted_classes == true_classes)
            print(f'Test Accuracy: {accuracy * 100}%')

        return  accuracy if  self.regression == False else  mse


# Example usage
input_size = 1
hidden_size = 3
output_size = 1
epochs = 100

# Linear regression data
X_train_regression = np.array([[1], [2], [3], [4], [5]])
y_train_regression = np.array([[2], [4], [6], [8], [10]])

# Classification data for XOR gate
X_train_classification = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y_train_classification = np.array([[1, 0], [0, 1], [0, 1], [1, 0]])

# Test data
X_test_regression = np.array([[6], [7]])
y_test_regression = np.array([[12], [14]])

X_test_classification = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y_test_classification = np.array([[1, 0], [0, 1], [0, 1], [1, 0]])

# Train and test linear regression
# Create and train the neural network with different activation functions
activation_functions = ['relu', 'sigmoid', 'tanh', 'leaky_relu']
learning_rates = [0.01, 0.001, 0.0001]
results = []

for activation in activation_functions:
    print(f'Activation Function: {activation}')
    for lr in learning_rates:
        print(f'Learning Rate: {lr}')
        print("Linear Regression")
        # Instantiate the neural network for regression
        model_regression = NeuralNetwork(input_size=1, hidden_size=3, output_size=1, activation=activation, learning_rate=lr, regression=True)

        # Train the neural network for regression
        model_regression.train(X_train_regression, y_train_regression, epochs)

        # Test the model using model_regression.test()
        mse_regression = model_regression.test(X_test_regression, y_test_regression)

        print("Classification (XOR Gate)")
        # Instantiate the neural network for classification
        model_classification = NeuralNetwork(input_size=2, hidden_size=3, output_size=2, activation=activation, learning_rate=lr, regression=False)

        # Train the neural network for classification
        model_classification.train(X_train_classification, y_train_classification, epochs)

        # Test the model using model_classification.test()
        accuracy_classification = model_classification.test(X_test_classification, y_test_classification)

        # Record the results in a list
        row = [activation, lr, mse_regression, accuracy_classification]
        results.append(row)
        print('\n')

# Tabulate the results
headers = ["Activation Function", "Learning Rate", "Linear Regression (MSE)", "Classification (Accuracy)"]
print(tabulate(results, headers=headers, tablefmt="grid"))
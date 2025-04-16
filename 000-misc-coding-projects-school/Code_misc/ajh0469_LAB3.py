# Aman Hogan-Bailey
# 1001830469
# Version Python 3.8.10
# Ubuntu (20.04.1 LTS Focal Fossa) [CSE 1320 Virtual Machine]

import os


# function finds the location and path of the input file
def find_path(name_of_file, root):
    # for each file from the root find where file is located
    for dirpath, dirname, filename in os.walk(root):

        # if the name matches the file name found, return the path
        if name_of_file in filename:
            return os.path.join(dirpath, name_of_file)


# function reads th file and stores the lines in a string list
def read_file(absolute_path):
    # initializing a string list
    lines = [""]

    # use the path given and read the lines in the file
    with open(absolute_path) as file:
        lines = file.readlines()

    # remove \n from the lines
    lines = [i[:-1] for i in lines]

    return lines


def evaluate(expression_list: object):
    # initializing a  variable that will hold the expressions
    expression = []

    # for each expression in the list, evaluate
    for expression_entry in expression_list:

        # initializing a stack that will evaluate operations using RPN
        stack = []

        # setting expression equal to the parsed entries in the expression list
        expression = (expression_entry.split(" "))

        # for each entry in the expression, use stack to evaluate
        for entry in expression:
            # if entry is an operator, evaluate using last two operands
            if entry == "+":
                stack.append(stack.pop() + stack.pop())
            elif entry == "-":
                x, y = stack.pop(), stack.pop()
                stack.append(y - x)
            elif entry == "/":
                x, y = stack.pop(), stack.pop()
                stack.append(int(y / x))
            elif entry == "*":
                stack.append(stack.pop() * stack.pop())

            # if entry is a number, add to the stack
            else:
                stack.append(int(entry))

        # print the evaluated expression
        print(stack[0])


# initializing the name of the input file
file_name = "input_RPN.txt"

# initializing the root path
start_path = "."

# finding where the input file is located and storing path
full_path = find_path(file_name, start_path)

# reading input file, line-by-line, and storing into string list
file_lines = read_file(full_path)

# evaluating expressions using postfix notation
evaluate(file_lines)

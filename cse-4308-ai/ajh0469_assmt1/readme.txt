Name: Aman Hogan-Bailey
MavId: 1001830469
Date: 2/25/2023

Programming Language: 3.11.2 64 Python
Environement: VsCode and Microsoft CMD command line prompt


STRUCTURE ******************************************************************************************************************************************************************************
The driver code is specified in 'expense_8_puzzle.py'. This python file is responisble for calling the bfs, dfs, ucs, greedy, a*, dls, and dls search
algorithms. Each search algorithm's implementation code is seperated into their own respective python module: 
    a_star.py
    breadth.py
    depth.py
    greedy.py 
    iterative_deep.py
    uniform.py
    depth_limited.py
    depth.py

Additionaly there are original helper modules: 
    eight.py - responsible for the puzzle logic
    nodes.py - nodes.py is resposible for keeping track of all information regrading each node created
    file2puzzle.py - responsible for reading the start.txt and goal.txt and converting them into puzzles

Additional files:
    goal.txt is the example goal file provided by the instrctor
    start.txt is the example start file provided by the instructor
    dfs.txt is a file that will be created by depth.py because of the stdin overflow
    trace_<date>-<time>.txt is a file that logs all dump information fot the algorithms

Program Logic **************************************************************************************************************************************************************************
1) expense_8_puzzle calls file2puzzle and translates the puzzle into a state. 
2) expense_8_puzzle then calls an algorithm implementation and sends in the start and goal states, and command lijne args.
3) the algorithm calls nodes.py and eight.py to handle te puzzle and node logic
4) the algorithm returns the goal state to expense_8_puzzle
5) expense_8_puzzle then calls nodes.py to print out the series of actions that led to the goal state


HOW TO RUN ******************************************************************************************************************************************************************************
There are two ways to run this program:

Windows CMD:
Unzip the downloaded file.
Open your Windows terminal.
Make sure you have python version 3 or higher installed.
Locate the directory the source code where 'expense_8_puzzle' is located: cd C:\Users\ .... \expense_8_puzzle
Then, from the command-line run: 'python expense_8_puzzle.py <start file> <goal file> <method>'
The code should then output the reults

Vscode:
Unzip the downloaded file.
Open the folder in vscode and select 'trust this folder'
Set up your vscode to have a python Environement
    * Hold down SHIFT+CTRL+P and select 'Python:select interpter' and choose the path where python is installed on your system
Find the 'expense_8_puzzle.py' and right click and select 'Run python file in terminal'
    * This will open a terminal in Vscode using a python interpreter.
Now, with the terminal open, enter python expense_8_puzzle.py <start file> <goal file> <method>
The program should then run and print the neccessary outputs


* NOTES ******************************************************************************************************************************************************************************

* dfs() in depth.py generally has a large solution output. For this reason, upon finishing, dfs() will not print to the console, but will print the solution in a file called dfs.txt.

* My implementaion uses a great deal of memmory. This program will not work for dfs() if you run it in IDEs with limited memory allocated to them, for example, PyCharm. It is reccommended
to run from the terminal or from vscode

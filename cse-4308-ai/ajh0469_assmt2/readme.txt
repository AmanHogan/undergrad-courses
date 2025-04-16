Name: Aman Hogan-Bailey
MavId: 1001830469
Date: 3/30/2023

Programming Language: 3.11.2 64 Python
Environement: VsCode and Microsoft CMD command line prompt


STRUCTURE ******************************************************************************************************************************************************************************
The driver code is specified in 'red_blue_nim.py'. This python file is responisble playing a modified version on nim. The game consists of two piles of marbles (red and blue). 
On each players turn they pick a pile and remove one marble from it. If on their turn, either pile is empty then they win. The amount they win is dependent on the number of marbles left 
(2 for every red marble and 3 for every blue marble). Whenever it is the computer's turn, the program runs minimax with alpha-beta pruning. The computer will then choose the most optmial
path via the algorithm.
    There are 8 main functions in 'red_blue_nim.py' that comprise its structure:
        parse_command_line - gets cmd values
        utility - finds value of terminal state
        terminal_test - checks if node is terminal
        successors - gets succesor states
        alpha_beta_decision - performs alpha-beta pruning
        max_value - MAX player
        min_value - MIN player
        start_game - starts the game


Program Logic **************************************************************************************************************************************************************************
1) parse_command_line gets command line values
2) either the computer or human goes first depenging on command line values
    2i) if human goes first, they are prompted to enter red or blue. Program will continue to prompt until
    a valid answer is entered.
    2ii) if the computer goes first, minimax w/ alpha beta pruning will return and return the an optimal desicion.
    This descision will be either 'red' or 'blue'
3) Players will alternate turns until a player chooses the last marble in a pile
4) The score will then be printed to the screen when the game ends

HOW TO RUN ******************************************************************************************************************************************************************************
There are two ways to run this program:

Windows CMD:
Unzip the downloaded file.
Open your Windows terminal.
Make sure you have python version 3 or higher installed.
Locate the directory the source code where 'red_blue_nim.py' is located: cd C:\Users\ .... \red_blue_nim.py
Then, from the command-line run: 'python red_blue_nim.py <red count> <blue count> <string of who goes first('human' or 'computer')>'
The code should then output the reults

Vscode:
Unzip the downloaded file.
Open the folder in vscode and select 'trust this folder'
Set up your vscode to have a python Environement
    * Hold down SHIFT+CTRL+P and select 'Python:select interpter' and choose the path where python is installed on your system
Find the 'red_blue_nim.py' and right click and select 'Run python file in terminal'
    * This will open a terminal in Vscode using a python interpreter.
Now, with the terminal open, enter 'python red_blue_nim.py <red count> <blue count> <string of who goes first('human' or 'computer')>'
The program should then run and print the neccessary outputs


* NOTES ******************************************************************************************************************************************************************************

** If two utilities have the same value, alpha_beta_decision() returns the first utility it found with said value.
** EX: node 1 = 4, node 2 = 4, node 1 will be chosen since that is the first utility it saw.


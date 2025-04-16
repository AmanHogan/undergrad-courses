// Tic-tac-toe (T3) Network Game
// Jason Losh

//-----------------------------------------------------------------------------
// Compile notes for C99 code
//-----------------------------------------------------------------------------

// gcc -o t3 t3.c udp.c

//-----------------------------------------------------------------------------
// Device includes, defines, and assembler directives
//-----------------------------------------------------------------------------

#include <stdlib.h>          // EXIT_ codes
#include <stdbool.h>         // bool
#include <stdio.h>           // printf, scanf
#include <string.h>          // strlen, strcmp

#include "udp.h"

#define CLIENT_PORT 4096
#define SERVER_PORT 4097

void clearBoard(char board[3][3])
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '.';
}

// TODO: Add code to display the game board
void showBoard(char board[3][3])
{
}

// TODO: Add code to determine if a winner (xo) has occurred
bool isWinner(char board[3][3], char xo)
{
    bool win;
    return win;
}

// TODO: Add code to test if an x or o (xo) is a valid move
//       and then record in the game board
bool addMove(char board[3][3], char move[], char xo)
{
    bool ok = strlen(move) == 2;
    // ...
    return ok;
}

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char *remoteIp;
    char *role;
    char str[100], str2[100];
    char board[3][3];
    bool validMove;
    bool winner = false;
    int moveCount = 0;

    bool myTurn;
    char myLetter, opponentLetter;
    int remotePort;

    // TODO: Verify arguments are valie
     bool goodArguments;
    // ...
    if (!goodArguments)
    {
        printf("usage: t3 IPV4_ADDRESS ROLE\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        printf("  ROLE is either invite or accept\n");
        exit(EXIT_FAILURE);
    }

    // TODO: Determine if client or server
    // A server will wait to accept an invitation to play
    // A client will send an invitation to play
    // bool client = _____;

    // TODO: Open listener port number dependent on client/server role

    // TODO: Determine remote port that you will send data to
    //       If you are server, send to client port, and vice versa

    // Setup game
    clearBoard(board);

    // TODO: Determine whether it is your turn or not
    // myTurn = ______;

    // TODO: Determine your letter (x or o) and your opponent's letter

    // TODO: Add code to send an invite or wait to accept an invite

    // Start game loop, alternating turns
    while(!winner && moveCount != 9)
    {
        // get my move
        if (myTurn)
        {
            // TODO: add code your move here to get the move, validate move,
            //       show board, send move to remote port, and check for a winner
        }
        // get opponent's move
        else
        {
            // TODO: add code to receive your opponent's move, validate move,
            //       show board, and check for a winner
        }

        // Increment move count, alternate turns
        moveCount++;
        myTurn = !myTurn;
    }
    if (!winner)
        printf("The game was a draw\n");


    // TO DO: Close listener port
    return EXIT_SUCCESS;
}

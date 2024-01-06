#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "../include/gameInitializer.h"
#include "../include/printer.h"
#include "../include/getter.h"
#include "../include/gamePlay.h"
#include "../include/constants.h"

void handleUserGuessAndUpdateCounters(char userGuess[3], bool **board, bool **boardToCheckUserHit, int *hitCounterPtr, int *guessCounterPtr)
{
    (*guessCounterPtr)++;

    int x_coordinate = userGuess[0] - 'A';
    int y_coordinate = userGuess[1] - '0' - 1;

    if (boardToCheckUserHit[x_coordinate][y_coordinate])
    {
        printf("You've tried shooting this block la!\n");
    }
    else if (board[x_coordinate][y_coordinate] == false)
    {
        printf("You hit a ship!\n");
        (*hitCounterPtr)++;
    }
    else
    {
        printf("You missed. :(\n");
    }

    boardToCheckUserHit[x_coordinate][y_coordinate] = true;
}

void playAMatch(int *guessCounterPtr)
{
    bool **board = initializeBoard(BOARD_SIZE);
    bool **boardToCheckUserHit = initializeUserHitCheckerBoard(BOARD_SIZE);
    createAndSetShips(board, BOARD_SIZE);

    int hitCounter = 0;
    char userGuess[3];

    do
    {
        getGuess(userGuess);
        handleUserGuessAndUpdateCounters(userGuess, board, boardToCheckUserHit, &hitCounter, guessCounterPtr);

        sleep(1);
        printf("\e[1;1H\e[2J"); // 'clear' screen

        printBoard(board, boardToCheckUserHit);
    } while (hitCounter != NUMBER_OF_SHIPS * SHIP_SEGMENTS);
}

void handleHighscore(bool *isFirstTimePlayingPtr, int highscore, int guessCounter)
{
    if (!(*isFirstTimePlayingPtr))
    {
        if (highscore > guessCounter)
        {
            highscore = guessCounter;
            printHighscore(highscore, true);
        }
        else
        {
            printHighscore(highscore, false);
        }
    }
    else
    {
        highscore = guessCounter;
        printHighscore(highscore, false);
        (*isFirstTimePlayingPtr) = false;
    }
}

void gamePlay()
{
    int guessCounter;
    int highscore;
    bool isFirstTimePlaying = true;

    do
    {
        printIntro();
        guessCounter = 0;
        playAMatch(&guessCounter);
        printGameResult(guessCounter);
        handleHighscore(&isFirstTimePlaying, highscore, guessCounter);
    } while (getUserReplayChoice() != 'q');
}
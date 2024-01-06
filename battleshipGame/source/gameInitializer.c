#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../include/gameInitializer.h"
#include "../include/constants.h"

bool **initializeBoard(int size)
{
    bool **board = (bool **)malloc(size * sizeof(bool *));

    if (board == NULL)
    {
        // Memory allocation failed
        return NULL;
    }

    for (int i = 0; i < size; ++i)
    {
        board[i] = (bool *)malloc(size * sizeof(bool));

        if (board[i] == NULL)
        {
            // Memory allocation failed, clean up previously allocated memory
            for (int j = 0; j < i; ++j)
            {
                free(board[j]);
            }
            free(board);
            return NULL;
        }

        // Initialize the elements of the row
        for (int j = 0; j < size; ++j)
        {
            board[i][j] = true;
        }
    }

    return board;
}

bool **initializeUserHitCheckerBoard(int size)
{
    bool **userHitBoard = (bool **)malloc(size * sizeof(bool *));

    if (userHitBoard == NULL)
    {
        // Memory allocation failed
        return NULL;
    }

    for (int i = 0; i < size; ++i)
    {
        userHitBoard[i] = (bool *)malloc(size * sizeof(bool));

        if (userHitBoard[i] == NULL)
        {
            // Memory allocation failed, clean up previously allocated memory
            for (int j = 0; j < i; ++j)
            {
                free(userHitBoard[j]);
            }
            free(userHitBoard);
            return NULL;
        }

        // Initialize the elements of the row
        for (int j = 0; j < size; ++j)
        {
            userHitBoard[i][j] = false;
        }
    }

    return userHitBoard;
}

void setShipPosition(int XPos, int YPos, int excludedDirection, int shipPosition[SHIP_SEGMENTS][COORDINATES_PER_POSITION])
{
    switch (excludedDirection)
    {
    case 0: // excludes west direction from ship position vector
    {
        shipPosition[0][X_COORDINATE] = XPos;
        shipPosition[0][Y_COORDINATE] = YPos - 1;
        shipPosition[1][X_COORDINATE] = XPos;
        shipPosition[1][Y_COORDINATE] = YPos;
        shipPosition[2][X_COORDINATE] = XPos;
        shipPosition[2][Y_COORDINATE] = YPos + 1;
        shipPosition[3][X_COORDINATE] = XPos + 1;
        shipPosition[3][Y_COORDINATE] = YPos;
        break;
    }
    case 1: // excludes east direction from ship position vector
    {
        shipPosition[0][X_COORDINATE] = XPos;
        shipPosition[0][Y_COORDINATE] = YPos - 1;
        shipPosition[1][X_COORDINATE] = XPos;
        shipPosition[1][Y_COORDINATE] = YPos;
        shipPosition[2][X_COORDINATE] = XPos;
        shipPosition[2][Y_COORDINATE] = YPos + 1;
        shipPosition[3][X_COORDINATE] = XPos - 1;
        shipPosition[3][Y_COORDINATE] = YPos;
        break;
    }
    case 2: // excludes south direction from ship position vector
    {
        shipPosition[0][X_COORDINATE] = XPos - 1;
        shipPosition[0][Y_COORDINATE] = YPos;
        shipPosition[1][X_COORDINATE] = XPos;
        shipPosition[1][Y_COORDINATE] = YPos;
        shipPosition[2][X_COORDINATE] = XPos + 1;
        shipPosition[2][Y_COORDINATE] = YPos;
        shipPosition[3][X_COORDINATE] = XPos;
        shipPosition[3][Y_COORDINATE] = YPos - 1;
        break;
    }
    case 3: // excludes north direction from ship position vector
    {
        shipPosition[0][X_COORDINATE] = XPos - 1;
        shipPosition[0][Y_COORDINATE] = YPos;
        shipPosition[1][X_COORDINATE] = XPos;
        shipPosition[1][Y_COORDINATE] = YPos;
        shipPosition[2][X_COORDINATE] = XPos + 1;
        shipPosition[2][Y_COORDINATE] = YPos;
        shipPosition[3][X_COORDINATE] = XPos;
        shipPosition[3][Y_COORDINATE] = YPos + 1;
        break;
    }
    }
}

bool isShipPositionValid(int shipPosition[SHIP_SEGMENTS][COORDINATES_PER_POSITION], bool **board, int size)
{
    for (int index = 0; index < NUMBER_OF_SHIPS; index++)
    {
        // Check if the shipPosition coordinates are out of bounds
        if (shipPosition[index][X_COORDINATE] < 0 || shipPosition[index][X_COORDINATE] > size - 1 ||
            shipPosition[index][Y_COORDINATE] < 0 || shipPosition[index][Y_COORDINATE] > size - 1)
        {
            return false;
        }

        // Check if the position on the board is already taken
        if (!board[shipPosition[index][X_COORDINATE]][shipPosition[index][Y_COORDINATE]])
            return false;
    }
    return true;
}

void createAndSetShips(bool **board, int size)
{
    srand(time(NULL));
    int shipPosition[SHIP_SEGMENTS][COORDINATES_PER_POSITION];
    for (int index = 0; index < NUMBER_OF_SHIPS; index++)
    {
        int xPosition, yPosition, excludedDirection;
        do
        {
            xPosition = rand() % size;
            yPosition = rand() % size;
            excludedDirection = rand() % DIRECTIONS;
            setShipPosition(xPosition, yPosition, excludedDirection, shipPosition);
        } while (!isShipPositionValid(shipPosition, board, BOARD_SIZE));

        for (int innerIndex = 0; innerIndex < NUMBER_OF_SHIPS; innerIndex++)
        {
            board[shipPosition[innerIndex][X_COORDINATE]][shipPosition[innerIndex][Y_COORDINATE]] = false;
        }
    }
}
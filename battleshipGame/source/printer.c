#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/printer.h"
#include "../include/constants.h"

void printIntro()
{
    FILE *gameNameFile = fopen("resources/name.txt", "r");
    if (!gameNameFile)
    {
        perror("Failed to open name.txt");
        exit(1);
    }
    char character;
    character = fgetc(gameNameFile);
    while (character != EOF)
    {
        printf("%c", character);
        character = fgetc(gameNameFile);
    }
    fclose(gameNameFile);
    printf("\n");
    FILE *gameDrawingFile = fopen("resources/drawing.txt", "r");
    if (!gameDrawingFile)
    {
        perror("Failed to open drawing.txt");
        exit(1);
    }
    character = fgetc(gameDrawingFile);
    while (character != EOF)
    {
        printf("%c", character);
        character = fgetc(gameDrawingFile);
    }
    fclose(gameDrawingFile);

    printf("\n\n");
    printf("Eliminate all the ships to win!\n");
    sleep(1);
    /*
        In the game Battleship, a fleet of ships is hidden in a n x n grid.
        The fleet consists of a number of 4-square battleships.
        Each row of the grid is denoted by an integer number (e.g 1, 2, 3).
        Each column is denoted by one uppercase letter in the alphabet (e.g 'A', 'B', 'C').
        By locating the squares where the battleships are, you can shoot them down and win the game!
        The ships are shaped like the following shape rotated in any directions:
                0
            0   0   0
    */
    printf("In this game of Battleship, a fleet of ships is hidden in a 8 x 8 grid.\nThe fleet consists of 4 battleships. \nEach column of the grid is denoted by an integer number (e.g 1, 2, 3). \nEach row is by one uppercase letter in the alphabet(e.g 'A', 'B', 'C').\nBy locating the squares where the battleships are (e.g. enter 'A1'), you can shoot them down and win the game!\n");
    printf("\nThe ships are shaped like the following shape rotated in any directions:\n");
    printf("\t\t0\n");
    printf("\t0\t0\t0\n");
}
void printBoard(bool **board, bool **boardToCheckUserHit)
{
    char rowChar[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    printf("Your current board: \n");
    for (int index = 0; index < BOARD_SIZE; index++)
    {
        printf("\t");
        printf("%d", index + 1);
    }
    printf("\n");
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (col == 0)
                printf("%c", rowChar[row]);
            printf("\t");
            if (boardToCheckUserHit[row][col])
            {
                if (board[row][col])
                    printf("X");
                else
                    printf("O");
            }
            else
                printf("-");
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------\n");
}
void printGameResult(int guessCounter)
{
    if (guessCounter > 55)
    {
        printf("You're so bad haha! Might wanna consider playing another game than this one lol.\n");
    }
    else if (guessCounter > 45)
    {
        printf("%d guesses huh? That's pretty average.\n", guessCounter);
    }
    else if (guessCounter > 30)
    {
        printf("%d guesses! You're kinda good yooooo\n", guessCounter);
    }
    else
    {
        printf("%d guesses!!!!! OMG YOU SHOULD GO PRO! YOU'RE PHENOMENAL!\n", guessCounter);
    }
    printf("--------------------------------\n");
}
void printHighscore(int highscore, bool isNewHighscore)
{
    if (isNewHighscore)
        printf("OMG NEW HIGHSCORE! YOU'RE THE GOAT!!!\n");
    printf("Your current high score is: %d\n", highscore);
}
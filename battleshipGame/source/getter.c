#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "../include/getter.h"

bool isValidGuess(char userInput[100])
{
    if (strlen(userInput) > 2)
    {
        printf("Input too long.\n");
        return false;
    }
    if (strlen(userInput) < 2)
    {
        printf("Input too short.\n");
        return false;
    }
    if ((userInput[0] < 'a' || userInput[0] > 'h') && (userInput[0] < 'A' || userInput[0] > 'H'))
    {
        printf("Invalid input.\n");
        return false;
    }
    if (userInput[1] < '1' || userInput[1] > '8')
    {
        printf("Invalid input.\n");
        return false;
    }
    return true;
}
void getGuess(char userGuess[3])
{
    char userInput[100];
    do
    {
        printf("Make a guess!\n");
        scanf("%99s", userInput);
    } while (!isValidGuess(userInput));
    (userInput[0] >= 'a' && userInput[0] <= 'h') ? (userGuess[0] = userInput[0] - 32) : (userGuess[0] = userInput[0]);
    userGuess[1] = userInput[1];
    userGuess[2] = '\0';
}
bool isVaLidReplayChoice(char userReplayChoice[100])
{
    if (strlen(userReplayChoice) > 1)
        return false;
    if (userReplayChoice[0] != 'Q' && userReplayChoice[0] != 'q' && userReplayChoice[0] != 'R' && userReplayChoice[0] != 'r')
        return false;
    return true;
}
char getUserReplayChoice()
{
    char userReplayChoice[100];
    printf("Ehe do you wanna play again? ;)\n");
    printf("Type r to replay and q to end the game.\n");
    scanf("%99s", userReplayChoice);
    while (!isVaLidReplayChoice(userReplayChoice))
    {
        printf("Invalid input. Please try again T.T\n");
        scanf("%99s", userReplayChoice);
    }
    char result = userReplayChoice[0] > 97 ? userReplayChoice[0] : userReplayChoice[0] + 32;
    sleep(2);
    printf("\e[1;1H\e[2J");
    return result;
}
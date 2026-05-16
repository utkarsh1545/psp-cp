#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tic_tac_toe.h"

#define LEADERBOARD_FILE "leaderboard.txt"

typedef struct
{
    int pvpPlayer1Wins;
    int pvpPlayer2Wins;
    int pvpDraws;
    int pvcPlayerWins;
    int pvcComputerWins;
    int pvcDraws;
} Leaderboard;

void startTicTacToe(void);

static void initializeBoard(char board[3][3]);
static void printBoard(char board[3][3]);
static int getNumberInput(void);
static int getMenuChoice(void);
static int getReplayChoice(void);
static int placeMove(char board[3][3], int position, char symbol);
static int isPositionAvailable(char board[3][3], int position);
static char checkWinner(char board[3][3]);
static int isBoardFull(char board[3][3]);
static int playHumanVsHuman(Leaderboard *leaderboard);
static int playHumanVsComputer(Leaderboard *leaderboard);
static int getRandomComputerMove(char board[3][3]);
static void loadLeaderboard(Leaderboard *leaderboard);
static void saveLeaderboard(Leaderboard *leaderboard);
static void showLeaderboard(Leaderboard *leaderboard);
static void resetLeaderboard(Leaderboard *leaderboard);
static void clearInputBuffer(void);

void startTicTacToe(void)
{
    Leaderboard leaderboard;
    int menuChoice;
    int shouldExit;

    srand((unsigned int)time(NULL));
    loadLeaderboard(&leaderboard);

    shouldExit = 0;

    while (!shouldExit)
    {
        printf("\n===== TIC TAC TOE =====\n");
        printf("1. Human vs Human\n");
        printf("2. Human vs Computer\n");
        printf("3. Show Leaderboard\n");
        printf("0. Exit to Dashboard\n");
        printf("Enter your choice: ");

        menuChoice = getMenuChoice();

        if (menuChoice == 1)
        {
            shouldExit = playHumanVsHuman(&leaderboard);
        }
        else if (menuChoice == 2)
        {
            shouldExit = playHumanVsComputer(&leaderboard);
        }
        else if (menuChoice == 3)
        {
            showLeaderboard(&leaderboard);
        }
        else if (menuChoice == 0)
        {
            shouldExit = 1;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }

    printf("Returning to dashboard...\n");
}

static void initializeBoard(char board[3][3])
{
    int row;
    int column;
    char value;

    value = '1';

    for (row = 0; row < 3; row++)
    {
        for (column = 0; column < 3; column++)
        {
            board[row][column] = value;
            value++;
        }
    }
}

static void printBoard(char board[3][3])
{
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

static int getNumberInput(void)
{
    int value;
    int result;

    result = scanf("%d", &value);

    if (result != 1)
    {
        clearInputBuffer();
        return -1;
    }

    clearInputBuffer();
    return value;
}

static int getMenuChoice(void)
{
    return getNumberInput();
}

static int getReplayChoice(void)
{
    return getNumberInput();
}

static int placeMove(char board[3][3], int position, char symbol)
{
    int row;
    int column;

    if (!isPositionAvailable(board, position))
    {
        return 0;
    }

    row = (position - 1) / 3;
    column = (position - 1) % 3;
    board[row][column] = symbol;
    return 1;
}

static int isPositionAvailable(char board[3][3], int position)
{
    int row;
    int column;
    char expectedValue;

    if (position < 1 || position > 9)
    {
        return 0;
    }

    row = (position - 1) / 3;
    column = (position - 1) % 3;
    expectedValue = (char)('0' + position);

    if (board[row][column] == expectedValue)
    {
        return 1;
    }

    return 0;
}

static char checkWinner(char board[3][3])
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    return 'N';
}

static int isBoardFull(char board[3][3])
{
    int row;
    int column;

    for (row = 0; row < 3; row++)
    {
        for (column = 0; column < 3; column++)
        {
            if (board[row][column] >= '1' && board[row][column] <= '9')
            {
                return 0;
            }
        }
    }

    return 1;
}

static int playHumanVsHuman(Leaderboard *leaderboard)
{
    char board[3][3];
    char currentPlayer;
    char winner;
    int move;
    int replayChoice;
    int gameFinished;

    replayChoice = 1;

    while (replayChoice == 1)
    {
        initializeBoard(board);
        currentPlayer = 'X';
        gameFinished = 0;

        while (!gameFinished)
        {
            printBoard(board);
            printf("Player %c, enter a position (1-9) or 0 to exit: ", currentPlayer);

            move = getNumberInput();

            if (move == 0)
            {
                return 1;
            }

            if (move < 1 || move > 9)
            {
                printf("Invalid input. Enter a number from 1 to 9.\n");
                continue;
            }

            if (!placeMove(board, move, currentPlayer))
            {
                printf("That position is already taken. Try again.\n");
                continue;
            }

            winner = checkWinner(board);

            if (winner == 'X')
            {
                printBoard(board);
                printf("Player 1 wins!\n");
                leaderboard->pvpPlayer1Wins++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
            }
            else if (winner == 'O')
            {
                printBoard(board);
                printf("Player 2 wins!\n");
                leaderboard->pvpPlayer2Wins++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
            }
            else if (isBoardFull(board))
            {
                printBoard(board);
                printf("The match is a draw.\n");
                leaderboard->pvpDraws++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
            }
            else
            {
                if (currentPlayer == 'X')
                {
                    currentPlayer = 'O';
                }
                else
                {
                    currentPlayer = 'X';
                }
            }
        }

        printf("1. Play again\n");
        printf("2. Return to Tic-Tac-Toe menu\n");
        printf("0. Exit to Dashboard\n");
        printf("Enter your choice: ");

        replayChoice = getReplayChoice();

        while (replayChoice != 1 && replayChoice != 2 && replayChoice != 0)
        {
            printf("Invalid choice. Enter 1, 2, or 0: ");
            replayChoice = getReplayChoice();
        }

        if (replayChoice == 2)
        {
            return 0;
        }

        if (replayChoice == 0)
        {
            return 1;
        }
    }

    return 0;
}

static int playHumanVsComputer(Leaderboard *leaderboard)
{
    char board[3][3];
    char winner;
    int move;
    int computerMove;
    int replayChoice;
    int gameFinished;

    replayChoice = 1;

    while (replayChoice == 1)
    {
        initializeBoard(board);
        gameFinished = 0;

        while (!gameFinished)
        {
            printBoard(board);
            printf("Player X, enter a position (1-9) or 0 to exit: ");

            move = getNumberInput();

            if (move == 0)
            {
                return 1;
            }

            if (move < 1 || move > 9)
            {
                printf("Invalid input. Enter a number from 1 to 9.\n");
                continue;
            }

            if (!placeMove(board, move, 'X'))
            {
                printf("That position is already taken. Try again.\n");
                continue;
            }

            winner = checkWinner(board);

            if (winner == 'X')
            {
                printBoard(board);
                printf("You win!\n");
                leaderboard->pvcPlayerWins++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
                continue;
            }

            if (isBoardFull(board))
            {
                printBoard(board);
                printf("The match is a draw.\n");
                leaderboard->pvcDraws++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
                continue;
            }

            computerMove = getRandomComputerMove(board);
            placeMove(board, computerMove, 'O');
            printf("Computer chose position %d.\n", computerMove);

            winner = checkWinner(board);

            if (winner == 'O')
            {
                printBoard(board);
                printf("Computer wins!\n");
                leaderboard->pvcComputerWins++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
            }
            else if (isBoardFull(board))
            {
                printBoard(board);
                printf("The match is a draw.\n");
                leaderboard->pvcDraws++;
                saveLeaderboard(leaderboard);
                gameFinished = 1;
            }
        }

        printf("1. Play again\n");
        printf("2. Return to Tic-Tac-Toe menu\n");
        printf("0. Exit to Dashboard\n");
        printf("Enter your choice: ");

        replayChoice = getReplayChoice();

        while (replayChoice != 1 && replayChoice != 2 && replayChoice != 0)
        {
            printf("Invalid choice. Enter 1, 2, or 0: ");
            replayChoice = getReplayChoice();
        }

        if (replayChoice == 2)
        {
            return 0;
        }

        if (replayChoice == 0)
        {
            return 1;
        }
    }

    return 0;
}

static int getRandomComputerMove(char board[3][3])
{
    int move;

    move = (rand() % 9) + 1;

    while (!isPositionAvailable(board, move))
    {
        move = (rand() % 9) + 1;
    }

    return move;
}

static void loadLeaderboard(Leaderboard *leaderboard)
{
    FILE *file;
    int itemsRead;

    resetLeaderboard(leaderboard);

    file = fopen(LEADERBOARD_FILE, "r");

    if (file == NULL)
    {
        printf("Leaderboard file not found. Starting with zero stats.\n");
        return;
    }

    itemsRead = fscanf(
        file,
        "%d %d %d %d %d %d",
        &leaderboard->pvpPlayer1Wins,
        &leaderboard->pvpPlayer2Wins,
        &leaderboard->pvpDraws,
        &leaderboard->pvcPlayerWins,
        &leaderboard->pvcComputerWins,
        &leaderboard->pvcDraws
    );

    fclose(file);

    if (itemsRead != 6)
    {
        printf("Leaderboard file was invalid. Stats have been reset to zero.\n");
        resetLeaderboard(leaderboard);
    }
}

static void saveLeaderboard(Leaderboard *leaderboard)
{
    FILE *file;

    file = fopen(LEADERBOARD_FILE, "w");

    if (file == NULL)
    {
        printf("Error: could not save leaderboard.\n");
        return;
    }

    fprintf(
        file,
        "%d %d %d %d %d %d\n",
        leaderboard->pvpPlayer1Wins,
        leaderboard->pvpPlayer2Wins,
        leaderboard->pvpDraws,
        leaderboard->pvcPlayerWins,
        leaderboard->pvcComputerWins,
        leaderboard->pvcDraws
    );

    fclose(file);
}

static void showLeaderboard(Leaderboard *leaderboard)
{
    printf("\n===== LEADERBOARD =====\n");
    printf("Human vs Human\n");
    printf("Player 1 wins: %d\n", leaderboard->pvpPlayer1Wins);
    printf("Player 2 wins: %d\n", leaderboard->pvpPlayer2Wins);
    printf("Draws: %d\n", leaderboard->pvpDraws);

    printf("\nHuman vs Computer\n");
    printf("Player wins: %d\n", leaderboard->pvcPlayerWins);
    printf("Computer wins: %d\n", leaderboard->pvcComputerWins);
    printf("Draws: %d\n", leaderboard->pvcDraws);
}

static void resetLeaderboard(Leaderboard *leaderboard)
{
    leaderboard->pvpPlayer1Wins = 0;
    leaderboard->pvpPlayer2Wins = 0;
    leaderboard->pvpDraws = 0;
    leaderboard->pvcPlayerWins = 0;
    leaderboard->pvcComputerWins = 0;
    leaderboard->pvcDraws = 0;
}

static void clearInputBuffer(void)
{
    int ch;

    ch = getchar();

    while (ch != '\n' && ch != EOF)
    {
        ch = getchar();
    }
}

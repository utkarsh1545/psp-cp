# Tic-Tac-Toe Course Project

This project is a simple tic-tac-toe game written in C.

It is designed for:
- beginners
- easy explanation in a class project or viva
- simple compilation in modern compilers like GCC
- easier compatibility with older compilers like Turbo C later

The program is modular, readable, and uses only basic C concepts such as:
- arrays
- loops
- `if` / `else`
- functions
- file input and output
- random number generation

## Features

The game currently supports:

- Human vs Human mode
- Human vs Computer mode
- simple random computer moves
- input validation
- leaderboard
- file saving and loading for leaderboard data
- separate draw counts for both game modes
- replay in the same mode
- universal exit using `0`

## Project Files

- [main.c](D:\projects\psp-cp\main.c)
  This is the current entry point of the standalone program.

- [tic_tac_toe.h](D:\projects\psp-cp\tic_tac_toe.h)
  This contains the function declaration for starting the game module.

- [tic_tac_toe.c](D:\projects\psp-cp\tic_tac_toe.c)
  This contains the full tic-tac-toe logic.

- `leaderboard.txt`
  This file is created automatically when match results are saved.

## How the Game Works

The tic-tac-toe board is stored in:

```c
char board[3][3];
```

At the beginning, the board stores characters from `'1'` to `'9'`:

```text
1 2 3
4 5 6
7 8 9
```

This makes the logic easier because:

- the same board is used for display
- the player enters numbers from `1` to `9`
- if a board position still contains its original number, that position is empty
- if it contains `X` or `O`, that position is already used

Player symbols:

- Player 1 is always `X`
- Player 2 is always `O`
- Computer is always `O`

## Menu Structure

The program shows this menu:

```text
1. Human vs Human
2. Human vs Computer
3. Show Leaderboard
0. Exit to Dashboard
```

## Universal Exit

The game supports a universal exit rule:

- entering `0` during a match immediately exits the game
- the unfinished match is not saved
- no confirmation is shown
- control returns back to the caller

This is useful for future dashboard integration.

## Replay Behavior

After a completed match, the program asks:

```text
1. Play again
2. Return to Tic-Tac-Toe menu
0. Exit to Dashboard
```

## Leaderboard

The leaderboard stores these totals:

- Human vs Human:
  - Player 1 wins
  - Player 2 wins
  - Draws

- Human vs Computer:
  - Player wins
  - Computer wins
  - Draws

The game automatically:

- loads previous stats at program start
- creates new stats from zero if the file is missing
- resets stats to zero if the file contains invalid data
- saves the file after every completed match

## Leaderboard File Format

The file is a very simple text file with 6 integers:

```text
pvpPlayer1Wins pvpPlayer2Wins pvpDraws pvcPlayerWins pvcComputerWins pvcDraws
```

Example:

```text
3 1 2 4 5 1
```

This means:

- Player 1 wins in Human vs Human = `3`
- Player 2 wins in Human vs Human = `1`
- Draws in Human vs Human = `2`
- Player wins in Human vs Computer = `4`
- Computer wins in Human vs Computer = `5`
- Draws in Human vs Computer = `1`

This format was chosen because it is:

- easy to explain
- easy to read with `fscanf`
- easy to write with `fprintf`
- simple enough for a beginner project

## How to Compile and Run

Open a terminal in:

`D:\projects\psp-cp`

### Compile with GCC

```powershell
gcc main.c tic_tac_toe.c -o tictactoe.exe
```

### Run the Program

```powershell
.\tictactoe.exe
```

### Recommended Development Compile Command

This version enables extra warnings and uses an older C style standard:

```powershell
gcc -Wall -Wextra -std=c89 -pedantic main.c tic_tac_toe.c -o tictactoe.exe
```

Then run:

```powershell
.\tictactoe.exe
```

## How to Use the Game

### Human vs Human

1. Choose option `1`
2. Player `X` enters a position from `1` to `9`
3. Player `O` enters a position from `1` to `9`
4. Continue until someone wins or the match is a draw

### Human vs Computer

1. Choose option `2`
2. Player `X` enters a position from `1` to `9`
3. Computer picks a random empty position
4. Continue until someone wins or the match is a draw

### Show Leaderboard

1. Choose option `3`
2. The program shows the saved totals for both game modes

### Exit to Dashboard

1. Enter `0` from the main menu
2. Or enter `0` during a match
3. The game exits immediately

## Input Rules

- enter `1` to `9` for board moves
- enter `0` to exit back to the caller or dashboard
- if the input is invalid, the program asks again
- if the chosen position is already used, the program asks again

## Beginner-Friendly Design Choices

This project intentionally avoids complicated techniques.

It does not use:

- dynamic memory
- complex pointers
- advanced data structures
- graphics
- non-standard libraries for game logic

This makes it easier to:

- understand
- explain to a teacher
- debug
- integrate later

## Main Functions in the Project

Some important functions are:

- `startTicTacToe()`
  Starts the full tic-tac-toe module.

- `initializeBoard()`
  Fills the board with characters `'1'` to `'9'`.

- `printBoard()`
  Displays the board using simple `printf`.

- `placeMove()`
  Places `X` or `O` on the selected position if valid.

- `isPositionAvailable()`
  Checks whether a chosen position is still empty.

- `checkWinner()`
  Checks rows, columns, and diagonals for a winner.

- `isBoardFull()`
  Checks whether all positions are filled.

- `playHumanVsHuman()`
  Runs the Human vs Human game mode.

- `playHumanVsComputer()`
  Runs the Human vs Computer game mode.

- `getRandomComputerMove()`
  Selects a random empty box for the computer.

- `loadLeaderboard()`
  Loads saved stats from file.

- `saveLeaderboard()`
  Saves stats to file.

- `showLeaderboard()`
  Prints the leaderboard.

## How to Integrate This Game Into a Main Dashboard Program

This section is for the teammate who will combine multiple games into one dashboard.

### Current Design

Right now, the standalone project has:

- `main.c`
- `tic_tac_toe.c`
- `tic_tac_toe.h`

The important part for integration is:

```c
void startTicTacToe(void);
```

This function already behaves like a game module entry point.

### Integration Idea

In the final shared project, the dashboard should control the top-level menu.

Example dashboard menu:

```text
1. Tic-Tac-Toe
2. Game 2
3. Game 3
0. Exit
```

When the user selects Tic-Tac-Toe, the dashboard should call:

```c
startTicTacToe();
```

When the user exits tic-tac-toe using `0`, the tic-tac-toe module returns to the dashboard.

### What the Integrating Teammate Should Do

#### 1. Keep `tic_tac_toe.c` and `tic_tac_toe.h`

These files should be copied into the final combined project.

#### 2. Do not use this project `main.c` directly in the final dashboard

The current [main.c](D:\projects\psp-cp\main.c) is only for running tic-tac-toe as a standalone program.

In the final combined project, the dashboard project should have its own `main.c`.

#### 3. Include the header in the dashboard file

Example:

```c
#include "tic_tac_toe.h"
```

#### 4. Call the function from the dashboard menu

Example:

```c
if (choice == 1)
{
    startTicTacToe();
}
```

### Example Dashboard `main.c`

This is a simple example of how another teammate can integrate the game:

```c
#include <stdio.h>
#include "tic_tac_toe.h"

int main(void)
{
    int choice;

    while (1)
    {
        printf("\n===== GAME DASHBOARD =====\n");
        printf("1. Tic-Tac-Toe\n");
        printf("2. Game 2\n");
        printf("3. Game 3\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            startTicTacToe();
        }
        else if (choice == 2)
        {
            printf("Game 2 not added yet.\n");
        }
        else if (choice == 3)
        {
            printf("Game 3 not added yet.\n");
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
```

### How to Compile After Integration

Suppose the final project contains:

- dashboard `main.c`
- `tic_tac_toe.c`
- `tic_tac_toe.h`
- other game files

Then the dashboard teammate can compile everything together.

Example:

```powershell
gcc main.c tic_tac_toe.c game2.c game3.c -o dashboard.exe
```

### Important Integration Rules for the Whole Team

To make integration easier, all teammates should follow these rules:

- each game should have one public start function
- each game should keep most logic in its own `.c` file
- each game should have its own `.h` file
- avoid putting all game logic directly in `main()`
- use `0` as a common back or exit rule if possible
- keep each game responsible for its own data files

### What This Project Already Provides for Integration

This tic-tac-toe project is already integration-friendly because:

- the game logic is separate from `main()`
- there is a single public start function
- exiting the game returns control cleanly
- file handling is inside the module
- no unfinished game state is saved on forced exit

## Future Improvement Ideas

These are optional and can be added later if needed:

- reset leaderboard option
- smarter computer moves
- player names
- colored output
- better dashboard integration with multiple shared headers

## Suggested Commit Message for This Change

If you want to commit this README, a good commit message is:

`Add detailed README with build, usage, and integration guide`

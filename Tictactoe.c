#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------- Global Variables ----------
char board[3][3];

// ---------- Function Declarations ----------
void initBoard();
void printBoard();
int checkWin();
int isDraw();
void playerMove(int player, char mark);
void computerMove();
void playHumanVsHuman();
void playHumanVsComputer();
void playGame(int mode);
void clear_screen();

// ---------- Function Definitions ----------

// Clears the console screen
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Initialize the board
void initBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Print the board
void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Check for win
int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return 1;
    return 0;
}

// Check for draw
int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Player move (with validation)
void playerMove(int player, char mark) {
    int row, col;
    while (1) {
        printf("Player %d (%c), enter row and column (0 1 2): ", player, mark);
        scanf("%d %d", &row, &col);
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = mark;
            break;
        }
        printf("Invalid move! Try again.\n");
    }
}

// Computer move (random)
void computerMove() {
    int row, col;
    while (1) {
        row = rand() % 3;
        col = rand() % 3;
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            printf("Computer chose: %d %d\n", row, col);
            break;
        }
    }
}

// Human vs Human mode
void playHumanVsHuman() {
    int player = 1;
    char mark;

    printf("Player 1 = X | Player 2 = O\n");

    while (1) {
        clear_screen();
        printBoard();
        mark = (player == 1) ? 'X' : 'O';
        playerMove(player, mark);

        if (checkWin()) {
            clear_screen();
            printBoard();
            printf("Player %d wins!\n", player);
            break;
        }

        if (isDraw()) {
            clear_screen();
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        player = (player == 1) ? 2 : 1;
    }
}

// Human vs Computer mode
void playHumanVsComputer() {
    int row, col;

    printf("You = X | Computer = O\n");

    while (1) {
        clear_screen();
        printBoard();
        printf("Your turn (X), enter row and column (0 1 2): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = 'X';

        if (checkWin()) {
            clear_screen();
            printBoard();
            printf("You win!\n");
            break;
        }

        if (isDraw()) {
            clear_screen();
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        computerMove();

        if (checkWin()) {
            clear_screen();
            printBoard();
            printf("Computer wins!\n");
            break;
        }

        if (isDraw()) {
            clear_screen();
            printBoard();
            printf("It's a draw!\n");
            break;
        }
    }
}

// Play based on mode
void playGame(int mode) {
    initBoard();
    if (mode == 1)
        playHumanVsComputer();
    else if (mode == 2)
        playHumanVsHuman();
    else
        printf("Invalid mode selected!\n");
}

// ---------- MAIN ----------
int main() {
    int mode;
    char playAgain;

    srand(time(0));

    do {
        clear_screen();
        printf("TIC TAC TOE GAME\n");
        printf("Select mode: 1 = Computer, 2 = Human: ");
        scanf("%d", &mode);

        playGame(mode);

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    clear_screen();
    printf("\n Thanks for playing Tic Tac Toe!\n");
    return 0;
}
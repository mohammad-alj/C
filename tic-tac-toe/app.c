#include <stdio.h>
#define ROWS 3
#define COLS 3

typedef struct Game
{
    char board[ROWS][COLS];
    int spaces;
    char current_player;
} Game;

void init_game(Game *g);
void print_board(char[ROWS][COLS]);
int place(Game *g, int row, int col);
int is_winner(Game g, char player);
int is_tie(Game g);

void clear_buffer()
{
    while (1)
        if (getchar() == '\n')
            break;
}

int main()
{
    printf("WELCOME TO TIC TAC TOE!\n");
    Game game;
    init_game(&game);

    while (1)
    {
        print_board(game.board);

        char might_be_winner = 'X';
        if (is_winner(game, might_be_winner))
        {
            printf("Player X has won!\n");
            break;
        }
        might_be_winner = 'O';
        if (is_winner(game, might_be_winner))
        {
            printf("Player O has won!\n");
            break;
        }
        if (is_tie(game))
        {
            printf("It's a tie!\n");
            break;
        }

        printf("%c players turn!\n", game.current_player);

        int row, col;
        do
        {
            do
            {
                printf("Enter row (1-3): ");
                int is_valid = scanf("%i", &row);
                row = (is_valid) ? row - 1 : -1;
            } while (0 > row || row > 2);
            clear_buffer();

            do
            {
                printf("Enter column (1-3): ");
                int is_valid = scanf("%i", &col);
                col = (is_valid) ? col - 1 : -1;
            } while (0 > col || col > 2);

            clear_buffer();
        } while (!place(&game, row, col));
    }
    return 0;
}

void init_game(Game *g)
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            g->board[i][j] = ' ';
    g->current_player = 'X';
    g->spaces = 9;
}

void print_board(char board[ROWS][COLS])
{
    printf("   1   2   3\n");
    printf("     |   |   \n");
    printf("1  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("  ___|___|___\n");
    printf("     |   |   \n");
    printf("2  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("  ___|___|___\n");
    printf("     |   |   \n");
    printf("3  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("     |   |   \n");
}

int place(Game *g, int row, int col)
{
    char *c = &g->board[row][col];
    if (*c != ' ')
        return 0;
    *c = g->current_player;
    g->current_player = (g->current_player == 'X') ? 'O' : 'X';
    g->spaces--;
    return 1;
}

int is_winner(Game g, char player)
{
    for (int i = 0; i < ROWS; i++)
    {
        if (g.board[i][0] == player && g.board[i][1] == player && g.board[i][2] == player)
            return 1;
    }

    for (int i = 0; i < COLS; i++)
    {
        if (g.board[0][i] == player && g.board[1][i] == player && g.board[2][i] == player)
            return 1;
    }

    if (g.board[0][0] == player && g.board[1][1] == player && g.board[2][2] == player)
        return 1;
    else if (g.board[0][2] == player && g.board[1][1] == player && g.board[2][0] == player)
        return 1;

    return 0;
}

int is_tie(Game g)
{
    return (!is_winner(g, 'X') && !is_winner(g, 'O') && g.spaces == 0) ? 1 : 0;
}
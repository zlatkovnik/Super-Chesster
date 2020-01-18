#include "gamecontext.h"

GameContext::GameContext()
{
    blackTurn = false;
    setDefaultBoard();
}

void GameContext::setDefaultBoard()
{
    board[0][0] = board[0][7] = 'R';
    board[7][0] = board[7][7] = 'r';
    board[0][1] = board[0][6] = 'N';
    board[7][1] = board[7][6] = 'n';
    board[0][2] = board[0][5] = 'B';
    board[7][2] = board[7][5] = 'b';
    board[0][3] = 'Q';
    board[7][3] = 'q';
    board[0][4] = 'K';
    board[7][4] = 'k';
    for(int i = 0; i < 8; i++){
        board[1][i] = 'P';
        board[2][i] = '_';
        board[3][i] = '_';
        board[4][i] = '_';
        board[5][i] = '_';
        board[6][i] = 'p';
    }
}

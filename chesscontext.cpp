#include "chesscontext.h"
#include <iostream>

ChessContext::ChessContext()
{
    blackTurn = false;
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

ChessContext::ChessContext(ChessContext &cc)
{
    blackTurn = cc.blackTurn;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            board[i][j] = cc.board[i][j];
}

char ChessContext::tile(int i, int j)
{
    return board[i][j];
}

bool ChessContext::isBlackTurn()
{
    return blackTurn;
}

void ChessContext::playTurn(int fromX, int fromY, int toX, int toY)
{
    board[toY][toX] = board[fromY][fromX];
    board[fromY][fromX] = '_';
    blackTurn = !blackTurn;
}

void ChessContext::playTurn(Turn turn)
{
    board[turn.toY][turn.toX] = board[turn.fromY][turn.fromX];
    board[turn.fromY][turn.fromX] = '_';
    blackTurn = !blackTurn;
}

QList<Turn> ChessContext::getTurns(int x, int y)
{
    char f = board[y][x];
    if(blackTurn){
        if(f == 'P')
            return getPawnTurns(x, y);
        else if(f == 'R')
            return getRookTurns(x, y);
        else if(f == 'N')
            return getKnightTurns(x, y);
        else if(f == 'B')
            return getBishopTurns(x, y);
        else if(f == 'Q')
            return getQueenTurns(x, y);
        else
            return getKingTurns(x, y);
    }
    else{
        if(f == 'p')
            return getPawnTurns(x, y);
        else if(f == 'r')
            return getRookTurns(x, y);
        else if(f == 'n')
            return getKnightTurns(x, y);
        else if(f == 'b')
            return getBishopTurns(x, y);
        else if(f == 'q')
            return getQueenTurns(x, y);
        else
            return getKingTurns(x, y);
    }
}


QList<Turn> ChessContext::getAllTurns()
{
    QList<Turn> turns;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(board[i][j] != '_'){
                if(blackTurn && board[i][j] < 'Z')
                    turns.append(getTurns(j, i));
                else if(!blackTurn && board[i][j] > 'Z')
                    turns.append(getTurns(j, i));
            }
    return turns;
}

QList<Turn> ChessContext::getPawnTurns(int x, int y)
{
    QList<Turn> turns;
    if(!blackTurn){
        int posY = y - 1;
        int posX = x - 1;
        if (board[posY][x] == '_' && posY >= 0) {
            Turn turn(x, y, x, posY);
            turns.append(turn);
        }
        if(y == 6 && board[posY - 1][x] == '_') {
            Turn turn(x, y, x, posY - 1);
            turns.append(turn);
        }
        if (posX >= 0 && posY >= 0) {
            char f = board[posY][posX];
            if (f > 'A' && f < 'Z'){
                Turn turn(x, y, posX, posY);
                turns.append(turn);
            }
        }
        posX = x + 1;
        if(posX < 8 && posY >= 0) {
            char f = board[posY][posX];
            if (f > 'A' && f < 'Z') {
                Turn turn(x, y, posX, posY);
                turns.append(turn);
            }
        }
    }
    else{
        int posY = y + 1;
        int posX = x - 1;
        if (board[posY][x] == '_' && posY < 8) {
            Turn turn(x, y, x, posY);
            turns.append(turn);
        }
        if(y == 1 && board[posY + 1][x] == '_') {
            Turn turn(x, y, x, posY + 1);
            turns.append(turn);
        }
        if (posX >= 0 && posY < 8) {
            char f = board[posY][posX];
            if (f > 'a' && f < 'z'){
                Turn turn(x, y, posX, posY);
                turns.append(turn);
            }
        }
        posX = x + 1;
        if(posX < 8 && posY < 8) {
            char f = board[posY][posX];
            if (f > 'a' && f < 'z') {
                Turn turn(x, y, posX, posY);
                turns.append(turn);
            }
        }
    }
    return turns;
}

QList<Turn> ChessContext::getRookTurns(int x, int y)
{
    QList<Turn> turns;
    int j = x - 1;
    int i = y;
    bool hit = false;
    //LEFT
    while(!hit && j >= 0)
    {
        char c = board[i][j];
        if (c == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && c >= 'a' && c <= 'z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else if(!blackTurn && c >= 'A' && c <= 'Z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else
            hit = true;
        j--;
    }
    j = x + 1;
    i = y;
    hit = false;
    //RIGHT
    while (!hit && j < 8)
    {
        char c = board[i][j];
        if (c == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && c >= 'a' && c <= 'z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else
            hit = true;
        j++;
    }
    j = x;
    i = y - 1;
    hit = false;
    //UP
    while (!hit && i >= 0)
    {
        char c = board[i][j];
        if (c == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && c >= 'a' && c <= 'z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else
            hit = true;
        i--;
    }
    j = x;
    i = y + 1;
    hit = false;
    //DOWN
    while (!hit && i < 8)
    {
        char c = board[i][j];
        if (c == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && c >= 'a' && c <= 'z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z')
        {
            {Turn turn(x, y, j, i); turns.append(turn);}
            hit = true;
        }
        else
            hit = true;
        i++;
    }
    return turns;
}

QList<Turn> ChessContext::getKnightTurns(int x, int y)
{
    QList<Turn> turns;
    char f;
    int i = y - 1;
    int j = x - 2;
    if(i >= 0 && j >= 0)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    i = y + 1;
    if (i < 8 && j >= 0)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    j = x - 1;
    i = y - 2;
    if (i >= 0 && j >= 0)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    j = x + 1;
    if (i >= 0 && j < 8)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    i = y - 1;
    j = x + 2;
    if (i >= 0 && j < 8)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    i = y + 1;
    if (i < 8 && j < 8)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    i = y + 2;
    j = x - 1;
    if (i < 8 && j >= 0)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    j = x + 1;
    if (i < 8 && j < 8)
    {
        f = board[i][j];
        if (f == '_')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (blackTurn && f >= 'a' && f <= 'z')
        {Turn turn(x, y, j, i); turns.append(turn);}
        else if (!blackTurn && f >= 'A' && f <= 'Z')
        {Turn turn(x, y, j, i); turns.append(turn);}
    }
    return turns;
}

QList<Turn> ChessContext::getBishopTurns(int x, int y)
{
    QList<Turn> turns;
    int j = x - 1;
    int i = y - 1;
    bool hit = false;
    //LEFT UP
    while (!hit && j >= 0 && i >= 0)
    {
        char c = board[i][j];
        if (c == '_'){
            Turn turn(x, y, j, i);
            turns.append(turn);
        }
        else if (blackTurn && c >= 'a' && c <= 'z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else
            hit = true;
        j--;
        i--;
    }
    j = x + 1;
    i = y - 1;
    hit = false;
    //RIGHT UP
    while (!hit && j < 8 && i >= 0)
    {
        char c = board[i][j];
        if (c == '_') {
            Turn turn(x, y, j, i);
            turns.append(turn);
        }
        else if (blackTurn && c >= 'a' && c <= 'z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else
            hit = true;
        j++;
        i--;
    }
    j = x - 1;
    i = y + 1;
    hit = false;
    //LEFT DOWN
    while (!hit && i < 8 && j >= 0)
    {
        char c = board[i][j];
        if (c == '_'){
            Turn turn(x, y, j, i);
            turns.append(turn);
        }
        else if (blackTurn && c >= 'a' && c <= 'z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else
            hit = true;
        i++;
        j--;
    }
    j = x + 1;
    i = y + 1;
    hit = false;
    //RIGHT DOWN
    while (!hit && i < 8 && j < 8)
    {
        char c = board[i][j];
        if (c == '_') {
            Turn turn(x, y, j, i);
            turns.append(turn);
        }
        else if (blackTurn && c >= 'a' && c <= 'z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else if (!blackTurn && c >= 'A' && c <= 'Z') {
            Turn turn(x, y, j, i);
            turns.append(turn);
            hit = true;
        }
        else
            hit = true;
        i++;
        j++;
    }
    return turns;
}

QList<Turn> ChessContext::getQueenTurns(int x, int y)
{
    QList<Turn> turns(getRookTurns(x, y));
    turns.append(getBishopTurns(x, y));
    return turns;
}

QList<Turn> ChessContext::getKingTurns(int x, int y)
{
    QList<Turn> turns;
    for(int i = y - 1; i <= y + 1; i++)
    {
        for(int j = x - 1; j <= x + 1; j++)
        {
            if(i >= 0 && j >= 0 && i < 8 && j < 8)
            {
                char c = board[i][j];
                if (c == '_'){
                    Turn turn(x, y, j, i);
                    turns.append(turn);
                }
                else if(blackTurn && c >= 'a' && c <= 'z'){
                    Turn turn(x, y, j, i);
                    turns.append(turn);
                }

                else if(!blackTurn && c >= 'A' && c <= 'Z'){
                    Turn turn(x, y, j, i);
                    turns.append(turn);
                }
            }
        }
    }
    return turns;
}

Turn ChessContext::getBestTurn(ChessContext cc, int depth)
{
    int alpha = -214748364, beta = 214748364;
    QList<Turn> turns(cc.getAllTurns());
    Turn maxTurn;
    for(int i = 0; i < turns.count(); i++)      //TODO
    {
        ChessContext newContext(cc);
        newContext.playTurn(turns[i]);

        int val = -AlphaBeta(newContext, depth - 1, -beta, -alpha);
        if(val > alpha)
        {
            maxTurn.fromX = turns[i].fromX;
            maxTurn.fromY = turns[i].fromY;
            maxTurn.toX = turns[i].toX;
            maxTurn.toY = turns[i].toY;
            alpha = val;
        }
        if (alpha >= beta)
            break;
    }
    return maxTurn;
}

int ChessContext::AlphaBeta(ChessContext cc, int depth, int alpha, int beta)
{
    if(depth <= 0)
    {
        return cc.EvaluateBoard();
    }
    QList<Turn> turns(cc.getAllTurns());
    if(turns.count() == 0)
    {
        return cc.EvaluateBoard();
    }
    Turn turnToReturn(0, 0, 0, 0);
    for(int i = 0; i < turns.count(); i++)
    {
        ChessContext newContext(cc);
        newContext.playTurn(turns[i]);
        int val = -AlphaBeta(newContext, depth - 1, -beta, -alpha);
        if(val > alpha)
            alpha = val;
        if (alpha >= beta)
            break;
    }
    return alpha;
}

int ChessContext::EvaluateBoard()
{
    int acc = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //As black player
            char f = board[i][j];
            if(f == '_')
                continue;
            else if(f == 'P')
                acc += 100;
            else if(f == 'p')
                acc -= 100;
            else if(f == 'N')
                acc += 300;
            else if(f == 'n')
                acc -= 300;
            else if(f == 'B')
                acc += 325;
            else if(f == 'b')
                acc -= 325;
            else if(f == 'R')
                acc += 500;
            else if(f == 'r')
                acc -= 500;
            else if(f == 'Q')
                acc += 900;
            else if(f == 'q')
                acc -= 900;
            else if(f == 'K')
                acc += 100000;
            else if(f == 'k')
                acc -= 100000;
        }
    }
    if(blackTurn)
        return acc;
    else
        return -acc;
}

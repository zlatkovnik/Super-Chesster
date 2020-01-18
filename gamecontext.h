#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H


class GameContext
{
private:
    char board[8][8];
    bool blackTurn;
public:
    GameContext();

    void setDefaultBoard();
};

#endif // GAMECONTEXT_H

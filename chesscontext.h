#ifndef CHESSCONTEXT_H
#define CHESSCONTEXT_H

#include <QObject>
#include <QList>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <functional>
#include <turn.h>

class ChessContext
{

private:
    char board[8][8];
    bool blackTurn;
    inline constexpr const static int whiteKnightValue[8][8] = {
        {-16, -8, -4, 0, 0, -4, -8, -16},
        {8, 16, 32, 32, 32, 32, 16, 8},
        {24, 40, 56, 62, 62, 56, 40, 24},
        {32, 48, 60, 64, 64, 60, 48, 32},
        {16, 32, 56, 60, 60, 56, 32, 16},
        {-8, 8, 24, 20, 20, 24, 8, -8},
        {-20, -16, -8, 16, 16, -8, -16, -20},
        {-48, -32, -24, -16, -16, -24, -32, -48}
    };
    inline constexpr const static int blackKnightValue[8][8] = {
        {-48, -32, -24, -16, -16, -24, -32, -48},
        {-20, -16, -8, 16, 16, -8, -16, -20},
        {-8, 8, 24, 20, 20, 24, 8, -8},
        {16, 32, 56, 60, 60, 56, 32, 16},
        {32, 48, 60, 64, 64, 60, 48, 32},
        {24, 40, 56, 62, 62, 56, 40, 24},
        {8, 16, 32, 32, 32, 32, 16, 8},
        {-16, -8, -4, 0, 0, -4, -8, -16}
    };

    std::vector<Turn> *getAllTurns();
    std::vector<Turn> *getPawnTurns(int x, int y);
    std::vector<Turn> *getRookTurns(int x, int y);
    std::vector<Turn> *getKnightTurns(int x, int y);
    std::vector<Turn> *getBishopTurns(int x, int y);
    std::vector<Turn> *getQueenTurns(int x, int y);
    std::vector<Turn> *getKingTurns(int x, int y);

    static int pvs(ChessContext cc, int depth, int alpha, int beta);
    static int AlphaBeta(ChessContext cc, int depth, int alpha, int beta);
    int EvaluateBoard();
public:
    ChessContext();
    ChessContext(const ChessContext &cc);

    char tile(int i, int j);
    bool isBlackTurn();
    void playTurn(int fromX, int fromY, int toX, int toY);
    void playTurn(Turn turn);
    std::vector<Turn> *getTurns(int x, int y);

    static Turn getBestTurn(ChessContext cc, int depth);


signals:

public slots:

};

#endif // CHESSCONTEXT_H

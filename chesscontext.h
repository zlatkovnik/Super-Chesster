#ifndef CHESSCONTEXT_H
#define CHESSCONTEXT_H

#include <QObject>
#include <QList>
#include <QLinkedList>
#include <thread>
#include <future>
#include <turn.h>

class ChessContext
{

private:
    char board[8][8];
    bool blackTurn;

    QList<Turn> getAllTurns();
    QList<Turn> getPawnTurns(int x, int y);
    QList<Turn> getRookTurns(int x, int y);
    QList<Turn> getKnightTurns(int x, int y);
    QList<Turn> getBishopTurns(int x, int y);
    QList<Turn> getQueenTurns(int x, int y);
    QList<Turn> getKingTurns(int x, int y);

    static int AlphaBeta(ChessContext cc, int depth, int alpha, int beta);
    int EvaluateBoard();
public:
    ChessContext();
    ChessContext(ChessContext &cc);

    char tile(int i, int j);
    bool isBlackTurn();
    void playTurn(int fromX, int fromY, int toX, int toY);
    void playTurn(Turn turn);
    QList<Turn> getTurns(int x, int y);

    static Turn getBestTurn(ChessContext cc, int depth);


signals:

public slots:
};

#endif // CHESSCONTEXT_H

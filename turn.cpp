#include "turn.h"

Turn::Turn()
{

}

Turn::Turn(const Turn &turn)
{
    fromX = turn.fromX;
    fromY = turn.fromY;
    toX = turn.toX;
    toY = turn.toY;
}

Turn::Turn(int fx, int fy, int tx, int ty): fromX(fx), fromY(fy), toX(tx), toY(ty)
{
}

bool Turn::operator==(const Turn &turn) const
{
    return (fromX == turn.fromX && fromY == turn.fromY &&
            toX == turn.toX && toY == turn.toY);
}

Turn &Turn::operator=(const Turn &turn)
{
    fromX = turn.fromX;
    fromY = turn.fromY;
    toX = turn.toX;
    toY = turn.toY;
    return *this;
}


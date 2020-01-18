#ifndef TURN_H
#define TURN_H


class Turn
{
public:
    int fromX;
    int fromY;
    int toX;
    int toY;
    Turn();
    Turn(const Turn &turn);
    Turn(int fx, int fy, int tx, int ty);
    bool operator== (const Turn &turn) const;
    Turn &operator= (const Turn &turn);
};

#endif // TURN_H

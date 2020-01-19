#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QMouseEvent>
#include <QSpinBox>
#include <QPushButton>
#include <thread>
#include <future>
#include <chesscontext.h>

class BoardView : public QWidget
{
    Q_OBJECT
private:
    QWidget *myParent;
    ChessContext context;
    ChessContext prevContext;
    bool canUndo;
    QImage spriteSheet;

    int selectedX;
    int selectedY;
    QList<Turn> turns;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    QPoint getSprite(int i, int j);
public:
    explicit BoardView(QWidget *parent);


signals:

public slots:
    void undoMove();
};

#endif // BOARDVIEW_H

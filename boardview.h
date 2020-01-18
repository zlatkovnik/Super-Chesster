#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QMouseEvent>
#include <thread>
#include <future>
#include <chesscontext.h>

class BoardView : public QWidget
{
    Q_OBJECT
private:
    ChessContext context;
    QImage spriteSheet;

    int selectedX;
    int selectedY;
    QList<Turn> turns;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    QPoint getSprite(int i, int j);
public:
    explicit BoardView(QWidget *parent = nullptr);


signals:

public slots:
};

#endif // BOARDVIEW_H

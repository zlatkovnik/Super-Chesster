#include "boardview.h"
#include "iostream"


BoardView::BoardView(QWidget *parent) : QWidget(parent)
{
    spriteSheet.load(":/chessFigures.png");
    selectedX = -1;
    selectedY = -1;
}

void BoardView::paintEvent(QPaintEvent *event)
{
    event = nullptr;
    QPainter p(this);
    bool black = true;
    int tileSize = this->height() >> 3;
    int x = 0;
    int y = 0;
    for(int i = 0; i < 8; i++){
        x = 0;
        for(int j = 0; j < 8; j++){
            //Tiles
            QRect rect(x, y, tileSize, tileSize);
            QColor c;
            if(black)
                c.setRgb(118, 150, 86);
            else
                c.setRgb(238, 238, 210);
            //Check if tile is selected
            Turn t(selectedX, selectedY, j, i);
            if(turns.contains(t))
                c.setRgb(0, 0, 255);
            p.fillRect(rect, c);
            p.drawRect(rect);
            //Pieces
            QPoint point = getSprite(i, j);
            if(point.x() >= 0){
                QImage temp = spriteSheet.copy(point.x(), point.y(), 200, 200);
                temp.scaled(tileSize, tileSize, Qt::KeepAspectRatio);
                p.drawImage(rect, temp);
            }
            //Math
            x += tileSize;
            black = !black;
        }
        black = !black;
        y += tileSize;
    }
}

void BoardView::mousePressEvent(QMouseEvent *event)
{
    int tileSize = this->height() >> 3;
    int y = event->y() / tileSize;
    int x = event->x() / tileSize;
    if(x < 0 || y < 0 || x >= 8 || y >= 8){
        selectedX = selectedY = -1;
        return;
    }

    if(selectedX >= 0){
        //If piece selected
        Turn turn(selectedX, selectedY, x, y);
        if(turns.contains(turn)){
            context.playTurn(selectedX, selectedY, x, y);

            //AI HERE
            auto fu = std::async(std::launch::async, ChessContext::getBestTurn, context, 5);
            Turn turn = fu.get();
            //Turn turn = ChessContext::getBestTurn(context, 5);
            context.playTurn(turn);
        }
        selectedX = -1;
        selectedY = -1;
    }
    else{
        //If piece not selected
        turns.clear();
        selectedX = x;
        selectedY = y;
        if((context.isBlackTurn() && context.tile(y, x) <= 'Z') ||
                (!context.isBlackTurn() && context.tile(y, x) > 'Z'))
        turns.append(context.getTurns(x, y));
    }
    update();
}

QPoint BoardView::getSprite(int i, int j)
{
    QPoint point;
    char figure = context.tile(i, j);
    if(figure == '_'){
        point.setX(-1);
        point.setY(-1);
    }
    else if(figure == 'P'){
        point.setX(1000);
        point.setY(0);
    }
    else if(figure == 'p'){
        point.setX(1000);
        point.setY(200);
    }
    else if(figure == 'R'){
        point.setX(800);
        point.setY(0);
    }
    else if(figure == 'r'){
        point.setX(800);
        point.setY(200);
    }
    else if(figure == 'N'){
        point.setX(600);
        point.setY(0);
    }
    else if(figure == 'n'){
        point.setX(600);
        point.setY(200);
    }
    else if(figure == 'B'){
        point.setX(400);
        point.setY(0);
    }
    else if(figure == 'b'){
        point.setX(400);
        point.setY(200);
    }
    else if(figure == 'Q'){
        point.setX(200);
        point.setY(0);
    }
    else if(figure == 'q'){
        point.setX(200);
        point.setY(200);
    }
    else if(figure == 'K'){
        point.setX(0);
        point.setY(0);
    }
    else if(figure == 'k'){
        point.setX(0);
        point.setY(200);
    }
    return point;
}

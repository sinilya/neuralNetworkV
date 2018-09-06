#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "picturedata.h"

class drawScene : public QGraphicsScene
{
public:

    std::vector<double> getPicture();
    void setColor(QColor color);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    drawScene(int rowsCount, int colsCount, int width, int height, QColor color);
    ~drawScene();

private:
    QColor rectColor;
    int rows;
    int cols;
    int cellWidth;
    int cellHeight;
    pictureData* newData;
};

#endif // DRAWSCENE_H

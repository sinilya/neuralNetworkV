#include "drawscene.h"

drawScene::drawScene(int rowsCount, int colsCount, int width, int height)
{
    newData = new pictureData(rowsCount * colsCount);
    rows = rowsCount;
    cols = colsCount;
    cellWidth = width/colsCount;
    cellHeight = height/rowsCount;
    QPen lines(Qt::black);
    lines.setCosmetic(true);
    for(int i = cellWidth; i < width; i=i+cellWidth){
        addLine(i, 0, i, height, lines);
    }
    for(int i = cellHeight; i < height; i=i+cellHeight){
        addLine(0, i, width, i, lines);
    }
}

drawScene::~drawScene(){
    delete newData;
}

void drawScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    if(x < cols*cellWidth && x > 0 && y < rows*cellHeight && y > 0){
        newData->insertElem(1, floor(y/cellHeight)*cols + floor(x/cellWidth));
        addRect(floor(x/cellWidth)*cellWidth, floor(y/cellHeight)*cellHeight, cellWidth, cellHeight, QPen(Qt::NoPen),QBrush(Qt::red));
    }
}

void drawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    if(x < cols*cellWidth && x > 0 && y < rows*cellHeight && y > 0){
        newData->insertElem(1, floor(y/cellHeight)*cols + floor(x/cellWidth));
        addRect(floor(x/cellWidth)*cellWidth, floor(y/cellHeight)*cellHeight, cellWidth, cellHeight, QPen(Qt::NoPen),QBrush(Qt::red));
    }
}

std::vector<double> drawScene::getPicture(){
    return newData->getData();
}

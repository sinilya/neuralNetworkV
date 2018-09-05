#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    view = new QGraphicsView(this);

    sizeXLabel = new QLabel(this);
    sizeYLabel = new QLabel(this);
    sizeX = new QLineEdit(this);
    sizeY = new QLineEdit(this);
    applySize = new QPushButton(this);
    handleButton = new QPushButton(this);

    QMainWindow::setGeometry(50, 50, 700, 700);
    sizeXLabel->setGeometry(10, 510, 120, 30);
    sizeYLabel->setGeometry(10, 550, 120, 30);
    sizeX->setGeometry(140, 510, 40, 30);
    sizeY->setGeometry(140, 550, 40, 30);
    applySize->setGeometry(10, 590, 100, 30);
    view->setGeometry(0, 0, 500, 500);
    handleButton->setGeometry(10, 630, 100, 30);

    sizeXLabel->setText("Количество строк:");
    sizeYLabel->setText("Количество столбцов:");
    applySize->setText("Применить");
    handleButton->setText("Обработать");

    sizeX->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), this));
    sizeY->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), this));

    connect(applySize, SIGNAL(released()), this, SLOT(createScene()));
    connect(handleButton, SIGNAL(released()), this, SLOT(handlePicture()));
}

void MainWindow::createScene() {
    int x = sizeX->text().toInt();
    int y = sizeY->text().toInt();
    if(x > y){
        y = round((y*500)/x);
        x = 500;
    } else if(x < y) {
        x = round((x*500)/y);
        y = 500;
    } else {
        x = 500; y = 500;
    }
    x = (x%(sizeX->text().toInt()) == 0) ? x : floor(x/(sizeX->text().toInt()))*(sizeX->text().toInt());
    y = (y%(sizeY->text().toInt()) == 0) ? y : floor(y/(sizeY->text().toInt()))*(sizeY->text().toInt());
    view->setGeometry(0, 0, y, x);
    newScene = new drawScene(sizeX->text().toInt(), sizeY->text().toInt(), y, x);
    view->setScene(newScene);
    newScene->setSceneRect(0,0,view->width(), view->height());
    view->fitInView(newScene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::handlePicture(){
    std::vector<double> v = newScene->getPicture();
    QString buff = "";
    for(int i = 0; i < v.size(); i++)
        buff = buff + " " + QString::number(v.at(i));
    qDebug() << buff;

    delete newScene;
    this->createScene();
}

MainWindow::~MainWindow()
{

}

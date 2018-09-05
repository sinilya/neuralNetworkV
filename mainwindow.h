#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>

#include "drawscene.h"
#include "picturedata.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createScene();
    void handlePicture();

private:
    QLabel* sizeXLabel;
    QLabel* sizeYLabel;
    QLineEdit* sizeX;
    QLineEdit* sizeY;
    QPushButton* handleButton;
    QPushButton* applySize;

    drawScene* newScene;
    QGraphicsView* view;

};

#endif // MAINWINDOW_H

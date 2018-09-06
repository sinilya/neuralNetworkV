#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>
#include <QStackedWidget>
#include <QGroupBox>
#include <QColorDialog>

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

    void switchToCreate();
    void switchToTeach();
    void switchToStatistics();
    void selectColor();
    void handleYes();
    void handleNo();

private:
    QWidget* currentColor;
    QPushButton* chooseColor;
    QGroupBox* resultBox;
    QGroupBox* setSceneBox;
    QLabel* neuralResultLabel;
    QLineEdit* neuralResult;
    QPushButton* toCreatePage;
    QPushButton* toTeachPage;
    QPushButton* toStatisticPage;
    QGroupBox* navigation;
    QStackedWidget* stackedWidget;
    QWidget* createNeuralWidget;
    QWidget* teachWidget;
    QWidget* statisticsWidget;
    QLabel* sizeXLabel;
    QLabel* sizeYLabel;
    QLineEdit* sizeX;
    QLineEdit* sizeY;
    QPushButton* handleButton;
    QPushButton* applySize;
    QPushButton* yes;
    QPushButton* no;

    drawScene* newScene = NULL;
    QGraphicsView* view;

    QColor color = Qt::black;

};

#endif // MAINWINDOW_H

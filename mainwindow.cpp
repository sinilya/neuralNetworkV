#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);

    createNeuralWidget = new QWidget;
    teachWidget = new QWidget;
    statisticsWidget = new QWidget;
    stackedWidget->addWidget(createNeuralWidget);
    stackedWidget->addWidget(teachWidget);
    stackedWidget->addWidget(statisticsWidget);

    navigation = new QGroupBox(this);
    toCreatePage = new QPushButton(navigation);
    toTeachPage = new QPushButton(navigation);
    toStatisticPage = new QPushButton(navigation);

    setSceneBox = new QGroupBox(teachWidget);
    view = new QGraphicsView(teachWidget);
    resultBox = new QGroupBox(teachWidget);

    handleButton = new QPushButton(resultBox);
    neuralResult = new QLineEdit(resultBox);
    neuralResultLabel = new QLabel(resultBox);
    yes = new QPushButton(resultBox);
    no = new QPushButton(resultBox);

    sizeXLabel = new QLabel(setSceneBox);
    sizeYLabel = new QLabel(setSceneBox);
    sizeX = new QLineEdit(setSceneBox);
    sizeY = new QLineEdit(setSceneBox);
    applySize = new QPushButton(setSceneBox);
    chooseColor = new QPushButton(setSceneBox);
    currentColor = new QWidget(setSceneBox);

    QMainWindow::setGeometry(50, 50, 710, 520);
    sizeXLabel->setGeometry(10, 20, 120, 30);
    sizeYLabel->setGeometry(10, 60, 120, 30);
    sizeX->setGeometry(140, 20, 30, 30);
    sizeY->setGeometry(140, 60, 30, 30);
    applySize->setGeometry(10, 120, 160, 30);
    view->setGeometry(10, 10, 500, 500);
    handleButton->setGeometry(10, 20, 160, 30);
    stackedWidget->setGeometry(QMainWindow::rect());
    navigation->setGeometry(520, 10, 180, 140);
    toCreatePage->setGeometry(10, 20, 160, 30);
    toTeachPage->setGeometry(10, 60, 160, 30);
    toStatisticPage->setGeometry(10, 100, 160, 30);
    neuralResultLabel->setGeometry(10, 60, 60, 30);
    neuralResult->setGeometry(80, 60, 30, 30);
    setSceneBox->setGeometry(520, 160, 180, 200);
    resultBox->setGeometry(520, 370, 180, 140);
    chooseColor->setGeometry(10, 160, 120, 30);
    yes->setGeometry(10, 100, 80, 30);
    no->setGeometry(90, 100, 80, 30);
    currentColor->setGeometry(140, 160, 30, 30);

    neuralResult->setReadOnly(true);
    currentColor->setStyleSheet(QString("background-color:").append(QColor(Qt::black).name()).append(";"));

    sizeXLabel->setText("Количество строк:");
    sizeYLabel->setText("Количество столбцов:");
    applySize->setText("Применить");
    handleButton->setText("Обработать");
    toCreatePage->setText("Создать");
    toTeachPage->setText("Обучить");
    toStatisticPage->setText("Статистика");
    navigation->setTitle("Навигация");
    neuralResultLabel->setText("Результат:");
    setSceneBox->setTitle("Настройка");
    resultBox->setTitle("Обучение");
    chooseColor->setText("Выбрать цвет");
    yes->setText("Да");
    no->setText("Нет");

    sizeX->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), this));
    sizeY->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), this));

    connect(applySize, SIGNAL(released()), this, SLOT(createScene()));
    connect(handleButton, SIGNAL(released()), this, SLOT(handlePicture()));

    connect(toCreatePage, SIGNAL(released()), this, SLOT(switchToCreate()));
    connect(toTeachPage, SIGNAL(released()), this, SLOT(switchToTeach()));
    connect(toStatisticPage, SIGNAL(released()), this, SLOT(switchToStatistics()));
    connect(chooseColor, SIGNAL(released()), this, SLOT(selectColor()));
    connect(yes, SIGNAL(released()), this, SLOT(handleYes()));
    connect(no, SIGNAL(released()), this, SLOT(handleNo()));

    stackedWidget->setCurrentWidget(teachWidget);
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
    view->setGeometry(10, 10, y, x);
    newScene = new drawScene(sizeX->text().toInt(), sizeY->text().toInt(), y, x, color);
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

void MainWindow::switchToCreate(){
    stackedWidget->setCurrentWidget(createNeuralWidget);
}

void MainWindow::switchToTeach(){
    stackedWidget->setCurrentWidget(teachWidget);
}

void MainWindow::switchToStatistics(){
    stackedWidget->setCurrentWidget(statisticsWidget);
}

void MainWindow::selectColor() {
    color = QColorDialog::getColor(Qt::black);
    if(newScene){
        newScene->setColor(color);
    }
    currentColor->setStyleSheet(QString("background-color:").append(color.name()).append(";"));
}

void MainWindow::handleYes(){

}

void MainWindow::handleNo(){

}

MainWindow::~MainWindow()
{

}

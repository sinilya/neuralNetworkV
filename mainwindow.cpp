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

    currentNeuralNetworkLabel = new QLabel(createNeuralWidget);
    currentNeuralNetwork = new QLabel(createNeuralWidget);
    createNeuralBox = new QGroupBox(createNeuralWidget);

    layersCountLabel = new QLabel(createNeuralBox);
    layersCount = new QLineEdit(createNeuralBox);
    createLayers = new QPushButton(createNeuralBox);
    setNeuralCountField = new QVBoxLayout(createNeuralBox);

    navigation = new QGroupBox(this);
    toCreatePage = new QPushButton(navigation);
    toTeachPage = new QPushButton(navigation);
    toStatisticPage = new QPushButton(navigation);

    setSceneBox = new QGroupBox(teachWidget);
    view = new QGraphicsView(teachWidget);
    resultBox = new QGroupBox(teachWidget);
    chooseNeuralLabel = new QLabel(teachWidget);
    chooseNeural = new QComboBox(teachWidget);

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

    QMainWindow::setGeometry(50, 50, 710, 570);
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
    chooseNeuralLabel->setGeometry(10, 520, 70, 30);
    chooseNeural->setGeometry(90, 520, 200, 30);
    currentNeuralNetworkLabel->setGeometry(10, 10, 130, 30);
    currentNeuralNetwork->setGeometry(150, 10, 300, 30);
    createNeuralBox->setGeometry(10, 50, 300, 300);
    layersCountLabel->setGeometry(10, 20, 100, 30);
    layersCount->setGeometry(120, 20, 30, 30);
    createLayers->setGeometry(160, 20, 100, 30);
    setNeuralCountField->setGeometry(QRect(10, 60, 50, 50));

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
    chooseNeuralLabel->setText("Выбрать сеть:");
    currentNeuralNetworkLabel->setText("Текущая нейронная сеть:");
    createNeuralBox->setTitle("Создать нейронную сеть");
    layersCountLabel->setText("Количество слоёв:");
    createLayers->setText("Создать");

    sizeX->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), this));
    sizeY->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), this));
    layersCount->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,2}"), this));

    connect(applySize, SIGNAL(released()), this, SLOT(createScene()));
    connect(handleButton, SIGNAL(released()), this, SLOT(handlePicture()));

    connect(toCreatePage, SIGNAL(released()), this, SLOT(switchToCreate()));
    connect(toTeachPage, SIGNAL(released()), this, SLOT(switchToTeach()));
    connect(toStatisticPage, SIGNAL(released()), this, SLOT(switchToStatistics()));
    connect(chooseColor, SIGNAL(released()), this, SLOT(selectColor()));
    connect(yes, SIGNAL(released()), this, SLOT(handleYes()));
    connect(no, SIGNAL(released()), this, SLOT(handleNo()));
    connect(createLayers, SIGNAL(released()), this, SLOT(createNeuralLayers()));

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

void MainWindow::createNeuralLayers(){
    for(int i = 0; i < layersCount->text().toInt(); i++){
        QPushButton* newButton = new QPushButton("кнопочка");
        newButton->setGeometry(10, 10, 100, 30);
        setNeuralCountField->addWidget(newButton);
    }
}

void MainWindow::handleYes(){

}

void MainWindow::handleNo(){

}

MainWindow::~MainWindow()
{

}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    blinkTimer = new QTimer(this);
    delayTimer = new QTimer(this);

    blinkTimer->setSingleShot(true);
    delayTimer->setSingleShot(true);

    blinkTimer->setInterval(1000);
    delayTimer->setInterval(500);

    connect(blinkTimer, &QTimer::timeout, this, &MainWindow::endBlink);
    connect(delayTimer, &QTimer::timeout, this, &MainWindow::nextBlink);

}

MainWindow::~MainWindow()
{
    delete ui;
}

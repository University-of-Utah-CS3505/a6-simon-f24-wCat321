#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Simon(this);
    blinkTimer = new QTimer(this);
    delayTimer = new QTimer(this);

    blinkTimer->setSingleShot(true);
    delayTimer->setSingleShot(true);
    blinkTimer->setInterval(blinkTimerTime);
    delayTimer->setInterval(delayTimerTime);

    connect(blinkTimer, &QTimer::timeout, this, &MainWindow::endBlink);
    connect(delayTimer, &QTimer::timeout, this, &MainWindow::nextBlink);

    connect(ui->buttonBlue, &QPushButton::pressed, this, [this]() {game->getInput(true);});
    connect(ui->buttonRed, &QPushButton::pressed, this, [this]() {game->getInput(false);});

    ui->buttonBlue->setEnabled(false);
    ui->buttonRed->setEnabled(false);

    // DEBUG:
    connect(ui->buttonStart, &QPushButton::pressed, this, [this]() {startBlink(&temp);});
}

void MainWindow::startBlink(const QVector<bool>* pattern) {
    blinkPattern = pattern;
    index = 0;
    ui->buttonRed->setEnabled(false);
    ui->buttonBlue->setEnabled(false);
    ui->buttonStart->setEnabled(false); // TEMP!! REMOVE
    nextBlink();
}

void MainWindow::nextBlink() {
    if (!blinkPattern || index >= blinkPattern->size()) { // If no pattern or if at the end of the list:
        releaseButtons();
    }

    if (blinkPattern->at(index))
        ui->buttonBlue->setStyleSheet(blue_button_showcase_style);
    else
        ui->buttonRed->setStyleSheet(red_button_showcase_style);

    index++;
    blinkTimer->start();
}

void MainWindow::endBlink() {
    ui->buttonBlue->setStyleSheet(blue_button_user_style);
    ui->buttonRed->setStyleSheet(red_button_user_style);

    delayTimer->start();
}

void MainWindow::releaseButtons() {
    ui->buttonRed->setEnabled(true);
    ui->buttonBlue->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

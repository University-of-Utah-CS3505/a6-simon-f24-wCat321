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
    blinkTimer->setInterval(blink_timer_time);
    delayTimer->setInterval(delay_timer_time);

    connect(blinkTimer, &QTimer::timeout, this, &MainWindow::stopBlink);
    connect(delayTimer, &QTimer::timeout, this, &MainWindow::startBlink);

    connect(ui->buttonBlue, &QPushButton::released, this, [this]() {game->getInput(true);});
    connect(ui->buttonRed, &QPushButton::released, this, [this]() {game->getInput(false);});
    connect(ui->buttonStart, &QPushButton::pressed, this, [this]() {ui->buttonStart->setEnabled(false); game->startGame();});

    connect(game, &Simon::sendButtonPattern, this, &MainWindow::loadPattern);
    connect(game, &Simon::endGame, this, &MainWindow::endGameBlink);

    lockButtons();
}

void MainWindow::loadPattern(const QVector<bool>* pattern) {
    blinkPattern = pattern;
    index = 0;
    lockButtons();
    stopBlink();
}

void MainWindow::displayBlink(const bool button) {
    if (button)
        ui->buttonBlue->setStyleSheet(blue_button_showcase_style);
    else
        ui->buttonRed->setStyleSheet(red_button_showcase_style);

}

void MainWindow::displayBlinkStop() {
    ui->buttonBlue->setStyleSheet(blue_button_user_style);
    ui->buttonRed->setStyleSheet(red_button_user_style);
}

void MainWindow::startBlink() {
    if (!blinkPattern || index >= blinkPattern->size()) { // If no pattern or if at the end of the list:
        return releaseButtons();
    }

    displayBlink(blinkPattern->at(index));

    index++;
    blinkTimer->start();
}

void MainWindow::stopBlink() {
    displayBlinkStop();

    delayTimer->start();
}

void MainWindow::endGameBlink() {
    lockButtons();

    for (int i = 0; i < end_game_blink_loop; i++) {\
        int start = i * (end_game_blink_start + end_game_blink_stop);
        int stop = start + end_game_blink_stop;

        QTimer::singleShot(start, this, [this]() {displayBlink(false); displayBlink(true);});
        QTimer::singleShot(stop, this, [this]() {displayBlinkStop();});
    }

    int end = end_game_blink_loop * (end_game_blink_start + end_game_blink_stop);
    QTimer::singleShot(end, this, [this]() {ui->buttonStart->setEnabled(true);});
}

void MainWindow::lockButtons() {
    ui->buttonRed->setEnabled(false);
    ui->buttonBlue->setEnabled(false);
}

void MainWindow::releaseButtons() {
    ui->buttonRed->setEnabled(true);
    ui->buttonBlue->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

    connect(blinkTimer, &QTimer::timeout, this, &MainWindow::stopBlink);
    connect(delayTimer, &QTimer::timeout, this, &MainWindow::startBlink);

    connect(ui->buttonBlue, &QPushButton::released, this, [this]() {game->getInput(true ^ gameSwap);}); // true XOR gameSwap : true unless gameSwap, then false
    connect(ui->buttonRed, &QPushButton::released, this, [this]() {game->getInput(false ^ gameSwap);}); // false XOR gameSwap : false unless gameSwap, then true
    connect(ui->buttonStart, &QPushButton::pressed, this, [this]() {ui->buttonStart->setEnabled(false); game->startGame();});

    connect(game, &Simon::sendButtonPattern, this, &MainWindow::loadPattern);
    connect(game, &Simon::endGame, this, &MainWindow::endGameBlink);

    lockButtons();
}

void MainWindow::loadPattern(const QVector<bool>* pattern) {
    blinkPattern = pattern;
    index = 0;
    gameSwap = ((blinkPattern->size() - Simon::initial_size) / game_swap_loop_timer ) % 2 == 1;
    lockButtons();
    stopBlink();
}

void MainWindow::displayBlink(const bool button) {
    if (gameSwap) {
        if (button)
            ui->buttonRed->setStyleSheet(blue_button_showcase_style);
        else
            ui->buttonBlue->setStyleSheet(red_button_showcase_style);
    }
    else {
        if (button)
            ui->buttonBlue->setStyleSheet(blue_button_showcase_style);
        else
            ui->buttonRed->setStyleSheet(red_button_showcase_style);

    }
}

void MainWindow::displayBlinkStop() {
    if (gameSwap) {
        ui->buttonBlue->setStyleSheet(red_button_user_style);
        ui->buttonRed->setStyleSheet(blue_button_user_style);
    } else {
        ui->buttonBlue->setStyleSheet(blue_button_user_style);
        ui->buttonRed->setStyleSheet(red_button_user_style);
    }
}

void MainWindow::startBlink() {
    if (!blinkPattern || index >= blinkPattern->size()) { // If no pattern or if at the end of the list:
        return releaseButtons();
    }

    displayBlink(blinkPattern->at(index));

    index++;
    int time = blink_timer_time - (blinkPattern->size() * blink_timer_decr);
    time = time < blink_timer_min ? blink_timer_min : time;
    blinkTimer->start(time);
}

void MainWindow::stopBlink() {
    displayBlinkStop();

    int time = delay_timer_time - (blinkPattern->size() * delay_timer_decr);
    time = time < delay_timer_min ? delay_timer_min : time;
    delayTimer->start(time);
}

void MainWindow::endGameBlink() {
    lockButtons();
    gameSwap = false;

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

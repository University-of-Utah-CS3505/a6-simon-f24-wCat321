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

    connect(ui->buttonLeft, &QPushButton::released, this, [this]() {pressButton(true ^ gameSwap);}); // true XOR gameSwap : true unless gameSwap, then false
    connect(ui->buttonRight, &QPushButton::released, this, [this]() {pressButton(false ^ gameSwap);}); // false XOR gameSwap : false unless gameSwap, then true

    connect(ui->buttonStart, &QPushButton::pressed, this, [this]() {ui->buttonStart->setEnabled(false); ui->progressBar->setVisible(false); game->startGame();});

    connect(game, &Simon::sendButtonPattern, this, &MainWindow::loadPattern);
    connect(game, &Simon::endGame, this, &MainWindow::endGameBlink);

    ui->progressBar->setVisible(false);

    lockButtons();
}

void MainWindow::loadPattern(const QVector<bool>* pattern) {
    blinkPattern = pattern;
    index = 0;
    ui->progressBar->setValue(blinkPattern->size() - 1);

    gameSwap = // Check the new pattern size to see if it makes it time for a game swap.
            (blinkPattern->size() - Simon::initial_size) // current size - initial size = number of rounds.
            / game_swap_loop_round_count // int division by round count to decide how many rounds between swaps
            % 2 == 1; // if even, it's starting mode, if odd it's "swapped" mode.
    // IE: every "game_swap_loop_round_count" number of rounds, the buttons will swap.

    ui->progressBar->setInvertedAppearance(gameSwap);

    lockButtons();
    stopBlink();
}

void MainWindow::displayBlink(const bool button) {
    if (gameSwap) { // gameSwap swaps the position of the red and blue buttons. It does this through modifying the style sheet
        if (button)
            ui->buttonRight->setStyleSheet(blue_button_showcase_style);
        else
            ui->buttonLeft->setStyleSheet(red_button_showcase_style);
    }
    else {
        if (button)
            ui->buttonLeft->setStyleSheet(blue_button_showcase_style);
        else
            ui->buttonRight->setStyleSheet(red_button_showcase_style);

    }
}

void MainWindow::displayBlinkStop() {
    if (gameSwap) {
        ui->buttonLeft->setStyleSheet(red_button_user_style);
        ui->buttonRight->setStyleSheet(blue_button_user_style);
    } else {
        ui->buttonLeft->setStyleSheet(blue_button_user_style);
        ui->buttonRight->setStyleSheet(red_button_user_style);
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

    ui->progressBar->setVisible(false);

    for (int i = 0; i < end_game_blink_loop; i++) {\
        int start = i * (end_game_blink_start + end_game_blink_stop); // calculates offset based on the number of iterations
        int stop = start + end_game_blink_stop;

        QTimer::singleShot(start, this, [this]() {displayBlink(false); displayBlink(true);});
        QTimer::singleShot(stop, this, [this]() {displayBlinkStop();});
    }

    int end = end_game_blink_loop * (end_game_blink_start + end_game_blink_stop); // calculates the time spent after everything in the for loop.
    QTimer::singleShot(end, this, [this]() {ui->buttonStart->setEnabled(true);}); // reenable the start button to play again.
}

void MainWindow::pressButton(const bool pressedButton) {
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    game->getInput(pressedButton);
}

void MainWindow::lockButtons() {
    ui->buttonRight->setEnabled(false);
    ui->buttonLeft->setEnabled(false);
}

void MainWindow::releaseButtons() {
    ui->progressBar->setVisible(true);
    ui->buttonRight->setEnabled(true);
    ui->buttonLeft->setEnabled(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(blinkPattern->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

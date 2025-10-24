#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include "Simon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const int blink_timer_time = 500;
    const int delay_timer_time = 400;
    const int blink_timer_decr = 30;
    const int delay_timer_decr = 20;
    const int blink_timer_min = 50;
    const int delay_timer_min = 50;

    const QString red_button_user_style = "QPushButton {background-color: darkred;} QPushButton::hover:!pressed {background-color: maroon;} QPushButton::pressed {background-color: red;}";
    const QString red_button_showcase_style = "QPushButton::disabled {background-color: red;}";
    const QString blue_button_user_style = "QPushButton {background-color: darkblue;} QPushButton::hover:!pressed {background-color: navy;} QPushButton::pressed {background-color: blue;} ";
    const QString blue_button_showcase_style = "QPushButton::disabled {background-color: blue;} ";

    const int end_game_blink_loop = 3;
    const int end_game_blink_start = 300;
    const int end_game_blink_stop = 300;

    const int game_swap_loop_timer = 5;

    int index = 0;
    bool gameSwap = false;

    Ui::MainWindow *ui;
    Simon *game;
    const QVector<bool>* blinkPattern = nullptr;

    QTimer* blinkTimer;
    QTimer* delayTimer;

    void displayBlink(const bool button);
    void displayBlinkStop();
    void lockButtons();
    void releaseButtons();

public slots:
    void loadPattern(const QVector<bool>* pattern);

private slots:
    void startBlink();
    void stopBlink();
    void endGameBlink();
};
#endif // MAINWINDOW_H

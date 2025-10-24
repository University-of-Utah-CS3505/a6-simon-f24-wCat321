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
    const QVector<bool> temp = {false, false, true, false, true};


    Ui::MainWindow *ui;
    Simon *game;

    int index = 0;
    const QVector<bool>* blinkPattern = nullptr;

    QTimer* blinkTimer;
    QTimer* delayTimer;
    const int blinkTimerTime = 300;
    const int delayTimerTime = 200;

    const QString red_button_user_style = "QPushButton {background-color: darkred;} QPushButton::hover:!pressed {background-color: maroon;} QPushButton::pressed {background-color: red;}";
    const QString red_button_showcase_style = "QPushButton::disabled {background-color: red;}";
    const QString blue_button_user_style = "QPushButton {background-color: darkblue;} QPushButton::hover:!pressed {background-color: navy;} QPushButton::pressed {background-color: blue;} ";
    const QString blue_button_showcase_style = "QPushButton::disabled {background-color: blue;}";

    void releaseButtons();

public slots:
    void startBlink(const QVector<bool>* pattern);

private slots:
    void nextBlink();
    void endBlink();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    Ui::MainWindow *ui;

    int index = 0;
    QTimer* blinkTimer;
    QTimer* delayTimer;

    const std::string red_button_user_style = "QPushButton {background-color: darkred;} QPushButton::hover:!pressed {background-color: maroon;} QPushButton::pressed {background-color: red;}";
    const std::string red_button_showcase_style = "QPushButton::disabled {background-color: red;}";
    const std::string blue_button_user_style = "QPushButton {background-color: darkblue;} QPushButton::hover:!pressed {background-color: navy;} QPushButton::pressed {background-color: blue;} ";
    const std::string blue_button_showcase_style = "QPushButton::disabled {background-color: blue;}";

private slots:
    void nextBlink();
    void endBlink();
};
#endif // MAINWINDOW_H

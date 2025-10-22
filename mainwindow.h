#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    const std::string red_button_user_style = "QPushButton {background-color: darkred;} QPushButton::hover:!pressed {background-color: maroon;} QPushButton::pressed {background-color: red;}";
    const std::string red_button_showcase_style = "QPushButton::disabled {background-color: red;}";
    const std::string blue_button_user_style = "QPushButton {background-color: darkblue;} QPushButton::hover:!pressed {background-color: navy;} QPushButton::pressed {background-color: blue;} ";
    const std::string blue_button_showcase_style = "QPushButton::disabled {background-color: blue;}";
};
#endif // MAINWINDOW_H

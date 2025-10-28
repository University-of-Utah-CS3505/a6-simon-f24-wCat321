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
    // The maximum time that the blink timer will run.
    const int blink_timer_time = 500;
    // The maximum time that the delay timer will run.
    const int delay_timer_time = 400;
    // The decrement amount for the blink timer.
    const int blink_timer_decr = 30;
    // The decrement amount for the delay timer.
    const int delay_timer_decr = 20;
    // The minimum time that the blink timer will run.
    const int blink_timer_min = 50;
    // The minimum time that the delay timer will run.
    const int delay_timer_min = 50;

    // StyleSheet for the red button when the user is in control.
    const QString red_button_user_style = "QPushButton {background-color: darkred;} QPushButton::hover:!pressed {background-color: maroon;} QPushButton::pressed {background-color: red;}";
    // Stylesheet for the red button when the computer wants to flash the button.
    const QString red_button_showcase_style = "QPushButton::disabled {background-color: red;}";
    // StyleSheet for the blue button when the user is in control.
    const QString blue_button_user_style = "QPushButton {background-color: darkblue;} QPushButton::hover:!pressed {background-color: navy;} QPushButton::pressed {background-color: blue;} ";
    // Stylesheet for the red button when the computer wants to flash the button.
    const QString blue_button_showcase_style = "QPushButton::disabled {background-color: blue;} ";

    // Number of blinks the end of game flash will do.
    const int end_game_blink_loop = 3;
    // Amount of time the end of game flash will go on.
    const int end_game_blink_start = 300;
    // Amount of time the end of game flash will be off.
    const int end_game_blink_stop = 300;

    // Number of rounds that go by before the "game swap" visual happens.
    const int game_swap_loop_round_count = 5;

    // current index of the blink pattern being displayed.
    int index = 0;
    /**
     * @brief boolean deciding if the "game swap" visual is happening.
     * Game swap is a mechanic where the buttons and button inputs swap, so
     * the left button goes from red to blue. Game swap also swaps the inputs,
     * so the "red" button will always flash when its a red button from the
     * game, but the position of the red button changes.
     */
    bool gameSwap = false;

    // ui.
    Ui::MainWindow *ui;
    // Simon game data.
    Simon *game;
    // Pointer to a vector that holds the blink pattern for the round.
    const QVector<bool>* blinkPattern = nullptr;

    // Timer for the blink interval.
    QTimer* blinkTimer;
    // Timer for the delay interval.
    QTimer* delayTimer;

    /**
     * @brief Displays the provided button bool as "blinking." This method
     * accounts for the "game swap" mechanic.
     * @param button | The button that will be displayed as "blinking,"
     * true for blue, false for red.
     */
    void displayBlink(const bool button);
    /**
     * @brief Resets all buttons from their "blinking" state, if they're in it.
     * This method accounts for the "game swap" mechanic.
     */
    void displayBlinkStop();
    /**
     * @brief Sends a signal that the button was pressed, and updates the
     * progress counter.
     * @param pressedButton | button value that was pressed.
     */
    void pressButton(const bool pressedButton);
    /**
     * @brief locks the red and blue buttons, setting them to disabled.
     */
    void lockButtons();
    /**
     * @brief unlocks the red and blue buttons, setting them to enabled.
     */
    void releaseButtons();

public slots:
    /**
     * @brief Takes a pattern and loads it into the UI system, then
     * starts the UI computer display system.
     * @param pattern | The pattern of buttons to display, in order.
     */
    void loadPattern(const QVector<bool>* pattern);

private slots:
    /**
     * @brief Reads the current index's button and displays it, then increases
     * the index. This slot also calls the timer to end the blink.
     */
    void startBlink();
    /**
     * @brief Stops blinking all buttons currently blinking. This slot also calls
     * the timer to start the next blink.
     */
    void stopBlink();
    /**
     * @brief Causes the end of game blinking, alongside resetting the UI for a new
     * game.
     */
    void endGameBlink();
};
#endif // MAINWINDOW_H

#ifndef SIMON_H
#define SIMON_H

#include <QObject>

class Simon : public QObject {

    Q_OBJECT

public:
    explicit Simon(QObject *parent = nullptr);
    ~Simon();

    /**
     * @brief The initial size of the game when starting a new game.
     */
    static const int initial_size = 3;


private:
    // Vector holding the current game's patterns.
    QVector<bool>* pattern = nullptr;
    // current index being checked in the pattern.
    int index = 0;

    /**
     * @brief Runs the next round of the game, adding a new pattern
     * to the pattern vector and resetting the index.
     */
    void nextRound();
    /**
     * @brief Adds a random true or false value into the pattern
     * vector.
     */
    void addToPattern();
public slots:
    /**
     * @brief Starts the game, ensuring the pattern vector is empty
     * and the index is reset to 0.
     */
    void startGame();
    /**
     * @brief Receives a pattern input and compares it to the current
     * index value. Continues the round or moves to the next round if
     * the values match. Otherwise, ends the game.
     * @param inputPattern | Pattern passed to compare.
     */
    void getInput(bool inputPattern);

signals:
    /**
     * @brief Sends out the pattern vector to be displayed by a UI.
     * @param pattern | constant pointer to the pattern vector.
     */
    void sendButtonPattern(const QVector<bool>* pattern);
    /**
     * @brief Signal emitted when the game ends due to an incorrect input.
     */
    void endGame();
};




#endif // SIMON_H

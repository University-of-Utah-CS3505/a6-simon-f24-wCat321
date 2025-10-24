#include "Simon.h"
#include <QRandomGenerator>


Simon::Simon(QObject *parent) : QObject{parent} {}

void Simon::addToPattern() {
    bool value = QRandomGenerator::global()->bounded(2) == 0;
    pattern->append(value);
}

void Simon::startGame() {
    delete pattern;
    pattern = new QVector<bool>(); // clears and resets pattern to be empty.
    index = 0;

    for (int i = 0; i < initial_size; i++) {
        addToPattern();
    }

    emit sendButtonPattern(pattern);
}

void Simon::nextRound() {
    addToPattern();
    index = 0;
    emit sendButtonPattern(pattern);
}

void Simon::getInput(bool inputPattern) {
    if (!pattern) return; // nullchecking, shouldn't get ran.

    if (index < pattern->size() && pattern->at(index) == inputPattern) { // check to ensure index isn't beyond pattern size and that the button press is equal to the current index value.
        index ++;
        if (index == pattern->size()) // if at the end of the pattern, go to next round.
            nextRound();
    } else emit endGame();
}

Simon::~Simon() {
    delete pattern;
}

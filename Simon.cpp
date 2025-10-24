#include "Simon.h"
#include <QRandomGenerator>


Simon::Simon(QObject *parent) : QObject{parent} {


}

void Simon::addToPattern() {
    bool value = QRandomGenerator::global()->bounded(2) == 0;
    pattern->append(value);
}

void Simon::startGame() {
    delete pattern;
    pattern = new QVector<bool>();
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

void Simon::getInput(bool button) {
    if (!pattern) return;

    if (index < pattern->size() && pattern->at(index) == button) {
        index ++;
        if (index == pattern->size())
            nextRound();
    } else emit endGame();
}

Simon::~Simon() {
    delete pattern;
}

#ifndef SIMON_H
#define SIMON_H

#include <QObject>

class Simon : public QObject {

    Q_OBJECT

public:
    explicit Simon(QObject *parent = nullptr);
    ~Simon();

    static const int initial_size = 3;


private:
    QVector<bool>* pattern = nullptr;
    int index = 0;

    void nextRound();
    void addToPattern();
public slots:
    void startGame();
    void getInput(bool button);

signals:
    void sendButtonPattern(const QVector<bool>* pattern);
    void endGame();
};




#endif // SIMON_H

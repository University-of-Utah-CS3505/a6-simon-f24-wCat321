#ifndef SIMON_H
#define SIMON_H

#include <QObject>

class Simon : public QObject {

    Q_OBJECT

public:
    explicit Simon(QObject *parent = nullptr);

public slots:
    void getInput(bool button);
};




#endif // SIMON_H

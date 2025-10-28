/**
 * William Yount
 * wCat321
 *
 * The creative element of my game is the "game swap" feature,
 * where every few rounds, set to 5 currently, the positions of
 * the blue and red buttons swap. this happens every 5 rounds.
 * The colored button needed to press does not swap, if the pattern
 * starts with "blue blue red" you will always need to press
 * "blue blue red" even if the blue button is now on the other
 * side.
**/
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "A6_Simon_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}

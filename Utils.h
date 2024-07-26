#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMessageBox>
#include <QApplication>
#include <QTime>


class Utils
{
public:
    static void throwError(QString errorStr);
    static void showInfo(QString infoStr);
    static void showCritical(QString errorStr);
    static void errorExit(QString errorStr);
    static QString formatSeconds(int totalSeconds);
};

#endif // UTILS_H

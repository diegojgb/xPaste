#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMessageBox>
#include <QTime>


class Utils
{
public:
    static void throwError(QString errorStr);
    static void showInfo(QString infoStr);
    static void showCritical(QString errorStr);
    static QString formatSeconds(int total_seconds);
};

#endif // UTILS_H

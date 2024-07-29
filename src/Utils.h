#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMessageBox>
#include <QApplication>
#include <QTime>

#include <iostream>
#include <Windows.h>


// Declare the RtlGetVersion function manually
extern "C" NTSTATUS NTAPI RtlGetVersion(PRTL_OSVERSIONINFOW lpVersionInformation);

class Utils
{
public:
    static void throwError(QString errorStr);
    static void showInfo(QString infoStr);
    static void showCritical(QString errorStr);
    static void errorExit(QString errorStr);
    static QString formatSeconds(int totalSeconds);
    static bool isWindows10();
};

#endif // UTILS_H

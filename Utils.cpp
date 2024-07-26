#include "Utils.h"


void Utils::showCritical(QString errorStr)
{
    QMessageBox::critical(nullptr, "WatchLog", errorStr);
}

QString Utils::formatSeconds(int totalSeconds) {
    QTime time(0, 0, 0);

    time = time.addSecs(totalSeconds);

    return time.toString();
}

void Utils::throwError(QString errorStr)
{
    showCritical(errorStr);
    throw std::runtime_error(errorStr.toStdString());
}

void Utils::showInfo(QString infoStr)
{
    QMessageBox::information(nullptr, "WatchLog", infoStr);
}

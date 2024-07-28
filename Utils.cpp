#include "Utils.h"


void Utils::showCritical(QString errorStr)
{
    QMessageBox::critical(nullptr, "WatchLog", errorStr);
}

QString Utils::formatSeconds(int totalSeconds)
{
    QTime time(0, 0, 0);

    time = time.addSecs(totalSeconds);

    return time.toString();
}

bool Utils::isWindows10()
{
    RTL_OSVERSIONINFOW osInfo = {0};
    osInfo.dwOSVersionInfoSize = sizeof(osInfo);

    if (RtlGetVersion(&osInfo) != 0)
    {
        std::cerr << "Failed to get OS version information." << std::endl;
        return false;
    }

    return osInfo.dwBuildNumber < 22000;
}

void Utils::errorExit(QString errorStr)
{
    showCritical(errorStr);
    qApp->exit(1);
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

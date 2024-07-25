#include "Manager.h"

Manager::Manager(QObject *parent)
    : QObject{parent}
{}

Settings* Manager::settings()
{
    return &m_settings;
}

void Manager::initTrayIcon(QObject *parent, QQuickWindow *rootWindow)
{
    if (m_trayIcon != nullptr)
        Utils::throwError("Tray icon can only be initialized once.");

    m_trayIcon = new TrayIcon(parent, rootWindow);
}

#include "Manager.h"

Manager::Manager(QObject *parent)
    : QObject{parent}
{
    connect(&m_settings, &Settings::changeWindowTitle, this, &Manager::onChangeWindowTitle);
}

Settings* Manager::settings()
{
    return &m_settings;
}

void Manager::initTrayIcon(QObject *parent, QQuickWindow *rootWindow)
{
    if (m_trayIcon != nullptr)
        Utils::errorExit("[Manager]: Tray icon can only be initialized once.");

    m_trayIcon = new TrayIcon(parent, rootWindow, m_settings.singleClick());

    connect(&m_settings, &Settings::singleClickChangedOverload, m_trayIcon, &TrayIcon::onSingleClickChanged);
}

void Manager::setMainWindow(QQuickWindow *window)
{
    m_mainWindow = window;
}

void Manager::onChangeWindowTitle(const QString &windowTitle)
{
    m_mainWindow->setTitle(windowTitle);
}

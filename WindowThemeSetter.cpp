#include "WindowThemeSetter.h"
#include <QGuiApplication>
#include <QQuickWindow>
#include <dwmapi.h>

WindowThemeSetter::WindowThemeSetter(QObject *parent, BOOL init_dark)
    : QObject{parent}, m_darkEnabled(init_dark)
{
    connect(this, &WindowThemeSetter::darkEnabledChanged, this, &WindowThemeSetter::changeWindowTheme);
}

bool WindowThemeSetter::darkEnabled() const
{
    return m_darkEnabled;
}

void WindowThemeSetter::setDarkEnabled(bool newDarkEnabled)
{
    if (m_darkEnabled == newDarkEnabled)
        return;
    m_darkEnabled = newDarkEnabled;

    emit darkEnabledChanged();
}

void WindowThemeSetter::changeWindowTheme()
{
    if (windowHandle == 0)
        if (QWindow* window = QGuiApplication::allWindows().at(0))
            windowHandle = (HWND)window->winId();

    if (windowHandle != 0) {
        BOOL success = SUCCEEDED(DwmSetWindowAttribute(windowHandle, 20, &m_darkEnabled, sizeof(m_darkEnabled)));

        if (!success)
            DwmSetWindowAttribute(windowHandle, 19, &m_darkEnabled, sizeof(m_darkEnabled));
    }
}

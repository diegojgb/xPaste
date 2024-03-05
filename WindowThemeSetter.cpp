#include "WindowThemeSetter.h"
#include <QGuiApplication>
#include <QQuickWindow>
#include <dwmapi.h>


WindowThemeSetter::WindowThemeSetter(QObject *parent, BOOL darkEnabled)
    : QObject{parent}, m_darkEnabled(darkEnabled)
{
    connect(this, &WindowThemeSetter::darkEnabledChanged, this, &WindowThemeSetter::updateWindowTheme);

    m_themeToColor[true] = 0x00202020;
    m_themeToColor[false] = 0x00F3F3F3;
}

void WindowThemeSetter::updateWindowTheme()
{
    if (m_windowHandle == 0)
        if (QWindow* window = QGuiApplication::allWindows().at(0))
            m_windowHandle = (HWND)window->winId();

    if (m_windowHandle != 0) {
        // DwmSetWindowAttribute(m_windowHandle, 35, &m_themeToColor[m_darkEnabled], sizeof(m_themeToColor[m_darkEnabled])); // Windows 11 only

        if (!SUCCEEDED(DwmSetWindowAttribute(m_windowHandle, 20, &m_darkEnabled, sizeof(m_darkEnabled)))) // Windows 10 20H1+
            DwmSetWindowAttribute(m_windowHandle, 19, &m_darkEnabled, sizeof(m_darkEnabled)); // Windows 10 before 20H1
    }
}

BOOL WindowThemeSetter::darkEnabled() const
{
    return m_darkEnabled;
}

void WindowThemeSetter::setDarkEnabled(BOOL newDarkEnabled)
{
    if (m_darkEnabled == newDarkEnabled)
        return;

    m_darkEnabled = newDarkEnabled;

    emit darkEnabledChanged();
}

#include "WindowThemeSetter.h"

#include <QGuiApplication>
#include <QQuickWindow>

#include <dwmapi.h>


WindowThemeSetter::WindowThemeSetter(QObject *parent, BOOL darkEnabled)
    : QObject{parent}
    , m_qSettings{QSettings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat)}
    , m_darkEnabled(m_qSettings.value("DarkThemeEnabled", darkEnabled).toBool())
{
    connect(this, &WindowThemeSetter::darkEnabledChanged, this, &WindowThemeSetter::updateWindowTheme);
}

void WindowThemeSetter::updateWindowTheme()
{
    if (m_windowHandle == 0)
        if (QWindow* window = QGuiApplication::allWindows().at(0))
            m_windowHandle = (HWND)window->winId();

    if (m_windowHandle != 0) {
        if (!SUCCEEDED(DwmSetWindowAttribute(m_windowHandle, 20, &m_darkEnabled, sizeof(m_darkEnabled)))) // Windows 10 20H1+
            DwmSetWindowAttribute(m_windowHandle, 19, &m_darkEnabled, sizeof(m_darkEnabled)); // Windows 10 before 20H1
    }

    if (Utils::isWindows10())
        redraw();
}

// Redraw the Window. For Windows 10, which doesn't automatically change the title bar color to dark upon change.
// It's a hacky solution, forces a redraw by resizing the window.
void WindowThemeSetter::redraw()
{
    RECT rect;

    if (!GetWindowRect(m_windowHandle, &rect))
        return;

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    SetWindowPos(m_windowHandle, 0, 0, 0, width-1, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
    SetWindowPos(m_windowHandle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
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

    m_qSettings.setValue("DarkThemeEnabled", newDarkEnabled);

    emit darkEnabledChanged();
}

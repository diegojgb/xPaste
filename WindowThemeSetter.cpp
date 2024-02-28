#include "WindowThemeSetter.h"
#include <QQuickWindow>
#include <dwmapi.h>

WindowThemeSetter::WindowThemeSetter(QObject *parent, QQmlApplicationEngine *engine, BOOL init_dark)
    : QObject{parent}, engine(engine), m_darkEnabled(init_dark)
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
        if(QWindow* window = qobject_cast<QWindow*>(engine->rootObjects().at(0)))
            windowHandle = (HWND)window->winId();

    if (windowHandle != 0)
        DwmSetWindowAttribute(windowHandle, 20, &m_darkEnabled, sizeof(m_darkEnabled));
}

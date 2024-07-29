#ifndef WINDOWTHEMESETTER_H
#define WINDOWTHEMESETTER_H

#include "Utils.h"

#include <QObject>
#include <QSettings>

#include <dwmapi.h>


class WindowThemeSetter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BOOL darkEnabled READ darkEnabled WRITE setDarkEnabled NOTIFY darkEnabledChanged FINAL)

public:
    explicit WindowThemeSetter(QObject *parent, BOOL darkEnabled);

    BOOL darkEnabled() const;
    void setDarkEnabled(BOOL newDarkEnabled);

public slots:
    void updateWindowTheme();

signals:
    void darkEnabledChanged();

private:
    QSettings m_qSettings;
    BOOL m_darkEnabled;
    HWND m_windowHandle = 0;
    void redraw();
};

#endif // WINDOWTHEMESETTER_H

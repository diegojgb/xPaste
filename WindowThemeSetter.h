#ifndef WINDOWTHEMESETTER_H
#define WINDOWTHEMESETTER_H

#include <QObject>
#include <dwmapi.h>


class WindowThemeSetter: public QObject
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
    BOOL m_darkEnabled;
    HWND m_windowHandle = 0;
    std::map<BOOL, COLORREF> m_themeToColor;
};

#endif // WINDOWTHEMESETTER_H

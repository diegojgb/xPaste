#ifndef WINDOWTHEMESETTER_H
#define WINDOWTHEMESETTER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <dwmapi.h>

class WindowThemeSetter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool darkEnabled READ darkEnabled WRITE setDarkEnabled NOTIFY darkEnabledChanged FINAL)

public:
    explicit WindowThemeSetter(QObject *parent, QQmlApplicationEngine *engine = nullptr, BOOL init_dark = true);

    bool darkEnabled() const;
    void setDarkEnabled(bool newDarkEnabled);

    QQmlApplicationEngine *engine;

public slots:
    void changeWindowTheme();

signals:
    void darkEnabledChanged();

private:
    BOOL m_darkEnabled;
    HWND windowHandle = 0;
};

#endif // WINDOWTHEMESETTER_H

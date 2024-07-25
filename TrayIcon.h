#ifndef TRAYICON_H
#define TRAYICON_H

#include "Utils.h"
#include "ToastHandler.h"
#include "Registry.h"
#include "wintoastlib.h"

#include <QObject>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QQuickWindow>

#include <Windows.h>


class TrayIcon: public QObject
{
    Q_OBJECT

public:
    explicit TrayIcon(QObject* parent, QQuickWindow *root);

public slots:
    static void sendNotification(const WinToastTemplate& templ);
    static void sendNotification(const std::wstring title, const std::wstring subtitle);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void bringToTop();

signals:
    void singleClicked();
    void doubleClicked();

private:
    QQuickWindow *m_rootWindow{};
    HWND m_hwnd;
    QSystemTrayIcon* m_trayIcon{};

    QMenu* createMenu();
    void initWinToast();
};

#endif // TRAYICON_H

#ifndef MANAGER_H
#define MANAGER_H

#include "HookHandler.h"
#include "Settings.h"
#include "TrayIcon.h"

#include <QObject>
#include <QQuickWindow>


class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Settings *settings READ settings CONSTANT)
    Q_PROPERTY(bool isWindows10 READ isWindows10 CONSTANT)

public:
    explicit Manager(QObject *parent = nullptr);

    Settings *settings();
    bool isWindows10() const;

    void initTrayIcon(QObject *parent, QQuickWindow *root);
    void setMainWindow(QQuickWindow *window);
    bool getPasteHotkeyEditing();
    bool getToggleHotkeyEditing();
    int pressedModsCount();

    Q_INVOKABLE void setPasteHotkeyEditing(bool editing);
    Q_INVOKABLE void setToggleHotkeyEditing(bool editing);
    Q_INVOKABLE int getQModifiers();

public slots:
    void onChangeWindowTitle(const QString &windowTitle);

private:
    static bool pasteHotkeyEditing;
    static bool toggleHotkeyEditing;

    QQuickWindow *m_mainWindow{};
    Settings m_settings;
    TrayIcon *m_trayIcon{};
    HookHandler m_hookHandler;
    const bool m_isWindows10;
};

extern Manager *g_manager;

#endif // MANAGER_H

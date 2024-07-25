#ifndef MANAGER_H
#define MANAGER_H

#include "Settings.h"
#include "TrayIcon.h"

#include <QObject>
#include <QQuickWindow>


class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Settings* settings READ settings CONSTANT)

public:
    explicit Manager(QObject *parent = nullptr);

    Settings* settings();
    void initTrayIcon(QObject* parent, QQuickWindow* root);

private:
    Settings m_settings;
    TrayIcon* m_trayIcon{};
};

#endif // MANAGER_H

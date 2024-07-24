#ifndef MANAGER_H
#define MANAGER_H

#include "Settings.h"

#include <QObject>


class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Settings* settings READ settings CONSTANT FINAL)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged FINAL)

public:
    explicit Manager(QObject *parent = nullptr);

    Settings* settings();

    bool active() const;
    void setActive(bool newActive);

signals:
    void activeChanged();

private:
    Settings m_settings;
    bool m_active = false;
};

#endif // MANAGER_H

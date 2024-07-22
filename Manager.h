#ifndef MANAGER_H
#define MANAGER_H

#include "Settings.h"

#include <QObject>


class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Settings* settings READ settings CONSTANT)

public:
    explicit Manager(QObject *parent = nullptr);

    Settings* settings();

private:
    Settings m_settings;
};

#endif // MANAGER_H

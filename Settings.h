#ifndef SETTINGS_H
#define SETTINGS_H

#include "Hotkey.h"

#include <QObject>
#include <Windows.h>
#include <QDebug>


class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Hotkey* pasteHotkey READ pasteHotkey CONSTANT FINAL)

public:
    explicit Settings(QObject *parent = nullptr);

    Hotkey* pasteHotkey();

private:
    Hotkey m_pasteHotkey;
};

#endif // SETTINGS_H

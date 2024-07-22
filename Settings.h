#ifndef SETTINGS_H
#define SETTINGS_H

#include "Hotkey.h"

#include <QObject>
#include <Windows.h>
#include <QDebug>


class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString hotkeyStr READ hotkeyStr NOTIFY hotkeyStrChanged FINAL)

public:
    explicit Settings(QObject *parent = nullptr);

    QString hotkeyStr() const;

    Q_INVOKABLE void setHotkey(const int key, const int modifiers, quint32 nativeScanCode);

signals:
    void hotkeyStrChanged();

private:
    Hotkey m_hotkey;
};

#endif // SETTINGS_H

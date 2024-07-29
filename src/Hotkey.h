#ifndef HOTKEY_H
#define HOTKEY_H

#include "Utils.h"

#include <QObject>
#include <QKeySequence>
#include <QSettings>

#include <iostream>
#include <Windows.h>


class Hotkey : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString string READ string NOTIFY hotkeyChanged FINAL)

public:
    explicit Hotkey(QObject *parent,
                    QString name,
                    QSettings &m_qSettings);

    QString string() const;

    void setVkCode(DWORD vkCode);
    DWORD getVkCode();
    int getModifiers();
    bool isEmpty() const;

    Q_INVOKABLE bool setQKey(const int key, const int modifiers);

signals:
    void hotkeyChanged();

private:
    QSettings &m_qSettings;
    QString m_name;
    int m_qKey{};
    int m_qModifiers{};
    DWORD m_vkCode;
    bool m_isEmpty = true;

    static QString keyToString(const int key, const int modifiers);
    static bool isKeyUnknown(const int key);

    QString toString() const;
    void saveQKey();
};

#endif // HOTKEY_H

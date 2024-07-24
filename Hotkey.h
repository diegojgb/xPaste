#ifndef HOTKEY_H
#define HOTKEY_H

#include "Utils.h"

#include <QObject>
#include <QKeySequence>
#include <QDebug>

#include <iostream>
#include <Windows.h>


class Hotkey : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString string READ string NOTIFY hotkeyChanged FINAL)

public:
    static constexpr int PasteHotkeyID = 1000;
    static constexpr int ToggleHotkeyID = 1001;

    explicit Hotkey(QObject *parent,
                    const int ID,
                    quint32 defKey = 0x56, // 'V' char key-code.
                    quint32 defMods = MOD_CONTROL);

    QString string() const;
    bool isEmpty() const;

    bool registerHotkey();
    bool unregisterHotkey();

    Q_INVOKABLE bool setHotkey(const int key, const int modifiers, quint32 nativeScanCode);

signals:
    void hotkeyChanged();

private:
    QString m_string;
    int m_qKey{};
    int m_qModifiers{};
    quint32 m_nativeScanCode{};
    bool m_isEmpty = true;
    bool m_isRegistered = false;
    const int ID{};
    quint32 m_defKey;
    quint32 m_defMods;

    static quint32 scanCodeToVk(quint32 nativeScanCode);
    static quint32 toNativeModifiers(const int modifiers);
    static QString keyToString(const int key, const int modifiers);
    static bool isKeyUnknown(const int key);

    QString toString() const;
    quint32 getWinVk() const;
    quint32 getWinModifiers() const;
    bool registerDefault();
};

#endif // HOTKEY_H

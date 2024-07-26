#ifndef HOTKEY_H
#define HOTKEY_H

#include "Utils.h"

#include <QObject>
#include <QKeySequence>
#include <QDebug>
#include <QSettings>

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
                    QString name,
                    const int ID,
                    QSettings &m_qSettings,
                    quint32 defKey = 0,
                    quint32 defMods = 0);

    QString string() const;
    bool isEmpty() const;

    bool registerHotkey(bool regDefault = false);
    bool unregisterHotkey();
    bool registerDefault();

    Q_INVOKABLE bool setHotkey(const int key, const int modifiers,
                               quint32 nativeScanCode, bool reg = false);

signals:
    void hotkeyChanged();

private:
    QString m_name;
    QSettings &m_qSettings;
    QString m_string;
    int m_qKey{};
    int m_qModifiers{};
    quint32 m_nativeScanCode{};
    bool m_isEmpty = true;
    bool m_isRegistered = false;
    const int ID{};
    quint32 m_defKey{};
    quint32 m_defMods{};

    static quint32 scanCodeToVk(quint32 nativeScanCode);
    static quint32 toNativeModifiers(const int modifiers);
    static QString keyToString(const int key, const int modifiers);
    static bool isKeyUnknown(const int key);

    QString toString() const;
    quint32 getWinVk() const;
    quint32 getWinModifiers() const;
    void saveHotkey();
};

#endif // HOTKEY_H

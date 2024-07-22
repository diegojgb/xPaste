#ifndef HOTKEY_H
#define HOTKEY_H

#include <QObject>
#include <QKeySequence>
#include <QDebug>

#include <Windows.h>


class Hotkey : public QObject
{
    Q_OBJECT

public:
    explicit Hotkey(QObject *parent = nullptr);

    void setHotkey(const int key, const int modifiers, quint32 nativeScanCode);
    QString getHotkeyStr() const;

signals:
    void hotkeyChanged();

private:
    int m_qKey{};
    int m_qModifiers{};
    quint32 m_nativeScanCode{};
    bool m_isEmpty = true;

    static quint32 toNativeModifiers(const int modifiers);
    static QString keyToString(const int key, const int modifiers);
    static bool isKeyUnknown(const int key);
};

#endif // HOTKEY_H

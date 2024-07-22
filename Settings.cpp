#include "Settings.h"


Settings::Settings(QObject *parent)
    : QObject{parent}
{
    connect(&m_hotkey, &Hotkey::hotkeyChanged, this, &Settings::hotkeyStrChanged);
}

void Settings::setHotkey(const int key, const int modifiers, quint32 nativeScanCode)
{
    m_hotkey.setHotkey(key, modifiers, nativeScanCode);
}

QString Settings::hotkeyStr() const
{
    return m_hotkey.getHotkeyStr();
}

#include "Hotkey.h"


Hotkey::Hotkey(QObject *parent)
    : QObject{parent}
{}

void Hotkey::setHotkey(const int key, const int modifiers, quint32 nativeScanCode)
{
    if (isKeyUnknown(key))
        return;

    m_qKey = key;
    m_qModifiers = modifiers;
    m_nativeScanCode = nativeScanCode;

    m_isEmpty = false;

    emit hotkeyChanged();
}

QString Hotkey::getHotkeyStr() const
{
    if (m_isEmpty)
        return "<not set>";

    return keyToString(m_qKey, m_qModifiers);
}

bool Hotkey::isKeyUnknown(const int key)
{
    // Range of weird key codes that appear when modifiers
    // are pressed without accompanying standard keys
    constexpr int RANGE_BOTTOM = 16777248;
    constexpr int RANGE_TOP = 16777251;

    if (RANGE_BOTTOM <= key && key <= RANGE_TOP)
        return true;

    if (key == Qt::Key_unknown)
        return true;

    return false;
}

QString Hotkey::keyToString(const int key, const int modifiers)
{
    if (isKeyUnknown(key))
        return "";

    QString str = QKeySequence(key | modifiers).toString().toUpper();

    if (modifiers & Qt::MetaModifier)
        str = str.replace("META", "WIN");

    return str;
}

quint32 Hotkey::toNativeModifiers(const int modifiers)
{
    quint32 mods = 0;

    if (modifiers & Qt::ShiftModifier)
        mods |= MOD_SHIFT;
    if (modifiers & Qt::ControlModifier)
        mods |= MOD_CONTROL;
    if (modifiers & Qt::AltModifier)
        mods |= MOD_ALT;
    if (modifiers & Qt::MetaModifier)
        mods |= MOD_WIN;

    return mods;
}

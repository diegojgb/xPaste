#include "Hotkey.h"

Hotkey::Hotkey(QObject *parent, QString name, QSettings &m_qSettings)
    : QObject{parent}
    , m_name{name}
    , m_qSettings{m_qSettings}
{
    setQKey(m_qSettings.value(m_name + "QKey", 0).toInt(),
            m_qSettings.value(m_name + "QModifiers", 0).toInt());

    setVkCode(m_qSettings.value(m_name + "vkCode", 0).toUInt());
}

bool Hotkey::setQKey(const int key, const int modifiers)
{
    if (isKeyUnknown(key) || key == 0)
        return false;

    m_qKey = key;
    m_qModifiers = modifiers;

    m_isEmpty = false;
    saveQKey();

    emit hotkeyChanged();

    return true;
}

QString Hotkey::toString() const
{
    if (m_isEmpty)
        return "<not set>";

    return keyToString(m_qKey, m_qModifiers);
}

void Hotkey::saveQKey()
{
    m_qSettings.setValue(m_name + "QKey", m_qKey);
    m_qSettings.setValue(m_name + "QModifiers", m_qModifiers);
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

QString Hotkey::string() const
{
    return toString();
}

void Hotkey::setVkCode(DWORD vkCode)
{
    m_vkCode = vkCode;

    m_qSettings.setValue(m_name + "vkCode", (unsigned int)m_vkCode);
}

DWORD Hotkey::getVkCode()
{
    return m_vkCode;
}

int Hotkey::getModifiers()
{
    return m_qModifiers;
}

bool Hotkey::isEmpty() const
{
    return m_isEmpty;
}

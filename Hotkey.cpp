#include "Hotkey.h"


Hotkey::Hotkey(QObject *parent, QString name, int ID, QSettings &m_qSettings, quint32 defKey, quint32 defMods)
    : QObject{parent}
    , m_name{name}
    , ID{ID}
    , m_defKey{defKey}
    , m_defMods{defMods}
    , m_qSettings{m_qSettings}
{
    setHotkey(m_qSettings.value(m_name + "QKey", 0).toInt(),
              m_qSettings.value(m_name + "QModifiers", 0).toInt(),
              m_qSettings.value(m_name + "NativeScanCode", 0).toUInt(),
              m_qSettings.value(m_name + "PasteActive", false).toBool());
}

bool Hotkey::setHotkey(const int key, const int modifiers, quint32 nativeScanCode, bool reg)
{
    if (isKeyUnknown(key) || key == 0)
        return false;

    m_qKey = key;
    m_qModifiers = modifiers;
    m_nativeScanCode = nativeScanCode;

    m_isEmpty = false;

    if (m_isRegistered) {
        unregisterHotkey();
        registerHotkey();
    }

    if (!m_isRegistered && reg)
        registerHotkey();

    saveHotkey();
    emit hotkeyChanged();

    return true;
}

QString Hotkey::toString() const
{
    if (m_isEmpty)
        return "<not set>";

    return keyToString(m_qKey, m_qModifiers);
}

bool Hotkey::registerHotkey(bool regDefault)
{
    if (m_isRegistered)
        return false;

    if (regDefault)
        return registerDefault();

    if (m_isEmpty)
        return false;

    BOOL success = RegisterHotKey(NULL,
                                  ID,
                                  getWinModifiers() + MOD_NOREPEAT,
                                  getWinVk());

    if (!success) {
        Utils::showCritical("Failed to register hotkey.");
        return false;
    }

    m_isRegistered = true;

    return true;
}

bool Hotkey::unregisterHotkey()
{
    if (!m_isRegistered)
        return false;

    BOOL success = UnregisterHotKey(NULL, ID);

    if (!success) {
        Utils::showCritical("Failed to unregister hotkey.");
        return false;
    }

    m_isRegistered = false;

    return true;
}

bool Hotkey::registerDefault()
{
    if (m_isRegistered || m_defKey == 0)
        return false;

    BOOL success = RegisterHotKey(NULL, ID, m_defMods, m_defKey);

    if (!success) {
        Utils::showCritical("Failed to register hotkey.");
        return false;
    }

    m_isRegistered = true;

    return true;
}

void Hotkey::saveHotkey()
{
    m_qSettings.setValue(m_name + "QKey", m_qKey);
    m_qSettings.setValue(m_name + "QModifiers", m_qModifiers);
    m_qSettings.setValue(m_name + "NativeScanCode", m_nativeScanCode);
}

quint32 Hotkey::getWinModifiers() const
{
    return toNativeModifiers(m_qModifiers);
}

quint32 Hotkey::getWinVk() const
{
    return scanCodeToVk(m_nativeScanCode);
}

quint32 Hotkey::scanCodeToVk(quint32 nativeScanCode)
{
    return MapVirtualKeyA(nativeScanCode, MAPVK_VSC_TO_VK);
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

QString Hotkey::string() const
{
    return toString();
}

bool Hotkey::isEmpty() const
{
    return m_isEmpty;
}

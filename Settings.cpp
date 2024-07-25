#include "Settings.h"


Settings::Settings(QObject *parent)
    : QObject{parent}
    , m_pasteHotkey{this, Hotkey::PasteHotkeyID, 0x56, MOD_CONTROL} // 0x56 == 'V'
    , m_toggleHotkey{this, Hotkey::ToggleHotkeyID}
{}

Hotkey* Settings::pasteHotkey()
{
    return &m_pasteHotkey;
}

Hotkey *Settings::toggleHotkey()
{
    return &m_toggleHotkey;
}

void Settings::togglePasteActive()
{   
    setPasteActive(!m_pasteActive);

    QString path = QCoreApplication::applicationDirPath()
        + (m_pasteActive ? "/assets/green-check.png" : "/assets/red-cross.png");

    if (m_pasteActive)
        TrayIcon::sendNotification(L"Pasting ON",
                                   L"Simulated pasting is now turned on.",
                                   path.toStdWString());
    else
        TrayIcon::sendNotification(L"Pasting OFF",
                                   L"Simulated pasting is now turned off.",
                                   path.toStdWString());
}

bool Settings::pasteActive() const
{
    return m_pasteActive;
}

void Settings::setPasteActive(bool newPasteActive)
{
    if (m_pasteActive == newPasteActive)
        return;

    m_pasteActive = newPasteActive;

    bool registerDefault = !m_customHotkeyEnabled;

    if (newPasteActive)
        m_pasteHotkey.registerHotkey(registerDefault);
    else
        m_pasteHotkey.unregisterHotkey();

    emit pasteActiveChanged();
}

bool Settings::toggleActive() const
{
    return m_toggleActive;
}

void Settings::setToggleActive(bool newToggleActive)
{
    if (m_toggleActive == newToggleActive)
        return;

    m_toggleActive = newToggleActive;

    if (newToggleActive)
        m_toggleHotkey.registerHotkey();
    else
        m_toggleHotkey.unregisterHotkey();

    emit toggleActiveChanged();
}

bool Settings::customHotkeyEnabled() const
{
    return m_customHotkeyEnabled;
}

void Settings::setCustomHotkeyEnabled(bool newCustomHotkeyEnabled)
{
    if (m_customHotkeyEnabled == newCustomHotkeyEnabled)
        return;

    m_customHotkeyEnabled = newCustomHotkeyEnabled;

    if (newCustomHotkeyEnabled) {
        if (m_pasteActive) {
            m_pasteHotkey.unregisterHotkey();

            if (!m_pasteHotkey.isEmpty())
                m_pasteHotkey.registerHotkey();
        }
    } else {
        if (m_pasteActive) {
            m_pasteHotkey.unregisterHotkey();
            m_pasteHotkey.registerDefault();
        }
    }

    emit customHotkeyEnabledChanged();
}

#include "Settings.h"


Settings::Settings(QObject *parent)
    : QObject{parent}
    , m_pasteHotkey{this, Hotkey::PasteHotkeyID, 0x56, MOD_CONTROL} // 0x56 == 'V'
    , m_toggleHotkey{this, Hotkey::ToggleHotkeyID}
{
    connect(&m_timer, &QTimer::timeout, this, &Settings::timerUpdateTitle);
}

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

    if (m_disableToggleToasts)
        return;

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

void Settings::timerUpdateTitle()
{
    if (m_remainingTime > 0) {
        emit changeWindowTitle("xPaste - " + Utils::formatSeconds(m_remainingTime));
    } else if (m_remainingTime == 0) {
        emit changeWindowTitle("Time is up!");
        setPasteActive(false);
        if (!m_disableTimeToast)
            TrayIcon::sendNotification(L"Time's up!",
                                       L"Simulated pasting is now turned off.",
                                        QCoreApplication::applicationDirPath().toStdWString() + L"/assets/red-cross.png");
    } else if (m_remainingTime == -3) {
        emit changeWindowTitle("xPaste");
        m_timer.stop();
    }

    m_remainingTime--;
}

void Settings::startCountdown()
{
    m_remainingTime = m_autoDisableSeconds;
    emit changeWindowTitle("xPaste - " + Utils::formatSeconds(m_remainingTime));
    m_remainingTime--;

    m_timer.start(1000); // 1 second interval
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

    if (newPasteActive && m_autoDisable)
        startCountdown();

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

bool Settings::disableToggleToasts() const
{
    return m_disableToggleToasts;
}

void Settings::setDisableToggleToasts(bool newDisableToggleToasts)
{
    if (m_disableToggleToasts == newDisableToggleToasts)
        return;

    m_disableToggleToasts = newDisableToggleToasts;

    emit disableToggleToastsChanged();
}

bool Settings::autoDisable() const
{
    return m_autoDisable;
}

void Settings::setAutoDisable(bool newAutoDisable)
{
    if (m_autoDisable == newAutoDisable)
        return;

    m_autoDisable = newAutoDisable;

    emit autoDisableChanged();
}

int Settings::autoDisableSeconds() const
{
    return m_autoDisableSeconds;
}

void Settings::setAutoDisableSeconds(int newAutoDisableSeconds)
{
    if (m_autoDisableSeconds == newAutoDisableSeconds)
        return;

    m_autoDisableSeconds = newAutoDisableSeconds;

    emit autoDisableSecondsChanged();
}

bool Settings::disableTimeToast() const
{
    return m_disableTimeToast;
}

void Settings::setDisableTimeToast(bool newDisableTimeToast)
{
    if (m_disableTimeToast == newDisableTimeToast)
        return;

    m_disableTimeToast = newDisableTimeToast;

    emit disableTimeToastChanged();
}

bool Settings::closeBtnExits() const
{
    return m_closeBtnExits;
}

void Settings::setCloseBtnExits(bool newCloseBtnExits)
{
    if (m_closeBtnExits == newCloseBtnExits)
        return;

    m_closeBtnExits = newCloseBtnExits;

    emit closeBtnExitsChanged();
}

bool Settings::singleClick() const
{
    return m_singleClick;
}

void Settings::setSingleClick(bool newSingleClick)
{
    if (m_singleClick == newSingleClick)
        return;

    m_singleClick = newSingleClick;

    emit singleClickChanged();
    emit singleClickChangedOverload(newSingleClick);
}

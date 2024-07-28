#include "Settings.h"


Settings::Settings(QObject *parent)
    : QObject{parent}
    , m_pasteHotkey{this, "PasteHotkey", m_qSettings} // 0x56 == 'V'
    , m_toggleHotkey{this, "ToggleHotkey", m_qSettings}
    , m_settingsFile{QApplication::applicationDirPath() + "/config.ini"}
    , m_qSettings{QSettings(m_settingsFile, QSettings::IniFormat)}
    , m_pasteActive{m_qSettings.value("PasteActive", false).toBool()}
    , m_toggleActive{m_qSettings.value("ToggleActive", false).toBool()}
    , m_customHotkeyEnabled{m_qSettings.value("CustomHotkeyEnabled", false).toBool()}
    , m_disableToggleToasts{m_qSettings.value("DisableToggleToasts", false).toBool()}
    , m_autoDisable{m_qSettings.value("AutoDisableEnabled", false).toBool()}
    , m_autoDisableSeconds{m_qSettings.value("AutoDisableSeconds", 30).toInt()}
    , m_disableTimeToast{m_qSettings.value("DisableTimeToast", false).toBool()}
    , m_closeBtnExits{m_qSettings.value("CloseButtonExits", false).toBool()}
    , m_singleClick{m_qSettings.value("TraySingleClick", false).toBool()}
    , m_hideOnMinimize{m_qSettings.value("HideOnMinimize", false).toBool()}
    , m_startMinimized{m_qSettings.value("StartMinimized", false).toBool()}
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
    if (m_remainingTime > 0)
    {
        emit changeWindowTitle("xPaste - " + Utils::formatSeconds(m_remainingTime));
    }
    else if (m_remainingTime == 0)
    {
        emit changeWindowTitle("Time is up!");
        setPasteActive(false);

        if (!m_disableTimeToast)
            TrayIcon::sendNotification(L"Time's up!",
                                       L"Simulated pasting is now turned off.",
                                        QCoreApplication::applicationDirPath().toStdWString() + L"/assets/red-cross.png");
    }
    else if (m_remainingTime == -3)
    {
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

    if (newPasteActive && m_autoDisable)
        startCountdown();

    m_qSettings.setValue("PasteActive", newPasteActive);

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

    m_qSettings.setValue("ToggleActive", newToggleActive);

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

    m_qSettings.setValue("CustomHotkeyEnabled", newCustomHotkeyEnabled);

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

    m_qSettings.setValue("DisableToggleToasts", newDisableToggleToasts);

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

    m_qSettings.setValue("AutoDisableEnabled", newAutoDisable);

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

    m_qSettings.setValue("AutoDisableSeconds", newAutoDisableSeconds);

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

    m_qSettings.setValue("DisableTimeToast", newDisableTimeToast);

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

    m_qSettings.setValue("CloseButtonExits", newCloseBtnExits);

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

    m_qSettings.setValue("TraySingleClick", newSingleClick);

    emit singleClickChanged();
    emit singleClickChangedOverload(newSingleClick);
}

bool Settings::hideOnMinimize() const
{
    return m_hideOnMinimize;
}

void Settings::setHideOnMinimize(bool newHideOnMinimize)
{
    if (m_hideOnMinimize == newHideOnMinimize)
        return;

    m_hideOnMinimize = newHideOnMinimize;

    m_qSettings.setValue("HideOnMinimize", newHideOnMinimize);

    emit hideOnMinimizeChanged();
}

bool Settings::startMinimized() const
{
    return m_startMinimized;
}

void Settings::setStartMinimized(bool newStartMinimized)
{
    if (m_startMinimized == newStartMinimized)
        return;

    m_startMinimized = newStartMinimized;

    m_qSettings.setValue("StartMinimized", newStartMinimized);

    emit startMinimizedChanged();
}

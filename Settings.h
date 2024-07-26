#ifndef SETTINGS_H
#define SETTINGS_H

#include "Hotkey.h"
#include "TrayIcon.h"
#include "Utils.h"

#include <QObject>
#include <QDebug>
#include <QTimer>

#include <Windows.h>


class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Hotkey* pasteHotkey READ pasteHotkey CONSTANT FINAL)
    Q_PROPERTY(Hotkey* toggleHotkey READ toggleHotkey CONSTANT FINAL)
    Q_PROPERTY(bool pasteActive READ pasteActive WRITE setPasteActive NOTIFY pasteActiveChanged FINAL)
    Q_PROPERTY(bool toggleActive READ toggleActive WRITE setToggleActive NOTIFY toggleActiveChanged FINAL)
    Q_PROPERTY(bool customHotkeyEnabled READ customHotkeyEnabled WRITE setCustomHotkeyEnabled NOTIFY customHotkeyEnabledChanged FINAL)
    Q_PROPERTY(bool disableToggleToasts READ disableToggleToasts WRITE setDisableToggleToasts NOTIFY disableToggleToastsChanged FINAL)
    Q_PROPERTY(bool autoDisable READ autoDisable WRITE setAutoDisable NOTIFY autoDisableChanged FINAL)
    Q_PROPERTY(int autoDisableSeconds READ autoDisableSeconds WRITE setAutoDisableSeconds NOTIFY autoDisableSecondsChanged FINAL)
    Q_PROPERTY(bool disableTimeToast READ disableTimeToast WRITE setDisableTimeToast NOTIFY disableTimeToastChanged FINAL)
    Q_PROPERTY(bool closeBtnExits READ closeBtnExits WRITE setCloseBtnExits NOTIFY closeBtnExitsChanged FINAL)

public:
    explicit Settings(QObject *parent = nullptr);

    bool pasteActive() const;
    void setPasteActive(bool newPasteActive);

    Hotkey* pasteHotkey();
    Hotkey* toggleHotkey();

    bool toggleActive() const;
    void setToggleActive(bool newToggleActive);

    bool customHotkeyEnabled() const;
    void setCustomHotkeyEnabled(bool newCustomHotkeyEnabled);

    bool disableToggleToasts() const;
    void setDisableToggleToasts(bool newDisableToggleToasts);

    bool autoDisable() const;
    void setAutoDisable(bool newAutoDisable);

    int autoDisableSeconds() const;
    void setAutoDisableSeconds(int newAutoDisableSeconds);

    bool disableTimeToast() const;
    void setDisableTimeToast(bool newDisableTimeToast);

    bool closeBtnExits() const;
    void setCloseBtnExits(bool newCloseBtnExits);

public slots:
    void togglePasteActive();
    void timerUpdateTitle();

signals:
    void pasteActiveChanged();
    void toggleActiveChanged();
    void customHotkeyEnabledChanged();
    void disableToggleToastsChanged();
    void autoDisableChanged();
    void autoDisableSecondsChanged();
    void disableTimeToastChanged();
    void closeBtnExitsChanged();

    void changeWindowTitle(const QString &windowTitle);

private:
    Hotkey m_pasteHotkey;
    Hotkey m_toggleHotkey;
    QTimer m_timer;
    int m_remainingTime{};
    bool m_pasteActive{};
    bool m_toggleActive{};
    bool m_customHotkeyEnabled{};
    bool m_disableToggleToasts{};
    bool m_autoDisable{};
    int m_autoDisableSeconds{};
    bool m_disableTimeToast{};
    bool m_closeBtnExits{};

    void startCountdown();

};

#endif // SETTINGS_H

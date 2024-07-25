#ifndef SETTINGS_H
#define SETTINGS_H

#include "Hotkey.h"
#include "TrayIcon.h"

#include <QObject>
#include <Windows.h>
#include <QDebug>


class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Hotkey* pasteHotkey READ pasteHotkey CONSTANT FINAL)
    Q_PROPERTY(Hotkey* toggleHotkey READ toggleHotkey CONSTANT FINAL)
    Q_PROPERTY(bool pasteActive READ pasteActive WRITE setPasteActive NOTIFY pasteActiveChanged FINAL)
    Q_PROPERTY(bool toggleActive READ toggleActive WRITE setToggleActive NOTIFY toggleActiveChanged FINAL)
    Q_PROPERTY(bool customHotkeyEnabled READ customHotkeyEnabled WRITE setCustomHotkeyEnabled NOTIFY customHotkeyEnabledChanged FINAL)

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

public slots:
    void togglePasteActive();

signals:
    void pasteActiveChanged();
    void toggleActiveChanged();
    void customHotkeyEnabledChanged();

private:
    Hotkey m_pasteHotkey;
    Hotkey m_toggleHotkey;
    bool m_pasteActive = false;
    bool m_toggleActive = false;
    bool m_customHotkeyEnabled = false;
};

#endif // SETTINGS_H

#ifndef HOTKEYEVENTFILTER_H
#define HOTKEYEVENTFILTER_H

#include "Hotkey.h"

#include <QAbstractNativeEventFilter>
#include <QApplication>
#include <QDebug>

#include <windows.h>


class HotkeyEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    bool nativeEventFilter(const QByteArray &eventType, void* message, qintptr*) override
    {
        MSG *msg = static_cast<MSG*>(message);

        if (msg->message == WM_HOTKEY) {
            int hotkeyId = msg->wParam;

            if (hotkeyId == Hotkey::PasteHotkeyID) {
                emit pasteHotkeyActivated();
                return true; // Event handled
            }
            if (hotkeyId == Hotkey::ToggleHotkeyID) {
                emit toggleHotkeyActivated();
                return true;
            }
        }

        return false; // Event not handled
    }

signals:
    void pasteHotkeyActivated();
    void toggleHotkeyActivated();

};

#endif // HOTKEYEVENTFILTER_H

#ifndef HOOKHANDLER_H
#define HOOKHANDLER_H

#include <Paster.h>

#include <QObject>
#include <QDebug>

#include <Windows.h>


class HookHandler : public QObject
{
    Q_OBJECT

public:
    explicit HookHandler(QObject *parent = nullptr);

    static void installHook();
    static void uninstallHook();
    static void setMainWindowHandle(HWND handle);
    static int getModifiers();

private:
    static HHOOK hKeyboardHook;
    static HWND qtMainWindowHandle;
    static int qModifiers;

    static bool checkModifierPress(DWORD vkCode);
    static bool checkModifierRelease(DWORD vkCode);
    static bool checkKeyPress(DWORD vkCode);

    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // HOOKHANDLER_H

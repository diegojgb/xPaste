#include "HookHandler.h"
#include "Manager.h"

#include <iostream>


HHOOK HookHandler::hKeyboardHook = nullptr;
HWND HookHandler::qtMainWindowHandle = nullptr;
int HookHandler::qModifiers = 0;


HookHandler::HookHandler(QObject *parent)
    : QObject{parent}
{}

bool HookHandler::checkModifierPress(DWORD vkCode)
{
    switch (vkCode) {
        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
            qModifiers |= Qt::ControlModifier;
            return true;
        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
            qModifiers |= Qt::ShiftModifier;
            return true;
        case VK_MENU:
        case VK_LMENU:
        case VK_RMENU:
            qModifiers |= Qt::AltModifier;
            return true;
        case VK_LWIN:
        case VK_RWIN:
            qModifiers |= Qt::MetaModifier;
            return true;
    }

    return false;
}

bool HookHandler::checkModifierRelease(DWORD vkCode)
{
    switch (vkCode) {
        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
            qModifiers &= ~Qt::ControlModifier;
            return true;
        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
            qModifiers &= ~Qt::ShiftModifier;
            return true;
        case VK_MENU:
        case VK_LMENU:
        case VK_RMENU:
            qModifiers &= ~Qt::AltModifier;
            return true;
        case VK_LWIN:
        case VK_RWIN:
            qModifiers &= ~Qt::MetaModifier;
            return true;
    }

    return false;
}

bool HookHandler::checkKeyPress(DWORD vkCode)
{
    if (g_manager->getPasteHotkeyEditing())
    {
        g_manager->settings()->pasteHotkey()->setVkCode(vkCode);
        return true;
    }
    else if (g_manager->getToggleHotkeyEditing())
    {
        g_manager->settings()->toggleHotkey()->setVkCode(vkCode);
        return true;
    }

    if (g_manager->settings()->pasteActive())
    {
        if (g_manager->settings()->pasteHotkey()->getVkCode() == vkCode
            && g_manager->settings()->pasteHotkey()->getModifiers() == qModifiers)
        {
            Paster::pasteClipboard();
            return true;
        }
    }

    if (g_manager->settings()->toggleActive())
    {
        if (g_manager->settings()->toggleHotkey()->getVkCode() == vkCode
            && g_manager->settings()->pasteHotkey()->getModifiers() == qModifiers)
        {
            g_manager->settings()->togglePasteActive();
            return true;
        }
    }

    return false;
}

void HookHandler::installHook()
{
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
}

void HookHandler::uninstallHook()
{
    if (hKeyboardHook) {
        UnhookWindowsHookEx(hKeyboardHook);
        hKeyboardHook = nullptr;
    }
}

void HookHandler::setMainWindowHandle(HWND handle)
{
    qtMainWindowHandle = handle;
}

int HookHandler::getModifiers()
{
    return qModifiers;
}

LRESULT CALLBACK HookHandler::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT*) lParam;
    DWORD vkCode = pKeyboard->vkCode;
    bool propagate = true;

    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
    {
        if (!checkModifierPress(vkCode))
            propagate = !checkKeyPress(vkCode);
    }
    else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
    {
        checkModifierRelease(vkCode);
    }

    PostMessage(qtMainWindowHandle, wParam, pKeyboard->vkCode, pKeyboard->flags);

    if (!propagate)
        return 1; // Block the key event from being processed further

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

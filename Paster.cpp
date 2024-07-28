#include "Paster.h"
#include "Manager.h"


Paster::Paster(QObject *parent)
    : QObject{parent}
{}

// static
// Code from "https://stackoverflow.com/questions/31305404/sending-two-or-more-chars-using-sendinput"
void Paster::sendInputString(const std::wstring &str)
{
    int len = str.length();
    if (len == 0) return;

    int extraSize = g_manager->pressedModsCount();

    std::vector<INPUT> in(len*2 + extraSize);
    ZeroMemory(&in[0], in.size()*sizeof(INPUT));

    int idx = 0;

    addModifiersRelease(in, idx);

    int i = 0;
    while (i < len)
    {
        WORD ch = (WORD) str[i++];

        if ((ch < 0xD800) || (ch > 0xDFFF))
        {
            in[idx].type = INPUT_KEYBOARD;
            in[idx].ki.wScan = ch;
            in[idx].ki.dwFlags = KEYEVENTF_UNICODE;
            ++idx;

            in[idx] = in[idx-1];
            in[idx].ki.dwFlags |= KEYEVENTF_KEYUP;
            ++idx;
        }
        else
        {
            in[idx].type = INPUT_KEYBOARD;
            in[idx].ki.wScan = ch;
            in[idx].ki.dwFlags = KEYEVENTF_UNICODE;
            ++idx;

            in[idx].type = INPUT_KEYBOARD;
            in[idx].ki.wScan = (WORD) str[i++];
            in[idx].ki.dwFlags = KEYEVENTF_UNICODE;
            ++idx;

            in[idx] = in[idx-2];
            in[idx].ki.dwFlags |= KEYEVENTF_KEYUP;
            ++idx;

            in[idx] = in[idx-2];
            in[idx].ki.dwFlags |= KEYEVENTF_KEYUP;
            ++idx;
        }
    }

    SendInput(in.size(), &in[0], sizeof(INPUT));
}

std::wstring Paster::getClipboardText()
{
    // Try opening the clipboard
    if (!OpenClipboard(nullptr)) {
        Utils::errorExit("[Paster]: Failed to open clipboard.");
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData == nullptr) {
        CloseClipboard();
        Utils::errorExit("[Paster]: Failed to get handle of clipboard object for UNICODE text.");
    }

    wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
    if (pszText == nullptr) {
        CloseClipboard();
        Utils::errorExit("[Paster]: Error while locking the handle to get the actual text pointer.");
    }

    std::wstring text(pszText);

    GlobalUnlock(hData);
    CloseClipboard();

    return text;
}

void Paster::pasteClipboard()
{
    sendInputString(getClipboardText());
}

// Excluding the WIN modifier.
void Paster::addModifiersRelease(std::vector<INPUT> &in, int &idx)
{
    Manager* manager = g_manager;
    int modifiers = manager->getQModifiers();

    if ((modifiers & Qt::ControlModifier) != 0)
        addCtrlRelease(in, idx);
    if ((modifiers & Qt::ShiftModifier) != 0)
        addShiftRelease(in, idx);
    if ((modifiers & Qt::AltModifier) != 0)
        addAltRelease(in, idx);
}

void Paster::addCtrlRelease(std::vector<INPUT> &in, int &idx)
{
    in[idx].type = INPUT_KEYBOARD;
    in[idx].ki.wVk = VK_CONTROL;
    in[idx].ki.dwFlags = KEYEVENTF_KEYUP;
    ++idx;
}

void Paster::addShiftRelease(std::vector<INPUT> &in, int &idx)
{
    in[idx].type = INPUT_KEYBOARD;
    in[idx].ki.wVk = VK_SHIFT;
    in[idx].ki.dwFlags = KEYEVENTF_KEYUP;
    ++idx;
}

void Paster::addAltRelease(std::vector<INPUT> &in, int &idx)
{
    in[idx].type = INPUT_KEYBOARD;
    in[idx].ki.wVk = VK_MENU;
    in[idx].ki.dwFlags = KEYEVENTF_KEYUP;
    ++idx;
}

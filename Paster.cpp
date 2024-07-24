#include "Paster.h"

Paster::Paster(QObject *parent)
    : QObject{parent}
{}

// static
// Code from "https://stackoverflow.com/questions/31305404/sending-two-or-more-chars-using-sendinput"
void Paster::sendInputString(const std::wstring &str)
{
    int len = str.length();
    if (len == 0) return;

    std::vector<INPUT> in(len*2);
    ZeroMemory(&in[0], in.size()*sizeof(INPUT));

    int i = 0, idx = 0;
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
        Utils::throwError("Failed to open clipboard.");
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData == nullptr) {
        CloseClipboard();
        Utils::throwError("Failed to get handle of clipboard object for UNICODE text.");
    }

    wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
    if (pszText == nullptr) {
        CloseClipboard();
        Utils::throwError("[Paster] Erorr while locking the handle to get the actual text pointer.");
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

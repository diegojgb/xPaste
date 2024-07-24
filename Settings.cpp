#include "Settings.h"


Settings::Settings(QObject *parent)
    : QObject{parent}, m_pasteHotkey{this, Hotkey::PasteHotkeyID}
{}

Hotkey* Settings::pasteHotkey()
{
    return &m_pasteHotkey;
}

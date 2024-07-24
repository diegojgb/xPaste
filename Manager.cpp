#include "Manager.h"


Manager::Manager(QObject *parent)
    : QObject{parent}
{}

Settings* Manager::settings()
{
    return &m_settings;
}

bool Manager::active() const
{
    return m_active;
}

void Manager::setActive(bool newActive)
{
    if (m_active == newActive)
        return;

    if (newActive)
        m_settings.pasteHotkey()->registerHotkey();
    else
        m_settings.pasteHotkey()->unregisterHotkey();

    m_active = newActive;

    emit activeChanged();
}

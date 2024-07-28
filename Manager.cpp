#include "Manager.h"

Manager* g_manager = nullptr;
bool Manager::pasteHotkeyEditing = false;
bool Manager::toggleHotkeyEditing = false;

Manager::Manager(QObject *parent)
    : QObject{parent}
    , m_isWindows10{Utils::isWindows10()}
    , m_hookHandler{this}
{
    m_hookHandler.installHook();
    connect(&m_settings, &Settings::changeWindowTitle, this, &Manager::onChangeWindowTitle);
}

Settings* Manager::settings()
{
    return &m_settings;
}

void Manager::initTrayIcon(QObject *parent, QQuickWindow *rootWindow)
{
    if (m_trayIcon != nullptr)
        Utils::errorExit("[Manager]: Tray icon can only be initialized once.");

    m_trayIcon = new TrayIcon(parent, rootWindow, m_settings.singleClick());

    connect(&m_settings, &Settings::singleClickChangedOverload, m_trayIcon, &TrayIcon::onSingleClickChanged);
}

void Manager::setMainWindow(QQuickWindow *window)
{
    m_mainWindow = window;
}

bool Manager::getPasteHotkeyEditing()
{
    return pasteHotkeyEditing;
}

bool Manager::getToggleHotkeyEditing()
{
    return toggleHotkeyEditing;
}

// Excluding the WIN modifier.
int Manager::pressedModsCount()
{
    int count = 0;
    int modifiers = m_hookHandler.getModifiers() & (Qt::ControlModifier | Qt::ShiftModifier | Qt::AltModifier);

    while (modifiers) {
        count += modifiers & 1;
        modifiers >>= 1;
    }

    return count;
}

void Manager::setPasteHotkeyEditing(bool editing)
{
    pasteHotkeyEditing = editing;
}

void Manager::setToggleHotkeyEditing(bool editing)
{
    toggleHotkeyEditing = editing;
}

int Manager::getQModifiers()
{
    return m_hookHandler.getModifiers();
}

void Manager::onChangeWindowTitle(const QString &windowTitle)
{
    m_mainWindow->setTitle(windowTitle);
}

bool Manager::isWindows10() const
{
    return m_isWindows10;
}

#include "TrayIcon.h"

using namespace WinToastLib;


TrayIcon::TrayIcon(QObject *parent, QQuickWindow *rootWindow, bool singleClick)
    : QObject{parent}
    , m_rootWindow{rootWindow}
    , m_hwnd{(HWND)rootWindow->winId()}
    , m_trayIcon{new QSystemTrayIcon(rootWindow)}
    , m_singleClick{singleClick}
{
    QMenu *trayIconMenu = createMenu();

    m_trayIcon->setContextMenu(trayIconMenu);
    m_trayIcon->setIcon(QIcon(":/qt/qml/xPaste/assets/xpaste-logo.ico"));
    m_trayIcon->setToolTip("xPaste");
    m_trayIcon->show();

    initWinToast();

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::trayIconActivated);

    if (singleClick)
        connect(this, &TrayIcon::singleClicked, this, &TrayIcon::showWindow);
    else
        connect(this, &TrayIcon::doubleClicked, this, &TrayIcon::showWindow);
}

void TrayIcon::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        emit singleClicked();
    if (reason == QSystemTrayIcon::DoubleClick)
        emit doubleClicked();
}

void TrayIcon::bringToTop()
{
    SetForegroundWindow(m_hwnd);
}

void TrayIcon::onSingleClickChanged(bool singleClick)
{
    if (m_singleClick == singleClick)
        return;

    if (singleClick)
    {
        disconnect(this, &TrayIcon::doubleClicked, this, &TrayIcon::showWindow);
        connect(this, &TrayIcon::singleClicked, this, &TrayIcon::showWindow);
    }
    else
    {
        disconnect(this, &TrayIcon::singleClicked, this, &TrayIcon::showWindow);
        connect(this, &TrayIcon::doubleClicked, this, &TrayIcon::showWindow);
    }

    m_singleClick = singleClick;
}

void TrayIcon::showWindow()
{
    m_rootWindow->showNormal();
    bringToTop();
}

QMenu *TrayIcon::createMenu()
{
    QAction *restoreAction = new QAction(QObject::tr("&Restore"), m_rootWindow);
    connect(restoreAction, &QAction::triggered, this, &TrayIcon::showWindow);

    QAction *quitAction = new QAction(QObject::tr("&Quit"), m_rootWindow);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    return trayIconMenu;
}

void TrayIcon::initWinToast()
{
    if (!WinToast::isCompatible())
        Utils::errorExit("[WinToast]: Error, your system in not supported!");

    WinToast::instance()->setAppName(L"xPaste");
    const auto aumi = WinToast::configureAUMI(L"diegojgb", L"xPaste", L"ToastNotifications");
    WinToast::instance()->setAppUserModelId(aumi);
    WinToast::instance()->setShortcutPolicy(WinToast::ShortcutPolicy::SHORTCUT_POLICY_IGNORE);

    // Add icon and name to registry, so Windows can display them in toast notifications.
    if (!Registry::createRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\AppUserModelId\\diegojgb.xPaste.ToastNotifications"))
    {
        Utils::errorExit("[Registry]: Error opening or creating new Registry key");
    }

    if (!Registry::writeStringInRegistry(
            HKEY_CURRENT_USER,
            L"Software\\Classes\\AppUserModelId\\diegojgb.xPaste.ToastNotifications",
            L"DisplayName",
            L"xPaste"))
    {
        Utils::errorExit("[Registry]: Error saving toast DisplayName Regitry value");
    }

    QString defaultIcon = QCoreApplication::applicationDirPath() + "/assets/xpaste-logo.png";
    defaultIcon.replace("/", "\\");
    if (!Registry::writeStringInRegistry(
            HKEY_CURRENT_USER,
            L"Software\\Classes\\AppUserModelId\\diegojgb.xPaste.ToastNotifications",
            L"IconUri",
            defaultIcon.toStdWString().c_str()))
    {
        Utils::errorExit("[Registry]: Error saving toast IconUri Regitry value");
    }

    if (!WinToast::instance()->initialize())
        Utils::errorExit("[WinToast]: Error, could not initialize WinToast!");
}

void TrayIcon::sendNotification(const WinToastTemplate &templ)
{
    if (WinToast::instance()->showToast(templ, new ToastHandler()) < 0)
    {
        Utils::errorExit("[WinToast]: Could not launch your toast notification!");
    }
}

void TrayIcon::sendNotification(const std::wstring title, const std::wstring subtitle, const std::wstring imagePath)
{
    WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
    templ.setTextField(title, WinToastTemplate::FirstLine);
    templ.setTextField(subtitle, WinToastTemplate::SecondLine);
    templ.setImagePath(imagePath);

    sendNotification(templ);
}

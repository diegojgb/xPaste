#include "TrayIcon.h"

using namespace WinToastLib;


TrayIcon::TrayIcon(QObject *parent, QQuickWindow *rootWindow)
    : QObject{parent}
    , m_rootWindow{rootWindow}
    , m_hwnd{(HWND)rootWindow->winId()}
    , m_trayIcon{new QSystemTrayIcon(rootWindow)}
{
    QMenu *trayIconMenu = createMenu();

    m_trayIcon->setContextMenu(trayIconMenu);
    m_trayIcon->setIcon(QIcon(":/qt/qml/xPasteQT/assets/xpaste_logo.ico"));
    m_trayIcon->setToolTip("xPaste");
    m_trayIcon->show();

    initWinToast();

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::trayIconActivated);
    connect(this, &TrayIcon::singleClicked, m_rootWindow, &QQuickWindow::showNormal);
    connect(this, &TrayIcon::singleClicked, this, &TrayIcon::bringToTop);
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

QMenu* TrayIcon::createMenu()
{
    QAction* restoreAction = new QAction(QObject::tr("&Restore"), m_rootWindow);
    connect(restoreAction, &QAction::triggered, m_rootWindow, &QQuickWindow::showNormal);
    connect(restoreAction, &QAction::triggered, this, &TrayIcon::bringToTop);

    QAction* quitAction = new QAction(QObject::tr("&Quit"), m_rootWindow);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QMenu* trayIconMenu = new QMenu();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    return trayIconMenu;
}

void TrayIcon::initWinToast()
{
    if (!WinToast::isCompatible())
        Utils::throwError("WinToast: Error, your system in not supported!");

    WinToast::instance()->setAppName(L"WatchLog");
    const auto aumi = WinToast::configureAUMI(L"diegojgb", L"xPaste", L"ToastNotifications");
    WinToast::instance()->setAppUserModelId(aumi);
    WinToast::instance()->setShortcutPolicy(WinToast::ShortcutPolicy::SHORTCUT_POLICY_IGNORE);

    // Add icon and name to registry, so Windows can display them in toast notifications.
    if (!Registry::createRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\AppUserModelId\\diegojgb.xPaste.ToastNotifications")) {
        Utils::throwError("Error opening or creating new Registry key");
    }

    if (!Registry::writeStringInRegistry(
            HKEY_CURRENT_USER,
            L"Software\\Classes\\AppUserModelId\\diegojgb.xPaste.ToastNotifications",
            L"DisplayName",
            L"xPaste")) {
        Utils::throwError("Error saving toast DisplayName Regitry value");
    }

    QString defaultIcon = QCoreApplication::applicationDirPath() + "/assets/xpaste_logo.ico";
    defaultIcon.replace("/", "\\");
    if (!Registry::writeStringInRegistry(
            HKEY_CURRENT_USER,
            L"Software\\Classes\\AppUserModelId\\diegojgb.xPaste.ToastNotifications",
            L"IconUri",
            defaultIcon.toStdWString().c_str())) {
        Utils::throwError("Error saving toast IconUri Regitry value");
    }

    if (!WinToast::instance()->initialize())
        Utils::throwError("Error, could not initialize WinToast!");
}

void TrayIcon::sendNotification(const WinToastTemplate& templ)
{
    if (WinToast::instance()->showToast(templ, new ToastHandler()) < 0) {
        Utils::throwError("Could not launch your toast notification!");
    }
}

void TrayIcon::sendNotification(const std::wstring title, const std::wstring subtitle)
{
    WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
    templ.setTextField(title, WinToastTemplate::FirstLine);
    templ.setTextField(subtitle, WinToastTemplate::SecondLine);

    sendNotification(templ);
}

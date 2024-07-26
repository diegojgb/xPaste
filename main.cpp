#include "HotkeyEventFilter.h"
#include "Manager.h"
#include "Paster.h"
#include "Settings.h"
#include "WindowThemeSetter.h"

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QStyleHints>
#include <QQuickWindow>
#include <QQmlContext>

#include <dwmapi.h>

bool isDark(Qt::ColorScheme colorScheme) {
    if (colorScheme == Qt::ColorScheme::Light) {
        return false;
    } else
        return true;
}

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");
    // app.setWindowIcon(QIcon(":/xPasteQT/assets/xpaste_logo.ico"));

    QStyleHints *styleHints = QGuiApplication::styleHints();
    Qt::ColorScheme colorScheme = styleHints->colorScheme();
    auto *themeSetter = new WindowThemeSetter(&app, colorScheme == Qt::ColorScheme::Dark);

    QObject::connect(styleHints, &QStyleHints::colorSchemeChanged, themeSetter, qOverload<>(&WindowThemeSetter::updateWindowTheme));

    QQmlApplicationEngine engine;

    auto *manager = new Manager(&app);

    engine.rootContext()->setContextProperty("Manager", manager);
    engine.rootContext()->setContextProperty("ThemeSetter", themeSetter);

    const QUrl url(u"qrc:/qt/qml/xPasteQT/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *root = engine.rootObjects().at(0);
    QQuickWindow *mainWindow = qobject_cast<QQuickWindow*>(root);

    manager->initTrayIcon(&app, mainWindow);
    manager->setMainWindow(mainWindow);

    // Add a filter/listener for global hotkey events.
    auto* eventFilter = new HotkeyEventFilter();
    app.installNativeEventFilter(eventFilter);

    QObject::connect(eventFilter, &HotkeyEventFilter::pasteHotkeyActivated, Paster::pasteClipboard);
    QObject::connect(eventFilter, &HotkeyEventFilter::toggleHotkeyActivated, manager->settings(), &Settings::togglePasteActive);

    return app.exec();
}

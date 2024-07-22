#include "Manager.h"
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

    QScopedPointer<WindowThemeSetter> themeSetter(new WindowThemeSetter(&app, colorScheme ==  Qt::ColorScheme::Dark));

    QObject::connect(styleHints, &QStyleHints::colorSchemeChanged, themeSetter.get(), qOverload<>(&WindowThemeSetter::updateWindowTheme));

    QQmlApplicationEngine engine;

    qmlRegisterSingletonInstance("com.obin.ThemeSetter", 1, 0, "ThemeSetter", themeSetter.get());
    engine.rootContext()->setContextProperty("Manager", new Manager());

    const QUrl url(u"qrc:/xPasteQT/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

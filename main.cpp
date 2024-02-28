#include "WindowThemeSetter.h"

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <dwmapi.h>



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");
    app.setWindowIcon(QIcon(":/xPasteQT/assets/xpaste_logo.ico"));

    QScopedPointer<WindowThemeSetter> themeSetter(new WindowThemeSetter(&app));

    QQmlApplicationEngine engine;

    themeSetter.get()->engine = &engine;

    qmlRegisterSingletonInstance("com.obin.ThemeSetter", 1, 0, "ThemeSetter", themeSetter.get());

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

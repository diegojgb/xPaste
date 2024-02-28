#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>


void InstallDefaultFont()
{
    qint32 fontId = QFontDatabase::addApplicationFont(":/xPasteQT/assets/Montserrat-Regular.ttf");
    QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);

    QString family = fontList.first();
    QGuiApplication::setFont(QFont(family));
}

int main(int argc, char *argv[])
{
    // QFont font("Verdana", 8);
    // QGuiApplication::setFont(font);

    // qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");

    // InstallDefaultFont();

    // QFontDatabase database;
    // QStringList fontFamilies = database.families();

    // qDebug() << "Available Font Families:";

    // // Print each font family to the console
    // for (const QString &fontFamily : fontFamilies) {
    //     qDebug() << fontFamily;
    // }

    app.setWindowIcon(QIcon(":/xPasteQT/assets/xpaste_logo.ico"));

    QQmlApplicationEngine engine;
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

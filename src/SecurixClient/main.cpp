#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtQuick>
#include "backend.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    BackEnd back_end;
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    engine.rootContext()->setContextProperty("back_end", &back_end);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

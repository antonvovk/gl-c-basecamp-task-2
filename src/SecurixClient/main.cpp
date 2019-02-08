#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtQuick>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtQml>

#include "backend.h"
#include "sqlconversationmodel.h"
#include "sqluserlistmodel.h"

static void connectToDatabase() {
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("users");
    database.setUserName("securix");
    database.setPassword("qw&UZ**485$xX9");

    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    qmlRegisterType<SqlUserListModel>("user.list.model", 1, 0, "SqlUserListModel");
    qmlRegisterType<SqlConversationModel>("conversation.model", 1, 0, "SqlConversationModel");

    connectToDatabase();

    BackEnd &back_end = BackEnd::instance();
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    engine.rootContext()->setContextProperty("back_end", &back_end);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

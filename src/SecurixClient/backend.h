#ifndef BACKEND_H
#define BACKEND_H

#include <QSslSocket>
#include <QObject>
#include <QDataStream>
#include <QSqlQuery>
#include <QSqlError>
#include "sqlconversationmodel.h"

class BackEnd : public QObject {
    Q_OBJECT
public:
    static BackEnd& instance();
public slots:
    void connectToSecureHost();
    void notifyServerOfNewMessage();
    void disconnectFromSecureHost();
    void onReadyRead();
    QString getAuthor();
    void initFirstStage(QString hostname, quint16 port, const QString &username);
    void addNewUserToDB(const QString &username, const QString &password, const QString &fullname);
    bool checkCredentialsWithDB(const QString &username, const QString &password);
    void updateCurrentRoom(const QString &roomname);
    void notifyServerOfNewConnection(const QString &recipient);
    void notifyServerOfDisconnect(const QString &recipient);
signals:
    void doUiData();
private:
    BackEnd(QObject *parent = nullptr);
    QSslSocket sslSocket;
    QSqlQuery query;
    QString hostname;
    quint16 port;
};

#endif

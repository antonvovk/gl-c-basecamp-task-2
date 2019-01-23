#ifndef SECURENETWORKMANAGER_H
#define SECURENETWORKMANAGER_H

#include <QSslSocket>
#include <QObject>
#include <QTextEdit>
#include "client.h"

class SecureNetworkManager : public QObject {
    Q_OBJECT
public:
    SecureNetworkManager(QObject *parent = nullptr);
    void connectToSecureHost(const QString &hostname, const quint16 &port, const QString &username, const QString &room);
    void sendMessage(const QString &message);
    void initUiFields(QTextEdit &history, QTextEdit &users);
    void outputToUi(const Client &client);
public slots:
    void onReadyRead();
private:
    QTextEdit *history, *users;
    Client client;
    QSslSocket sslSocket;

};

#endif

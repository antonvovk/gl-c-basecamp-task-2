#ifndef BACKEND_H
#define BACKEND_H

#include <QHostAddress>
#include <QSslSocket>
#include <QObject>
#include <QDataStream>
#include "sslserver.h"

class BackEnd : public QObject {
    Q_OBJECT
public:
    static BackEnd& instance();
private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
private:
    BackEnd(QObject *parent = nullptr);
    SslServer &sslServer = SslServer::instance();
    std::vector<QSslSocket*> sockets;
};

#endif

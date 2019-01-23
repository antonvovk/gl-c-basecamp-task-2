#ifndef SECURENETWORKMANAGER_H
#define SECURENETWORKMANAGER_H

#include <QHostAddress>
#include <QSslSocket>
#include <QObject>
#include "sslserver.h"
#include "client.h"

class SecureNetworkManager : public QObject {
    Q_OBJECT
public:
    SecureNetworkManager(QObject *parent = nullptr);
    void broadcastMessage(const Client &client) const;
    QString getClientsList(const QString &room);
protected slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
private:
    SslServer sslServer;
    std::vector<Client> clients;
    std::vector<QSslSocket*> sockets;
};

#endif

#include "securenetworkmanager.h"

SecureNetworkManager::SecureNetworkManager(QObject *parent) : QObject(parent) {
    QHostAddress address = QHostAddress::Any;
    quint16 port = 22336;

    sslServer.setSslLocalCertificate("../Certificates/Server/sslserver.pem");
    sslServer.setSslPrivateKey("../Certificates/Server/sslserver.key");
    sslServer.setSslProtocol(QSsl::TlsV1_2);

    if (!sslServer.listen(address, port)) {
        // Add error handling here
        qDebug() << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port;
    }

    QObject::connect(&this->sslServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void SecureNetworkManager::broadcastMessage(const Client &client) const {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        if (client.getRoom() == clients[i].getRoom()) {
            QDataStream stream(sockets[i]);
            stream << client;

            if (!sockets[i]->waitForBytesWritten(-1)) {
                // Add error handling here
                qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sockets[i]->errorString()) << ")";
            }
        }
    }
}

QString SecureNetworkManager::getClientsList(const QString &room) {
    QString clients_list = "Users: ";

    for (auto& i : clients) {
        if (i.getRoom() == room) {
            clients_list.append(i.getUsername() + " ");
        }
    }

    return clients_list;
}

void SecureNetworkManager::onNewConnection() {
        sockets.insert(std::begin(sockets), dynamic_cast<QSslSocket*>(sslServer.nextPendingConnection()));
        Client tmp_client;
        clients.insert(std::begin(clients), tmp_client);
        QObject::connect(this->sockets[0], SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        QObject::connect(this->sockets[0], SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void SecureNetworkManager::onReadyRead() {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        QDataStream stream(sockets[i]);
        stream.startTransaction();
        Client client_tmp;
        stream >> client_tmp;

        if (client_tmp.getMessage().isEmpty()) {
            continue;
        }

        clients[i] = client_tmp;

        if (clients[i].getMessage().contains("Cnnct")) {

            clients[i].setMessage(getClientsList(clients[i].getRoom()));
            broadcastMessage(clients[i]);
            clients[i].setMessage(clients[i].getUsername() + " connected!");
        }

        if(!stream.commitTransaction()) {
            // Add error handling here
            qDebug() << "Error:" << stream.status();
        }

        broadcastMessage(clients[i]);
    }

}

void SecureNetworkManager::onDisconnected() {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        if (sockets[i]->state() != QTcpSocket::ConnectedState) {
            sockets[i]->disconnectFromHost();
            sockets.erase(std::begin(sockets) + i);
            Client client_tmp(clients[i]);
            clients.erase(std::begin(clients) + i);

            client_tmp.setMessage(getClientsList(client_tmp.getRoom()));
            broadcastMessage(client_tmp);
            client_tmp.setMessage(client_tmp.getUsername() + " disconnected!");
            broadcastMessage(client_tmp);

        }
    }
}

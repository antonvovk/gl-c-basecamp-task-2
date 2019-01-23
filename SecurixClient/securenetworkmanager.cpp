#include "securenetworkmanager.h"

SecureNetworkManager::SecureNetworkManager(QObject *parent) : QObject(parent) {
    QObject::connect(&this->sslSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void SecureNetworkManager::connectToSecureHost(const QString &hostname, const quint16 &port, const QString &username, const QString &room) {
    if (sslSocket.state() != QTcpSocket::ConnectedState) {
        sslSocket.addCaCertificates("../Certificates/Client/sslserver.pem");
        sslSocket.connectToHostEncrypted(hostname, port);

        if (!sslSocket.waitForEncrypted(-1)) {
            // Add error handling here
            qDebug() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
        }

        client.setUsername(username);
        client.setRoom(room);

        QString message = ("Cnnct");
        this->sendMessage(message);
    }
}

void SecureNetworkManager::sendMessage(const QString &message) {
    QDataStream stream(&sslSocket);
    client.setMessage(message);
    stream << client;

    if (!sslSocket.waitForBytesWritten(-1)) {
        // Add error handling here
        qDebug() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";
    }
}

void SecureNetworkManager::initUiFields(QTextEdit &history, QTextEdit &users) {
    this->history = &history;
    this->users = &users;
}

void SecureNetworkManager::outputToUi(const Client &client) {
    if (client.getMessage().contains("Users:")) {
        QString buf;
        users->clear();
        for (int i = 0; i < client.getMessage().size(); ++i) {
            buf.append(client.getMessage()[i]);
            if (client.getMessage()[i] == ' ') {
                users->append(buf);
                buf.clear();
            }
        }
    }

    else if (client.getMessage().contains("disconnected")) {
        history->append(client.getMessage());
    }

    else if (client.getMessage().contains("connected")) {
        history->append(client.getMessage());
    }

    else {
        history->append(client.getUsername() + ": " + client.getMessage());
    }
}

void SecureNetworkManager::onReadyRead() {
        QDataStream stream(&sslSocket);
        stream.startTransaction();
        Client tmp_client;
        stream >> tmp_client;

        if(stream.commitTransaction()) {
            outputToUi(tmp_client);
        }
        else {
            // Add error handling here
            qDebug() << "Error:" << stream.status();
        }
}

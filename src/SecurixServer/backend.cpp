#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
    QHostAddress address = QHostAddress::Any;
    quint16 port = 4444;

    sslServer.setSslLocalCertificate("sslserver.pem");
    sslServer.setSslPrivateKey("sslserver.key");
    sslServer.setSslProtocol(QSsl::TlsV1_2);

    if (!sslServer.listen(address, port)) {
        // Add error handling here
        qDebug() << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port;
        return;
    }

    QObject::connect(&this->sslServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

BackEnd& BackEnd::instance() {
    static BackEnd instance;
    return instance;
}

void BackEnd::onNewConnection() {
    sockets.insert(std::begin(sockets), dynamic_cast<QSslSocket*>(sslServer.nextPendingConnection()));
    QObject::connect(this->sockets[0], SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(this->sockets[0], SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void BackEnd::onReadyRead() {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        QDataStream stream(sockets[i]);
        stream << "notifyClientsOfNewMessage";

        if (!sockets[i]->waitForBytesWritten(-1)) {
            // Add error handling here
            qDebug() << "ERROR: could not send message (" << qPrintable(sockets[i]->errorString()) << ")";
            return;
        }
    }
}

void BackEnd::onDisconnected() {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        if (sockets[i]->state() != QTcpSocket::ConnectedState) {
            sockets[i]->disconnectFromHost();
            sockets.erase(std::begin(sockets) + i);
        }
    }
}

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

void BackEnd::broadcastMessage() const {
    qDebug() << message_buffer.text_data;
    for (unsigned i = 0; i < sockets.size(); ++i) {
        if (room_buffer.name == rooms[i].name) {
            QDataStream stream(sockets[i]);
            stream << user_buffer << message_buffer;

            if (!sockets[i]->waitForBytesWritten(-1)) {
                // Add error handling here
                qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sockets[i]->errorString()) << ")";
                return;
            }
        }
    }
}

QString BackEnd::getClientsList() {
    QString users_list = "Users: ";

    for (unsigned i = 0; i < rooms.size(); ++i) {
        if (rooms[i].name == room_buffer.name) {
            users_list.append(users[i].name + " ");
        }
    }

    return users_list;
}

void BackEnd::onNewConnection() {
        sockets.insert(std::begin(sockets), dynamic_cast<QSslSocket*>(sslServer.nextPendingConnection()));
        users.emplace(std::begin(users));
        rooms.emplace(std::begin(rooms));

        QObject::connect(this->sockets[0], SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        QObject::connect(this->sockets[0], SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void BackEnd::onReadyRead() {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        QDataStream stream(sockets[i]);
        stream.startTransaction();
        stream >> user_buffer >> room_buffer >> message_buffer;

        if (message_buffer.text_data.isEmpty()) {
            continue;
        }

        if (users[i].name.isEmpty() || rooms[i].name.isEmpty()) {
            users[i] = user_buffer;
            rooms[i] = room_buffer;

            message_buffer.text_data = getClientsList();
            broadcastMessage();
            message_buffer.text_data = users[i].name + " connected!";
        }

        if (!stream.commitTransaction()) {
            // Add error handling here
            qDebug() << "Error:" << stream.status();
            return;
        }

        broadcastMessage();
    }

}

void BackEnd::onDisconnected() {
    for (unsigned i = 0; i < sockets.size(); ++i) {
        if (sockets[i]->state() != QTcpSocket::ConnectedState) {
            sockets[i]->disconnectFromHost();
            sockets.erase(std::begin(sockets) + i);
            user_buffer = users[i];
            room_buffer = rooms[i];

            users.erase(std::begin(users) + i);
            rooms.erase(std::begin(rooms) + i);

            message_buffer.text_data = getClientsList();
            broadcastMessage();
            message_buffer.text_data = user_buffer.name + " disconnected!";
            broadcastMessage();

        }
    }
}

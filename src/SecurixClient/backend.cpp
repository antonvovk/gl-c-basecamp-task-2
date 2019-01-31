#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
    QObject::connect(&this->sslSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void BackEnd::connectToSecureHost(const QString &hostname, const quint16 &port, const QString &username, const QString &roomname) {
    if (sslSocket.state() != QTcpSocket::ConnectedState) {
        sslSocket.addCaCertificates("sslserver.pem");
        sslSocket.connectToHostEncrypted(hostname, port);

        if (!sslSocket.waitForEncrypted(-1)) {
            // Add error handling here
            qDebug() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
            return;
        }

        user.name = username;
        room.name = roomname;
        sendMessage("Cnnct");
    }
}

void BackEnd::sendMessage(const QString &message_data_txt) {
    QDataStream stream(&sslSocket);
    message.text_data = message_data_txt;
    stream << user << room << message;

    if (!sslSocket.waitForBytesWritten(-1)) {
        // Add error handling here
        qDebug() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";
        return;
    }
}

void BackEnd::outputToUi() {
    history.clear();
    if (message_received.text_data.contains("disconnected") || message_received.text_data.contains("connected")) {
        history.append(message_received.text_data);
        emit doUiData(history, users_list);
        return;
    }

    if (!message_received.text_data.contains("Users:")) {
        history.append(user_received.name + ": " + message_received.text_data);
        emit doUiData(history, users_list);
        return;
    }

    QString buf;
    users_list.clear();
    for (int i = 0, ok = 0; i < message_received.text_data.size(); ++i) {
        buf.append(message_received.text_data[i]);
        if (message_received.text_data[i] == ' ') {
            if (ok == 0 && !buf.contains("Users:")) {
                break;
            }
            else {
             ++ok;
            }
            users_list.append(buf + '\n');
            buf.clear();
        }
    }

    emit doUiData(history, users_list);
}

void BackEnd::disconnectFromSecureHost() {
    sslSocket.disconnectFromHost();
}

void BackEnd::onReadyRead() {
        QDataStream stream(&sslSocket);
        stream.startTransaction();
        stream >> user_received >> message_received;

        if (stream.commitTransaction()) {
            outputToUi();
        }
        else {
            // Add error handling here
            qDebug() << "Error:" << stream.status();
            return;
        }
}

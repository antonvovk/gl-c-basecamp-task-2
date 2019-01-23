#include "client.h"

QString Client::getUsername() const {
    return this->username;
}

QString Client::getRoom() const {
    return this->room;
}

QString Client::getMessage() const {
    return this->message;
}

void Client::setUsername(const QString &username) {
    this->username = username;
}

void Client::setRoom(const QString &room) {
    this->room = room;
}

void Client::setMessage(const QString &message) {
    this->message = message;
}

QDataStream& operator<<(QDataStream &dataStream, const Client &client) {
    dataStream << client.getUsername() << client.getRoom() << client.getMessage();
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Client &client) {
    QString username, room, message;
    dataStream >> username >> room >> message;
    client.username = username;
    client.room = room;
    client.message = message;
    return dataStream;
}

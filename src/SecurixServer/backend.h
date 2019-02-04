#ifndef BACKEND_H
#define BACKEND_H

#include <QHostAddress>
#include <QSslSocket>
#include <QObject>
#include "sslserver.h"
#include "../Common/user.h"
#include "../Common/message.h"
#include "../Common/room.h"

class BackEnd : public QObject {
    Q_OBJECT
public:
    BackEnd(QObject *parent = nullptr);
    void broadcastMessage() const;
    QString getClientsList();
private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
private:
    SslServer sslServer;
    std::vector<QSslSocket*> sockets;
    std::vector<User> users;
    std::vector<Room> rooms;
    Message message_buffer;
    User user_buffer;
    Room room_buffer;
};

#endif

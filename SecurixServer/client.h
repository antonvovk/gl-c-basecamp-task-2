#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QString>

class Client {
public:
    QString getUsername() const;
    QString getRoom() const;
    QString getMessage() const;
    void setUsername(const QString &username);
    void setRoom(const QString &room);
    void setMessage(const QString &message);
    friend QDataStream& operator<<(QDataStream &dataStream, const Client &client);
    friend QDataStream& operator>>(QDataStream &dataStream, Client &client);
private:
    QString username, room, message;
};

#endif

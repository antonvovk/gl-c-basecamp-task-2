#ifndef ROOM_H
#define ROOM_H

#include <QDataStream>
#include <QString>

class BackEnd;

class Room {
public:
    friend QDataStream& operator<<(QDataStream &dataStream, const Room &room);
    friend QDataStream& operator>>(QDataStream &dataStream, Room &room);
private:
    QString name;
    friend class BackEnd;
};

#endif

#include "room.h"

QDataStream& operator<<(QDataStream &dataStream, const Room &room) {
    dataStream << room.name;
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Room &room) {
    dataStream >> room.name;
    return dataStream;
}

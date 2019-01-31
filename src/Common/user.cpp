#include "user.h"

QDataStream& operator<<(QDataStream &dataStream, const User &user) {
    dataStream << user.name;
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, User &user) {
    dataStream >> user.name;
    return dataStream;
}

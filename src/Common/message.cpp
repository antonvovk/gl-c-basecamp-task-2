#include "message.h"

QDataStream& operator<<(QDataStream &dataStream, const Message &message) {
    dataStream << message.text_data;
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Message &message) {
    dataStream >> message.text_data;
    return dataStream;
}

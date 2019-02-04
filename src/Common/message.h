#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDataStream>
#include <QString>

class BackEnd;

class Message {
public:
    friend QDataStream& operator<<(QDataStream &dataStream, const Message &message);
    friend QDataStream& operator>>(QDataStream &dataStream, Message &message);
private:
    QString text_data;
    friend class BackEnd;
};

#endif

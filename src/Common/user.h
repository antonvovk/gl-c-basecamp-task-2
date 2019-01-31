#ifndef USER_H
#define USER_H

#include <QDataStream>
#include <QString>

class BackEnd;

class User {
public:
    friend QDataStream& operator<<(QDataStream &dataStream, const User &user);
    friend QDataStream& operator>>(QDataStream &dataStream, User &user);
private:
    QString name;
    friend class BackEnd;
};

#endif

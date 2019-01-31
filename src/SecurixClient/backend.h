#ifndef BACKEND_H
#define BACKEND_H

#include <QSslSocket>
#include <QObject>
#include <QDebug>
#include "../Common/user.h"
#include "../Common/message.h"
#include "../Common/room.h"

class BackEnd : public QObject {
    Q_OBJECT
public:
    BackEnd(QObject *parent = nullptr);
public slots:
    void connectToSecureHost(const QString &hostname, const quint16 &port, const QString &username, const QString &roomname);
    void sendMessage(const QString &message_data_txt);
    void outputToUi();
    void disconnectFromSecureHost();
    void onReadyRead();
signals:
    void doUiData(QString historyB, QString users_listB);
private:
    QSslSocket sslSocket;
    User user, user_received;
    Room room;
    Message message, message_received;
    QString users_list, history;
};

#endif

#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
    QObject::connect(&this->sslSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    query.exec("CREATE TABLE `users`.`user` (`username` TEXT NULL DEFAULT NULL, "
                                            "`password` TEXT NULL DEFAULT NULL, "
                                            "`full_name` TEXT NULL DEFAULT NULL, "
                                            "`current_room` TEXT NULL DEFAULT NULL);");
}

BackEnd& BackEnd::instance() {
    static BackEnd instance;
    return instance;
}

void BackEnd::connectToSecureHost() {
    if (hostname.isEmpty()) {
        hostname = "127.0.0.1";
        port = 4444;
    }

    if (sslSocket.state() != QTcpSocket::ConnectedState) {
        sslSocket.addCaCertificates("sslserver.pem");
        sslSocket.connectToHostEncrypted(hostname, port);

        if (!sslSocket.waitForEncrypted(-1)) {
            // Add error handling here
            qDebug() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
            return;
        }

    }
}

void BackEnd::notifyServerOfNewMessage() {
    QDataStream stream(&sslSocket);
    stream << "New Message!";

    if (!sslSocket.waitForBytesWritten(-1)) {
        // Add error handling here
        qDebug() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";
        return;
    }
}

void BackEnd::disconnectFromSecureHost() {
    sslSocket.disconnectFromHost();
}

void BackEnd::onReadyRead() {
    emit doUiData();
}

QString BackEnd::getAuthor() {
    return SqlConversationModel::author;
}

void BackEnd::initFirstStage(QString hostname, quint16 port, const QString &username) {
    SqlConversationModel::author = username;
    this->hostname = hostname;
    this->port = port;
}

void BackEnd::addNewUserToDB(const QString &username, const QString &password, const QString &fullname) {
    const QString query_text = QString::fromLatin1("INSERT INTO users.user VALUES ('%1', '%2', '%3', '')").arg(username).arg(password).arg(fullname);
    query.exec(query_text);
}

bool BackEnd::checkCredentialsWithDB(const QString &username, const QString &password) {
    const QString query_text = QString::fromLatin1("SELECT * FROM  users.user WHERE username='%1';").arg(username);
    query.exec(query_text);
    query.first();

    return query.value(1) == password;
}

void BackEnd::updateCurrentRoom(const QString &roomname) {
    query.exec("SET SQL_SAFE_UPDATES=0;");
    const QString query_text = QString::fromLatin1("UPDATE users.user SET current_room='%1' WHERE username='%2';").arg(roomname).arg(SqlConversationModel::author);
    query.exec(query_text);
}

void BackEnd::notifyServerOfNewConnection(const QString &recipient) {
    SqlConversationModel tmp;
    tmp.sendMessage(recipient, SqlConversationModel::author + " has connected!");
    this->notifyServerOfNewMessage();
}

void BackEnd::notifyServerOfDisconnect(const QString &recipient) {
    SqlConversationModel tmp;
    tmp.sendMessage(recipient, SqlConversationModel::author + " has left!");
    this->notifyServerOfNewMessage();
}


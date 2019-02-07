#include "sslserver.h"

SslServer::SslServer(QObject *parent) : QTcpServer(parent), sslLocalCertificate(), sslPrivateKey(), sslProtocol(QSsl::UnknownProtocol) {

}

SslServer& SslServer::instance() {
    static SslServer instance;
    return instance;
}

void SslServer::incomingConnection(qintptr socketDescriptor) {
    QSslSocket *sslSocket = new QSslSocket(this);
    sslSocket->setSocketDescriptor(socketDescriptor);
    sslSocket->setLocalCertificate(sslLocalCertificate);
    sslSocket->setPrivateKey(sslPrivateKey);
    sslSocket->setProtocol(sslProtocol);
    sslSocket->startServerEncryption();

    this->addPendingConnection(sslSocket);
}

const QSslCertificate &SslServer::getSslLocalCertificate() const {
    return sslLocalCertificate;
}

const QSslKey &SslServer::getSslPrivateKey() const {
    return sslPrivateKey;
}

QSsl::SslProtocol SslServer::getSslProtocol() const {
    return sslProtocol;
}

void SslServer::setSslLocalCertificate(const QSslCertificate &certificate) {
    sslLocalCertificate = certificate;
}

bool SslServer::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format) {
    QFile certificateFile(path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        return false;

    sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}

void SslServer::setSslPrivateKey(const QSslKey &key) {
    sslPrivateKey = key;
}

bool SslServer::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase) {
    QFile keyFile(fileName);

    if (!keyFile.open(QIODevice::ReadOnly))
        return false;

    sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}

void SslServer::setSslProtocol(QSsl::SslProtocol protocol) {
    sslProtocol = protocol;
}

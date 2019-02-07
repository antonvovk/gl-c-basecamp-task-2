#ifndef SQLCONVERSATIONMODEL_H
#define SQLCONVERSATIONMODEL_H

#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

class BackEnd;
class SqlUserListModel;

class SqlConversationModel : public QSqlTableModel {
    Q_OBJECT
    Q_PROPERTY(QString recipient READ recipient WRITE setRecipient NOTIFY recipientChanged)
public:
    SqlConversationModel(QObject *parent = nullptr);
    QString recipient() const;
    void setRecipient(const QString &recipient);
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void sendMessage(const QString &recipient, const QString &message);
    Q_INVOKABLE void updateFromDB();
signals:
    void recipientChanged();
private:
    friend class BackEnd;
    friend class SqlUserListModel;
    QString m_recipient;
    static QString author, _recipient;
};

#endif

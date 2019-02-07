#include "sqlconversationmodel.h"

static const char *conversationsTableName = "Conversations";

QString SqlConversationModel::author = "", SqlConversationModel::_recipient = "";

static void createTable() {
    if (QSqlDatabase::database().tables().contains(conversationsTableName)) {
        // The table already exists; we don't need to do anything.
        return;
    }

    QSqlQuery query;
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS users.`Conversations` ("
        "`id` INT,"
        "`author` TEXT NOT NULL,"
        "`recipient` TEXT NOT NULL,"
        "`timestamp` TEXT NOT NULL,"
        "`message` TEXT NOT NULL,"
        "PRIMARY KEY(id))")) {

        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }

    query.exec("ALTER TABLE `users`.`conversations`"
        "DROP COLUMN `id`,"
        "DROP PRIMARY KEY;"
        ";");
}

SqlConversationModel::SqlConversationModel(QObject *parent) : QSqlTableModel(parent) {
    createTable();
    setTable(conversationsTableName);
    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QString SqlConversationModel::recipient() const {
    return m_recipient;
}

void SqlConversationModel::setRecipient(const QString &recipient) {
    if (recipient == m_recipient)
        return;

    m_recipient = recipient;
    _recipient = recipient;

    const QString filterString = QString::fromLatin1("recipient = '%1'").arg(m_recipient);
    setFilter(filterString);
    select();

    emit recipientChanged();
}

QVariant SqlConversationModel::data(const QModelIndex &index, int role) const {
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlConversationModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "author";
    names[Qt::UserRole + 1] = "recipient";
    names[Qt::UserRole + 2] = "timestamp";
    names[Qt::UserRole + 3] = "message";
    return names;
}

void SqlConversationModel::sendMessage(const QString &recipient, const QString &message) {
    const QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    QSqlRecord newRecord = record();
    newRecord.setValue("author", author);
    newRecord.setValue("recipient", recipient);
    newRecord.setValue("timestamp", timestamp);
    newRecord.setValue("message", message);
    if (!insertRecord(rowCount(), newRecord)) {
        qWarning() << "Failed to send message:" << lastError().text();
        return;
    }

    submitAll();
}

void SqlConversationModel::updateFromDB() {
    submitAll();
}


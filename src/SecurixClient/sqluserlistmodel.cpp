#include "sqluserlistmodel.h"

static const char *conversationsTableName = "User";

SqlUserListModel::SqlUserListModel(QObject *parent) : QSqlTableModel(parent) {
    setTable(conversationsTableName);
    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);

    QSqlQuery query;
    QString query_text = QString::fromLatin1("SELECT * FROM users.user WHERE username = '%1';").arg(SqlConversationModel::author);
    query.exec(query_text);
    query.first();

    const QString filterString = QString::fromLatin1("current_room = '%1'").arg(query.value(3).toString());
    setFilter(filterString);
    select();
}

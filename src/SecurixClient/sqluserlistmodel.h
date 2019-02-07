#ifndef SQLUSERLISTMODEL_H
#define SQLUSERLISTMODEL_H

#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include "sqlconversationmodel.h"

class SqlUserListModel : public QSqlTableModel {
public:
    SqlUserListModel(QObject *parent = nullptr);
};

#endif

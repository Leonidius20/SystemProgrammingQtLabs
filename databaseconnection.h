#pragma once

#include <QString>
#include <QSqlDatabase>

class DatabaseConnection
{
private:
    QSqlDatabase db;

public:
    DatabaseConnection();

    const QSqlDatabase &get() { return db; }

    ~DatabaseConnection();
};

#pragma once

#include <QString>
#include <QSqlDatabase>

class DatabaseConnection
{
private:
    QSqlDatabase db;

public:
    DatabaseConnection();
    ~DatabaseConnection();
};

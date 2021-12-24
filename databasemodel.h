#pragma once

#include <QList>
#include <QStandardItem>
#include <QString>
#include "imodel.h"
#include "databaseconnection.h"

class DatabaseModel : public IModel
{
private:
    DatabaseConnection *connection;
public:
    DatabaseModel();

    QList<QList<QStandardItem*>> getAll() override;

    void update(const QList<QList<QString>> &changedItems) override;

    ~DatabaseModel() override;
};


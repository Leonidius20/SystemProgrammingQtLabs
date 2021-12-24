#include "databasemodel.h"

DatabaseModel::DatabaseModel()
{
    this->connection = new DatabaseConnection();
}

QList<QList<QStandardItem*>> DatabaseModel::getAll() {

}

void DatabaseModel::update(const QList<QList<QString>> &changedItems) {

}

DatabaseModel::~DatabaseModel() {
    delete connection;
}

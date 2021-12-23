#include "imodel.h"
#include "databaseconnection.h"

DatabaseConnection::DatabaseConnection()
{
    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setHostName("localhost");
    this->db.setPort(5432);
    this->db.setDatabaseName("hotels");
    this->db.setUserName("postgres");
    db.open();
}

DatabaseConnection::~DatabaseConnection() {
    db.close();
}

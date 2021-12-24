#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <vector>
#include "hotel/hotel.h"
#include "csvfilemodel.h"
#include "databaseconnection.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void handleSearchButton();
    void handleAddButton();
    void handleDeleteButton();

    void handleMenuOpen();
    void handleMenuSave();
    void handleMenuSaveAs();
    void handleMenuConnectDb();

    void clearTable();


private:
    const QString MODEL_FILE = "file";
    const QString MODEL_DB = "db";

    QLineEdit *searchBox;
    QTextEdit *textBox;

    std::vector<hotelSystem::Hotel> hotels;
    std::vector<hotelSystem::Hotel> deletedHotels;

    IModel *dataModel;

    QTableView *tableView;
    QAbstractItemModel *tableModel;
    QSqlTableModel *sqlTableModel;


    DatabaseConnection *connection;

    QString modelType = MODEL_FILE;

    void createMenu();

    QList<QList<QString>> getConvertedData();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

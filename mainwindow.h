#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>
#include <QTableView>
#include <QStandardItemModel>
#include <vector>
#include "hotel/hotel.h"
#include "csvfilemodel.h"

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

    void clearTable();


private:
    QLineEdit *searchBox;
    QTextEdit *textBox;

    std::vector<hotelSystem::Hotel> hotels;
    std::vector<hotelSystem::Hotel> deletedHotels;

    CsvFileModel *csvFileModel;

    QTableView *tableView;
    QStandardItemModel *tableModel;

    void createMenu();

    QList<QList<QString>> getConvertedData();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

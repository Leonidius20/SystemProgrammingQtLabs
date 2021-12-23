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

    void writeToFile(QFile *file);

private:
    QLineEdit *searchBox;
    QTextEdit *textBox;

    std::vector<hotelSystem::Hotel> hotels;
    std::vector<hotelSystem::Hotel> deletedHotels;

    QFile *file;

    QTableView *tableView;
    QStandardItemModel *tableModel;

    void createMenu();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

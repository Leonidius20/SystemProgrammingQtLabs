#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
#include <QSqlTableModel>
#include "csvtablemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dataModel = nullptr;
    connection = new DatabaseConnection();

    setWindowTitle("Hotel");
    setGeometry(100, 100, 1290, 720);
    setMinimumSize(200, 200);

    searchBox = new QLineEdit(this);
    searchBox->setGeometry(10, 50, 1200, 20);

    QPushButton *searchButton = new QPushButton("Search", this);
    searchButton->setGeometry(1220, 50, 60, 20);
    connect(searchButton, SIGNAL(released()), this, SLOT(handleSearchButton()));


    //textBox = new QTextEdit(this);
    //textBox->setGeometry(10, 80, 1270, 30);

    tableView = new QTableView(this);
    tableView->setGeometry(10, 80, 1270, 600);

    csvTableModel = new QStandardItemModel(this);
    csvTableModel->setColumnCount(8);
    clearTable();
    tableView->setModel(csvTableModel);

    QPushButton *addButton = new QPushButton("Add", this);
    addButton->setGeometry(10, 690, 60, 20);
    connect(addButton, SIGNAL(released()), this, SLOT(handleAddButton()));

    QPushButton *deleteButton = new QPushButton("Delete", this);
    deleteButton->setGeometry(80, 690, 60, 20);
    connect(deleteButton, SIGNAL(released()), this, SLOT(handleDeleteButton()));


    createMenu();
}

void MainWindow::createMenu() {
    auto fileMenu = menuBar()->addMenu("File");

    auto openAction = new QAction("Open", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::handleMenuOpen);
    fileMenu->addAction(openAction);

    auto connectToDbAction = new QAction("Connect to DB", this);
    connect(connectToDbAction, &QAction::triggered, this, &MainWindow::handleMenuConnectDb);
    fileMenu->addAction(connectToDbAction);

    auto saveAction = new QAction("Save", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::handleMenuSave);
    saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    fileMenu->addAction(saveAction);

    auto saveAsAction = new QAction("Save As", this);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::handleMenuSaveAs);
    fileMenu->addAction(saveAsAction);

    auto clearDataAction = new QAction("Clear Data", this);
    connect(clearDataAction, &QAction::triggered, this, &MainWindow::clearTable);
    fileMenu->addAction(clearDataAction);
}

void MainWindow::handleSearchButton() {
    // textBox->setText(searchBox->text());
}

void MainWindow::handleMenuOpen() {
    QString path = QFileDialog::getOpenFileName(this, "Open hotel list file", QDir::homePath(), "csv files(*.csv)");

    if (!path.isEmpty()) {
        clearTable();

        dataModel = new CsvFileModel(path);
        auto data = dataModel->getAll();

        for (auto row: data) {
            csvTableModel->insertRow(csvTableModel->rowCount(), row);
        }

        modelType = MODEL_FILE;
    }

}

void MainWindow::handleMenuConnectDb() {
    sqlTableModel = new QSqlTableModel(this);
    sqlTableModel->setTable("hotels");
    sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    sqlTableModel->setHeaderData(0, Qt::Horizontal, "Code");
    sqlTableModel->setHeaderData(1, Qt::Horizontal, "Name");
    sqlTableModel->select();
    tableView->setModel(sqlTableModel);
    modelType = MODEL_DB;
}

void MainWindow::handleMenuSave() {
    if (dataModel != nullptr && modelType == MODEL_FILE) {
        dataModel->update(getConvertedData());
    } else if (sqlTableModel != nullptr && modelType == MODEL_DB) {
        sqlTableModel->submitAll();
    } else handleMenuSaveAs();
}

void MainWindow::handleMenuSaveAs() {
    if (modelType == MODEL_FILE) {
        QString path = QFileDialog::getSaveFileName(this, "Save hotel data", QDir::homePath(), "csv files(*.csv)");
        if (!path.isEmpty()) {
            if (dataModel != nullptr) delete dataModel;
            dataModel = new CsvFileModel(path);

            dataModel->update(getConvertedData());
        }
    }
}

void MainWindow::clearTable() {
    if (dataModel != nullptr) {
        delete dataModel;
        dataModel = nullptr;
    }

    if (modelType == MODEL_FILE) {
        csvTableModel->clear();
        csvTableModel->setHorizontalHeaderLabels(
                    QStringList() << "Code" << "Name" << "Country"
                   << "City" << "Address" << "Stars" << "Contact Name" << "Contact Phone");
    }
}

QList<QList<QString>> MainWindow::getConvertedData() {
    QList<QList<QString>> result;
    int rows = csvTableModel->rowCount();
    int columns = csvTableModel->columnCount();
    for (int i = 0; i < rows; i++) {
        QList<QString> row;
        for (int j = 0; j < columns; j++) {
            row.append(csvTableModel->data(csvTableModel->index(i, j)).toString());
        }
        result.append(row);
    }
    return result;
}

void MainWindow::handleAddButton() {
    if (modelType == MODEL_FILE) {
        int row = csvTableModel->rowCount();
        csvTableModel->insertRow(row);
        QModelIndex index = csvTableModel->index(row, 0);
        tableView->setCurrentIndex(index);
        tableView->edit(index);
    } else {
        int row = sqlTableModel->rowCount();
        sqlTableModel->insertRow(row);
        QModelIndex index = sqlTableModel->index(row, 0);
        tableView->setCurrentIndex(index);
        tableView->edit(index);
    }

}

void MainWindow::handleDeleteButton() {
    if (modelType == MODEL_FILE) {
        csvTableModel->removeRows(tableView->currentIndex().row(), 1);
    } else {
        sqlTableModel->removeRows(tableView->currentIndex().row(), 1);
    }
}

MainWindow::~MainWindow()
{
    if (dataModel != nullptr) delete dataModel;
    delete connection;
}

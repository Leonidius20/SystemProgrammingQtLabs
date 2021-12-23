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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    csvFileModel = nullptr;

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

    tableModel = new QStandardItemModel(this);
    tableModel->setColumnCount(8);
    clearTable();
    tableView->setModel(tableModel);

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
        csvFileModel = new CsvFileModel(path);
        auto data = csvFileModel->getAll();

        for (auto row: data) {
            tableModel->insertRow(tableModel->rowCount(), row);
        }
    }

}

void MainWindow::handleMenuSave() {
    if (csvFileModel != nullptr) {
        csvFileModel->update(getConvertedData());
    } else handleMenuSaveAs();
}

void MainWindow::handleMenuSaveAs() {
    QString path = QFileDialog::getSaveFileName(this, "Save hotel data", QDir::homePath(), "csv files(*.csv)");
    if (!path.isEmpty()) {
        if (csvFileModel != nullptr) delete csvFileModel;
        csvFileModel = new CsvFileModel(path);

        csvFileModel->update(getConvertedData());
    }
}

void MainWindow::clearTable() {
    if (csvFileModel != nullptr) {
        delete csvFileModel;
        csvFileModel = nullptr;
    }

    tableModel->clear();
    tableModel->setHorizontalHeaderLabels(
                QStringList() << "Code" << "Name" << "Country"
                << "City" << "Address" << "Stars" << "Contact Name" << "Contact Phone");
}

QList<QList<QString>> MainWindow::getConvertedData() {
    QList<QList<QString>> result;
    int rows = tableModel->rowCount();
    int columns = tableModel->columnCount();
    for (int i = 0; i < rows; i++) {
        QList<QString> row;
        for (int j = 0; j < columns; j++) {
            row.append(tableModel->data(tableModel->index(i, j)).toString());
        }
        result.append(row);
    }
    return result;
}

void MainWindow::handleAddButton() {
    int row = tableModel->rowCount();
    tableModel->insertRow(row);
    QModelIndex index = tableModel->index(row, 0);
    tableView->setCurrentIndex(index);
    tableView->edit(index);
}

void MainWindow::handleDeleteButton() {
    tableModel->removeRows(tableView->currentIndex().row(), 1);
}

MainWindow::~MainWindow()
{
    if (csvFileModel != nullptr) delete csvFileModel;
}

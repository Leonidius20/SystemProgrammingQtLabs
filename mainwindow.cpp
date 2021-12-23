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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    tableModel->setColumnCount(6);
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
    fileMenu->addAction(saveAction);

    auto saveAsAction = new QAction("Save As", this);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::handleMenuSaveAs);
    fileMenu->addAction(saveAsAction);

    auto clearDataAction = new QAction("Clear Data", this);
    connect(clearDataAction, &QAction::triggered, this, &MainWindow::clearTable);
    fileMenu->addAction(clearDataAction);
}

void MainWindow::handleSearchButton() {
    textBox->setText(searchBox->text());
}

void MainWindow::handleMenuOpen() {
    QString path = QFileDialog::getOpenFileName(this, "Open hotel list file", "/~", "csv files(*.csv)");
    if (!path.isEmpty()) {
        clearTable();

        file = new QFile(path);
        if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(file);
            while (!stream.atEnd()) {
                QString line = stream.readLine();
                QList<QStandardItem*> items;
                for (QString item : line.split(",")) {
                    items.append(new QStandardItem(item));
                }
                tableModel->insertRow(tableModel->rowCount(), items);
            }
            file->close();
        }
    }
}

void MainWindow::handleMenuSave() {
    if (file != nullptr) {
        writeToFile(file);
    } else handleMenuSaveAs();
}

void MainWindow::handleMenuSaveAs() {
    QString path = QFileDialog::getSaveFileName(this, "Save hotel data", "/~", "csv files(*.csv)");
    if (!path.isEmpty()) {
        file = new QFile(path);
        writeToFile(file);
    }
}

void MainWindow::clearTable() {
    file = nullptr;
    tableModel->clear();
    tableModel->setHorizontalHeaderLabels(
                QStringList() << "Code" << "Name" << "Country"
                << "City" << "Address" << "Stars");
}

void MainWindow::writeToFile(QFile *file) {
    if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString textData;
        int rows = tableModel->rowCount();
        int columns = tableModel->columnCount();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                textData += tableModel->data(tableModel->index(i, j)).toString();
                if (j != columns - 1) textData += ",";
            }
            textData += "\n";
        }

        QTextStream out(file);
        out << textData;
        file->close();
    }
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

}

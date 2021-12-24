#include <QTextStream>
#include "csvtablemodel.h"

CsvTableModel::CsvTableModel(const QString &filePath)
{
    file = new QFile(filePath);

    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QList<QVariant> items;
            for (QString item : line.split(",")) {
                items.append(QVariant(item));
            }
            tableData.append(items);
        }
        file->close();
    }
}

int CsvTableModel::rowCount(const QModelIndex &parent) const {
    return tableData.size();
}

int CsvTableModel::columnCount(const QModelIndex &parent) const {
    return 8;
}

QVariant CsvTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
             return QVariant();

         if (index.row() >= tableData.size())
             return QVariant();

         if (role == Qt::DisplayRole)
             return tableData[index.row()];//[index.column()];
         else
             return QVariant();
}

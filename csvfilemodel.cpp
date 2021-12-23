#include <QTextStream>
#include <QString>
#include <QStandardItem>
#include "csvfilemodel.h"

CsvFileModel::CsvFileModel(const QString &fileName)
{
    this->file = new QFile(fileName);
}

QList<QList<QStandardItem*>> CsvFileModel::getAll() {
    QList<QList<QStandardItem*>> result;
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QList<QStandardItem*> items;
            for (QString item : line.split(",")) {
                items.append(new QStandardItem(item));
            }
            result.append(items);
        }
        file->close();
    }
    return result;
}

void CsvFileModel::update(const QList<QList<QString>> &changedItems) {
    if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString textData;
        int rows = changedItems.size();
        if (rows == 0) return;
        int columns = changedItems[0].size();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                textData += changedItems[i][j];
                if (j != columns - 1) textData += ",";
            }
            textData += "\n";
        }

        QTextStream out(file);
        out << textData;
        file->close();
    }
}

CsvFileModel::~CsvFileModel() {
    delete file;
}

#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QString>
#include <QFile>
#include <QList>

class CsvTableModel : public QAbstractTableModel {
    Q_OBJECT
private:
     QFile *file;
     QList<QVariant> tableData;
public:
    CsvTableModel(const QString &filePath);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};

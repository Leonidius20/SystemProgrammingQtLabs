#pragma once

#include <QFile>
#include <QString>
#include "imodel.h"

class CsvFileModel : public IModel
{
private:
    QFile *file;
public:
    CsvFileModel(const QString &fileName);

    QList<QList<QStandardItem*>> getAll() override;

    void update(const QList<QList<QString>> &changedItems) override;

    ~CsvFileModel() override;
};


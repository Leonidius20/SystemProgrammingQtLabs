#pragma once

#include <QList>
#include <QStandardItem>
#include <QString>

class IModel
{
public:
    virtual QList<QList<QStandardItem*>> getAll() = 0;
    virtual void update(const QList<QList<QString>> &changedItems) = 0;
    virtual ~IModel() {}
};

#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H
#include <QAbstractListModel>
#include <QTime>
#include <QQueue>
#include <QList>
#include "task.h"

class MemoryModel : public QAbstractListModel
{
public:
    MemoryModel(const QQueue<Task>& ataskQueue = {});

    QQueue<Task> getTaskQueue();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;


    virtual bool addTask(const Task &task);
    virtual void removeTask(const Task &task);

    void clearTask();
    virtual QList<Task> step(int number);

protected:
    QQueue<Task> taskQueue;

    inline virtual QList<QString> getNameColumns() const;
    inline virtual QVariant getDataInRowColumn(const QModelIndex &index) const;
};

#endif // MEMORYMODEL_H

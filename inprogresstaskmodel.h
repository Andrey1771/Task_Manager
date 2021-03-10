#ifndef INPROGRESSTASKMODEL_H
#define INPROGRESSTASKMODEL_H
#include "memorymodel.h"

class InProgressTaskModel : public MemoryModel
{
    ///
    /// \brief Идея такова, что мы храним адрес задач для нашей модели, он может и должен повторятся столько раз
    /// каков размер самой задачи
    ///
    QVector<Task*> fieldsMemory;

public:
    InProgressTaskModel(uint memorySize, const QQueue<Task> &ataskQueue = {});


    virtual bool addTask(const Task &task) override;
    virtual void removeTask(const Task& task) override;

    int findMemory(uint taskSize);
    QList<Task> step(int number) override;
    void setMemorySize(uint newMemorySize);

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;

    // MemoryModel interface
protected:
    virtual QList<QString> getNameColumns() const override;
    virtual QVariant getDataInRowColumn(const QModelIndex &index) const override;
};

#endif // INPROGRESSTASKMODEL_H

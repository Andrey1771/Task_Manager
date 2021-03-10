#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "memorymodel.h"
#include <QTimer>
#include "inprogresstaskmodel.h"
#include <QObject>

///
/// \brief По сути, он выполняет роль контроллера в паттерне MVC,
///  который соблюден при разработке данных моделей
///
class MemoryManager : public QObject
{
    Q_OBJECT
public:
    MemoryManager();

    QTimer timer;
    int numberStep;

    MemoryModel *taskInQueueModel{nullptr};
    InProgressTaskModel *inProgressModel{nullptr};
    MemoryModel *finishedTaskModel{nullptr};
    MemoryModel *elapsedTimeModel{nullptr};

    void setModels(MemoryModel *ataskInQueueModel,
                   InProgressTaskModel *ainProgressModel,
                   MemoryModel *afinishedTaskModel,
                   MemoryModel *aelapsedTimeModel);

    void startWork();
    void stopWork();

private slots:
    void oneStep();

signals:
    void tick(int numberTick);
};

#endif // MEMORYMANAGER_H

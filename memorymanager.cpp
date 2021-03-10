#include "memorymanager.h"

MemoryManager::MemoryManager()
{
    timer.stop();
    connect(&timer, &QTimer::timeout, this, &MemoryManager::oneStep);//Конектим таймер к нашему слоту
}

///
/// \brief Устанавливает различные модели в наш менеджер
///
void MemoryManager::setModels(MemoryModel *ataskInQueueModel, InProgressTaskModel *ainProgressModel, MemoryModel *afinishedTaskModel, MemoryModel *aelapsedTimeModel)
{
    taskInQueueModel = ataskInQueueModel;
    inProgressModel = ainProgressModel;
    finishedTaskModel = afinishedTaskModel;
    elapsedTimeModel = aelapsedTimeModel;
    numberStep = 0;
}

///
/// \brief Запускает таймер
///
void MemoryManager::startWork()
{
    timer.start(1000);//1 sec
}

///
/// \brief Останавливает работу таймера
///
void MemoryManager::stopWork()
{
    timer.stop();
}

///
/// \brief Выполняет шаг для наших моделей, вызывается при срабатывании таймера
///
void MemoryManager::oneStep()
{
    numberStep++;
    auto finishedTasks = inProgressModel->step(numberStep);
    for(auto task : finishedTasks)
    {
        finishedTaskModel->addTask(task);
    }

    auto elapsedTasks = taskInQueueModel->step(numberStep);
    for(auto task : elapsedTasks)
        elapsedTimeModel->addTask(task);

    auto tasks = taskInQueueModel->getTaskQueue();
    for(auto i = 0; i < tasks.size(); ++i)
    {
        if(inProgressModel->addTask(tasks[i]))
        {
            taskInQueueModel->removeTask(tasks[i]);
        }
    }

    emit tick(numberStep);
}

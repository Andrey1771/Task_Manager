#include "inprogresstaskmodel.h"
#include <set>

InProgressTaskModel::InProgressTaskModel(uint memorySize, const QQueue<Task> &ataskQueue) : MemoryModel(ataskQueue)
{
    fieldsMemory.resize(static_cast<int>(memorySize));

    for(int i = 0; i < fieldsMemory.size(); ++i)
    {
        fieldsMemory[i] = nullptr;
    }
}

///
/// \brief Добавляет задачу в нашу модель
/// \param task - Сама задача
/// \return
///
bool InProgressTaskModel::addTask(const Task& task)
{
    int k = 0;
    Task *taskTemp = new Task(task);
    if((k = findMemory(task.size)) != -1)
    {
        for(int i = k; i < k + static_cast<int>(task.size); ++i)
            fieldsMemory[i] = taskTemp;
        return MemoryModel::addTask(task);
    }
    return false;
}


///
/// \brief Удаляет задачу из модели
/// \param task - Сама задача
///
void InProgressTaskModel::removeTask(const Task &task)
{
    QList<int> indexes;
    for(int i = 0; i < fieldsMemory.size(); ++i)
    {
        if(fieldsMemory[i] == &task)
        {
            indexes.push_back(i);
            break;
        }
    }
    for(auto index : indexes)
    {
        fieldsMemory[index] = nullptr;
    }

    return MemoryModel::removeTask(task);
}

///
/// \brief Ищет конретную свободную область в памяти
/// \param taskSize - размер нашей задачи
/// \return Возвращает номер, начала свободных ячеек, в случае, если ячейка не найдена, вернет -1
///
int InProgressTaskModel::findMemory(uint taskSize)
{
    uint number = 0;//Можно убрать
    int pos = -1;
    for(int i = 0; i < fieldsMemory.size(); ++i)
    {
        if(fieldsMemory[i] == nullptr)
        {
            if(pos == -1)
            {
                pos = i;
            }
            number++;

            if(number == taskSize)
                return pos;
        }
        else
        {
            pos = -1;
            number = 0;
        }
    }
    return -1;
}

///
/// \brief Выполняет один шаг для нашей модели
/// \return Возвращает список выполненных задач
///
QList<Task> InProgressTaskModel::step(int /*number*/)
{
    std::set<Task> setTemp;
    QList<Task> painList;
    Task *lastTask = nullptr;
    for(int i = 0; i < fieldsMemory.size(); ++i)
    {
        if(lastTask != fieldsMemory[i] && fieldsMemory[i] != nullptr)
        {
            if(fieldsMemory[i]->remainingTime == 0)
            {
                setTemp.insert(*fieldsMemory[i]);
                painList.push_back(*fieldsMemory[i]);
                removeTask(*fieldsMemory[i]);
            }
            else
            {
                --fieldsMemory[i]->remainingTime;
                lastTask = fieldsMemory[i];
            }
        }
        lastTask = fieldsMemory[i];
    }

    QList<Task> taskList;
    for(auto task : setTemp)
    {
        taskList.append(task);
    }
    emit dataChanged(QModelIndex(), QModelIndex());
    return taskList;
}

///
/// \brief Устанавливаем размер памяти для модели
/// \param newMemorySize - сам размер
///
void InProgressTaskModel::setMemorySize(uint newMemorySize)
{
    fieldsMemory.resize(static_cast<int>(newMemorySize));
}

///
/// \brief Возвращает названия колонок
/// \return
///
QList<QString> InProgressTaskModel::getNameColumns() const
{
    auto list = MemoryModel::getNameColumns();
    list.append("RemainingTime");
    return list;
}

///
/// \brief Возвращает данные для ячейки, в специальном Q-шном формате
/// \param index - сам индекс
/// \return
///
QVariant InProgressTaskModel::getDataInRowColumn(const QModelIndex &index) const
{
    if(index.column() == 4)
    {
        if(fieldsMemory[index.row()] != nullptr)
            return fieldsMemory[index.row()]->remainingTime;
    }
    return MemoryModel::getDataInRowColumn(index);
}

///
/// \brief Возвращает количество строк
/// \param parent - QModelIndex родителя для строки, он не нужен, тк данная модель не древовидная
/// \return
///
int InProgressTaskModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return fieldsMemory.size();
}

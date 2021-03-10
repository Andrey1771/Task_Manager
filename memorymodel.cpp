#include "memorymodel.h"
#include <QModelIndex>

MemoryModel::MemoryModel(const QQueue<Task> &ataskQueue)
{
    taskQueue = ataskQueue;
}

///
/// \brief возвращает объект очереди taskQueue
/// \return возвращает новый объект, который является копией данной очереди
///
QQueue<Task> MemoryModel::getTaskQueue()
{
    return taskQueue;
}

///
/// \brief Считает количество строк
/// \return количество строк
///
int MemoryModel::rowCount(const QModelIndex &/*parent*/) const
{
    return taskQueue.size();
}

///
/// \brief Отображает данные данной модели
/// \param index - индекс элемента (там номер строки и колонки есть, это самое главное)
/// \param role - роль данного запроса к data, есть различные роли, примеры:
///  роль отображения данных или изменения, каждая вызывается в конкретной ситуации
/// \return возвращает сами данные в специальном Q-шном стиле (QVariant)
///
QVariant MemoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= taskQueue.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return getDataInRowColumn(index);
    }
    else
        return QVariant();
}

///
/// \brief Возвращает название строки или столбца
/// \param section - это номер строки или столбца
/// \param orientation - это ориентация строки, может быть вертикальной или горизонтальной
/// \param role - роль данного запроса к headerData, есть различные роли, примеры:
///  роль отображения данных или изменения, каждая вызывается в конкретной ситуации
/// \return
///
QVariant MemoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return getNameColumns().at(section);
    else
        return QString("%1").arg(section);

}

///
/// \brief Возвращает названия вертикальных колонок для нашей модели
/// \return
///
QList<QString> MemoryModel::getNameColumns() const
{
    return QList<QString>{"Name", "Size", "MaxStartTime", "WorkTime"};
}

///
/// \brief Возвращает данные для конретной ячейки в таблице
/// \param index - индекс элемента (там номер строки и колонки есть, это самое главное)
/// \return
///
QVariant MemoryModel::getDataInRowColumn(const QModelIndex &index) const
{
    switch(index.column())
    {
    case 0:
        return taskQueue.at(index.row()).name;
    case 1:
        return taskQueue.at(index.row()).size;
    case 2:
        return taskQueue.at(index.row()).maxStartTime;
    case 3:
        return taskQueue.at(index.row()).workTime;

    default:
        return QVariant();
    }
}

///
/// \brief Возвращает количество вертикальных колонок в нашей модели
/// \param parent - QModelIndex родителя для нашей строки, он не нужен, тк данная модель не древовидная
/// \return
///
int MemoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return getNameColumns().size();
}

///
/// \brief Добавляет задачу в нашу модель
/// \param task - Сама задача
/// \return
///
bool MemoryModel::addTask(const Task &task)
{
    insertRows(taskQueue.size(), 1, QModelIndex());
    taskQueue.last() = Task(task);

    return true;
}

///
/// \brief Удаляет задачу из модели
/// \param task - Сама задача
///
void MemoryModel::removeTask(const Task &task)
{
    auto index = taskQueue.indexOf(task);
    if(index != -1)
        removeRows(index, 1, QModelIndex());
}

///
/// \brief Очищает список задач для модели
///
void MemoryModel::clearTask()
{
    removeRows(0, taskQueue.size(), QModelIndex());
}

///
/// \brief Выполняет шаг для нашей модели
/// \param number - номер шага, получает от таймера
/// \return
///
QList<Task> MemoryModel::step(int number)
{
    auto list = QList<Task>();
    for(auto i = 0; i < taskQueue.size(); ++i)
    {
        if(taskQueue[i].maxStartTime < number)
        {
            list.append(taskQueue[i]);
            removeRows(i, 1, QModelIndex());
            --i;
        }
    }
    return list;
}

///
/// \brief Вставляет строки в нашу модель
/// \param row - номер строки, куда будет произведена вставка
/// \param count - количесвто строк
/// \param parent - QModelIndex родителя для нашей строки, он не нужен, тк данная модель не древовидная
/// \return
///
bool MemoryModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    taskQueue.push_back(Task());
    endInsertRows();

    return true;
}

///
/// \brief Удаляет строки в нашей модели
/// \param row - номер строки, которая будет удалена
/// \param count - количество строк, которые будут удалены
/// \param parent - QModelIndex родителя для нашей строки, он не нужен, тк данная модель не древовидная
/// \return
///
bool MemoryModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(taskQueue.size() == 0)
        return true;
    if(taskQueue.size() < row + count)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    for(int i = row; i < row + count; ++i)
        taskQueue.removeAt(row);
    endRemoveRows();

    return true;
}

#include "task.h"
#include <tuple>

Task::Task(QString aname, uint asize, int amaxStartTime, int aworkTime)
{
    name = aname;
    size = asize;
    maxStartTime = amaxStartTime;
    workTime = aworkTime;
    remainingTime = workTime;
}

///
/// \brief Оператор <, необходим для использования структуры данных set
/// \param right - объект расположенные справа от оператора <
/// \return Возвращаем результат сравнения истина или ложь
///
bool Task::operator<(const Task &right)
{
    std::tuple<QString, uint, int, int> leftTuple(name, size,
                                                  maxStartTime, workTime);
    std::tuple<QString, uint, int, int> rightTuple(right.name,
                                                   right.size, right.maxStartTime, right.workTime);

    if(leftTuple < rightTuple)
        return true;

    return false;
}

///
/// \brief Оператор ==, необходим для использования indexOf в очереди
/// \param right - объект расположенные справа от оператора ==
/// \return Возвращаем результат сравнения истина или ложь
///
bool Task::operator==(const Task &right) const
{
    std::tuple<QString, uint, int, int> leftTuple(name, size,
                                                  maxStartTime, workTime);
    std::tuple<QString, uint, int, int> rightTuple(right.name,
                                                   right.size, right.maxStartTime, right.workTime);

    if(leftTuple == rightTuple)
        return true;

    return false;
}

///
/// \brief Оператор <, необходим для использования структуры данных set
/// \param left - объект расположенные справа от оператора ==
/// \param right - объект расположенные справа от оператора ==
/// \return Возвращаем результат сравнения истина или ложь
///
bool operator<(const Task &left, const Task &right)
{
    std::tuple<QString, size_t, int, int> leftTuple(left.name, left.size,
                                                    left.maxStartTime, left.workTime);
    std::tuple<QString, size_t, int, int> rightTuple(right.name,
                                                     right.size, right.maxStartTime, right.workTime);

    if(leftTuple < rightTuple)
        return true;

    return false;
}

///
/// \brief Выполняем один шаг, тем самым уменьшаем оставшиеся время работы на 1
///
void Task::stepWork()
{
    --remainingTime;
}

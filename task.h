#ifndef TASK_H
#define TASK_H
#include <QString>

struct Task
{
    QString name;
    uint size;
    int maxStartTime;
    int workTime;
    int remainingTime;

    Task(QString aName = "", uint aSize = 0, int aMaxStartTime = 0, int aWorkTime = 0);

    bool operator<(const Task &right);
    bool operator==(const Task &right) const;

    friend bool operator<(const Task &left, const Task &right);

    void stepWork();
};

#endif // TASK_H

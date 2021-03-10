#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingsdialog.h"
#include "memorymanager.h"
#include <QMainWindow>

class InProgressTaskModel;
class MemoryModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    MemoryModel *taskInQueueModel{nullptr};
    InProgressTaskModel *inProgressModel{nullptr};
    MemoryModel *finishedTaskModel{nullptr};
    MemoryModel *elapsedTimeModel{nullptr};

    MemoryManager memoryManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_randPushButton_clicked();
    void setSettings(AnswerData data);

    void on_pausePushButton_clicked();
    void on_startPushButton_clicked();

private:
    Ui::MainWindow *ui;

    void randomizeData(const AnswerData& data);
    void updateTimerLabel(int numberTick);

};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inprogresstaskmodel.h"
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time_t());//Генерация зерна

    //Установка моделей
    taskInQueueModel = new MemoryModel();
    inProgressModel = new InProgressTaskModel(0);
    finishedTaskModel = new MemoryModel();
    elapsedTimeModel = new MemoryModel();


    ui->taskInQueueTableView->setModel(taskInQueueModel);
    ui->inProgressTaskTableView->setModel(inProgressModel);
    ui->finishedTaskTableView->setModel(finishedTaskModel);
    ui->elapsedTimeTableView->setModel(elapsedTimeModel);
    //

    //Установка моделей для менеджера памяти
    memoryManager.setModels(taskInQueueModel, inProgressModel, finishedTaskModel, elapsedTimeModel);

    //Соединение сигналов кнопок и менеджера памяти
    connect(&memoryManager, &MemoryManager::tick, this, &MainWindow::updateTimerLabel);
    connect(ui->pausePushButton, &QPushButton::clicked, this, &MainWindow::on_pausePushButton_clicked);
    connect(ui->startPushButton, &QPushButton::clicked, this, &MainWindow::on_startPushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief вызывает диалоговое окно для выбора настроек рандомизации задач
///
void MainWindow::on_randPushButton_clicked()
{
    SettingsDialog *dialog = new SettingsDialog(this);
    connect(dialog, &SettingsDialog::answerDataSend, this, &MainWindow::setSettings);
    dialog->exec();
}

///
/// \brief устанавливает настройки для рандомайзера задач
/// \param данные настроек для рандомайзера
///
void MainWindow::setSettings(AnswerData data)
{
    randomizeData(data);
}

///
/// \brief приостанавливает работу менеджера памяти
///
void MainWindow::on_pausePushButton_clicked()
{
    memoryManager.stopWork();
}

///
/// \brief возобновляет работу менеджера памяти
///
void MainWindow::on_startPushButton_clicked()
{
    memoryManager.startWork();
}

///
/// \brief генерирует рандомное слово
/// \param длина слова
/// \return
///
QString randomWord(int lenght)
{
    QString str;
    for(int i = 0; i < lenght; ++i)
        str += char('a' + rand() % ('z' - 'a'));
    return str;
}

///
/// \brief Рандомайзер,
/// генерирует рандомные задачи, заполняет их в модели, обновляет данные формы //нарушается принцип Solid :)
/// \param данные настроек для рандомайзера
///
void MainWindow::randomizeData(const AnswerData &data)
{
    memoryManager.stopWork();
    memoryManager.setModels(taskInQueueModel, inProgressModel, finishedTaskModel, elapsedTimeModel);

    taskInQueueModel->clearTask();

    inProgressModel->setMemorySize(data.memorySize);
    std::multiset<Task> tasks;
    for(int i = 0; i < data.taskCount; ++i)
    {
        tasks.insert(Task(randomWord(5), static_cast<uint>(rand() % data.memoryTask) + 1,
                          rand() % data.timeStart + 1, rand() % data.timeEnd + 1));
    }

    for(auto task : tasks)
    {
        taskInQueueModel->addTask(task);
    }

    ui->memoryLabel->setText(tr("Memory: %1").arg(data.memorySize));
}

///
/// \brief Обновляет время на форме при возникновении сигнала от таймера менеджера
/// \param номер данного тика, полученного от таймера (сколько раз таймер уже прошел оборот)
///
void MainWindow::updateTimerLabel(int numberTick)
{
    ui->timerLabel->setText(tr("time: %1").arg(numberTick));
}


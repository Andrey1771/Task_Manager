#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTime>

struct AnswerData
{
    size_t memorySize;
    int taskCount;
    int timeStart;
    int timeEnd;
    int memoryTask;
    AnswerData(size_t amemorySize = 0, int ataskCount = 0, int atimeStart = 0, int atimeEnd = 0)
    {
        memorySize = amemorySize;
        taskCount = ataskCount;
        timeStart = atimeStart;
        timeEnd = atimeEnd;
    }
};

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:

    AnswerData answerData;

    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_okPushButton_clicked();
    void on_closePushButton_clicked();

signals:
    void answerDataSend(AnswerData data);

private:
    Ui::SettingsDialog *ui;

};

#endif // SETTINGSDIALOG_H

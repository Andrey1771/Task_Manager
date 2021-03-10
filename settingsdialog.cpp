#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &SettingsDialog::on_closePushButton_clicked);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

///
/// \brief Берем данные, после нажатия на кнопку ok, после закрываем окно
///
void SettingsDialog::on_okPushButton_clicked()
{
    answerData.memorySize = static_cast<size_t>(ui->memorySpinBox->value());
    answerData.taskCount = ui->taskCountspinBox->value();
    answerData.timeStart = ui->timeStartSpinBox->value();
    answerData.timeEnd = ui->workTimeSpinBox->value();
    answerData.memoryTask = ui->memoryTaskSpinBox->value();

    emit(answerDataSend(answerData));
    close();
}

///
/// \brief закрываем окно после нажатия на кнопку cancel
///
void SettingsDialog::on_closePushButton_clicked()
{
    close();
}

#include "CommunicationWidget.h"
#include "ui_CommunicationWidget.h"

CommunicationWidget::CommunicationWidget(QString portName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommunicationWidget)
{
    ui->setupUi(this);

    this->setWindowTitle(portName);
}

CommunicationWidget::~CommunicationWidget()
{
    delete ui;
}

void CommunicationWidget::addChar(char character)
{
    if (ui->debugCheckbox->isChecked() || missionMode)
        ui->plainTextEdit->insertPlainText(QString(character));

    if (ui->autoScrollCheckbox->isChecked())
        ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->verticalScrollBar()->maximum());
}

void CommunicationWidget::addQString(QString text)
{
    if (ui->debugCheckbox->isChecked() || missionMode)
        ui->plainTextEdit->insertPlainText(text);

    if (ui->autoScrollCheckbox->isChecked())
        ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->verticalScrollBar()->maximum());
}

void CommunicationWidget::setTimerMain(int time)
{
    ui->timerMainLabel->setText(intToTime(time));
}

void CommunicationWidget::setTimerLap(int time)
{
    ui->timerLapLabel->setText(intToTime(time));
}

// Converts a number of milliseconds into a formatted time String
QString CommunicationWidget::intToTime(int time)
{
    QString output;
    output.append(QString::number(time / 60000));
    output.append(QString(":"));
    output.append(QString("%1").arg(time / 1000 % 60, 2, 10, QChar('0')));
    output.append(QString("."));
    output.append(QString::number(time % 1000));
    return output;
}

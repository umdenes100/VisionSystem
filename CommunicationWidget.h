#ifndef COMMUNICATIONWIDGET_H
#define COMMUNICATIONWIDGET_H

#include <QMainWindow>
#include <QScrollBar>

namespace Ui {
class CommunicationWidget;
}

class CommunicationWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit CommunicationWidget(QString portName, QWidget *parent = 0);
    ~CommunicationWidget();

    void addChar(char character);
    void addQString(QString text);
    void setTimerMain(int time);
    void setTimerLap(int time);

    bool missionMode = false;

private:
    Ui::CommunicationWidget *ui;

    QString intToTime(int time);
};

#endif // COMMUNICATIONWIDGET_H

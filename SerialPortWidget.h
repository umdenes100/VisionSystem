#ifndef SERIALPORTWIDGET_H
#define SERIALPORTWIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTime>
#include "CommunicationWidget.h"
#include "Marker.h"
#include "Arena.h"
#include "missions/Mission.h"

namespace Ui {
class SerialPortWidget;
}

enum TeamType{
    BLACK_BOX,
    CHEMICAL,
    DEBRIS,
    FIRE,
    WATER
};

class SerialPortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortWidget(QString portName, Arena& arena, QWidget *parent = 0);
    ~SerialPortWidget();

    QString getPortName();
    void sendMessage(QByteArray message);
    void sendMessage(QString message);
    void start();

signals:
    void markerRequested(QString, int);
    void siteRequested(QString, TeamType);

private slots:
    void readData();
    void on_portNameLabel_textEdited(const QString &arg1);
    void updateTime();

private:
    void command(QString commandString);

    Ui::SerialPortWidget *ui;

    bool commandMode;
    QString buffer;
    QString portName;

    TeamType mType;

    QSerialPort *serialPort;
    CommunicationWidget *communicationWidget;

    QTime *time;
    QTimer *timer;
    bool running;
    bool lapped;

    double tempNumber;
    QString tempBuffer;

    Mission *mission;
    Arena& mArena;
};

#endif /* SERIALPORTWIDGET_H */

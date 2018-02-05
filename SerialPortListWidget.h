#ifndef SERIALPORTLISTWIDGET_H
#define SERIALPORTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include "SerialPortWidget.h"
#include "Arena.h"


class SerialPortListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SerialPortListWidget(Arena& arena, QWidget *parent = 0);

private slots:
    void refreshPorts();

private:
    Arena& mArena;
    QMap<QString, SerialPortWidget *> serialPortWidgets;
    QVBoxLayout *mainLayout;
    QTimer *refreshPortsTimer;
    QWidget *spacer;
};

#endif /* SERIALPORTLISTWIDGET_H */

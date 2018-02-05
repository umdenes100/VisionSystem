#include "SerialPortListWidget.h"

#include <QSerialPortInfo>

SerialPortListWidget::SerialPortListWidget(Arena& arena, QWidget *parent) :
    QWidget(parent),
    mArena(arena)
{
    refreshPortsTimer = new QTimer(this);
    connect(refreshPortsTimer,SIGNAL(timeout()),this,SLOT(refreshPorts()));
    refreshPortsTimer->start(500); //Check twice a second.

    //Initialize the vertical layout.
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(mainLayout, Qt::AlignTop);
    spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}


void SerialPortListWidget::refreshPorts()
{
    // Get a list of available serial ports
    // A serial port is "available" if something is plugged into it and it is not
    // in use by another program
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    foreach (QSerialPortInfo info, availablePorts) {
        if (!serialPortWidgets.contains(info.portName())) {
            SerialPortWidget *widget = new SerialPortWidget(info.portName(), mArena, this);
            serialPortWidgets.insert(info.portName(), widget);
            mainLayout->addWidget(widget);
            widget->start();
        }
    }

    // If there are more widgets than ports, a port has become unavailable
    if (serialPortWidgets.size() > availablePorts.size()) {
        // Iterate through all widgets
        foreach (QString portName, serialPortWidgets.keys()) {
            // Check if the widget is in the list of available ports
            bool isListed = false;
            foreach (QSerialPortInfo info, availablePorts) {
                if (portName == info.portName())
                    isListed = true;
            }

            if (!isListed) {
                // The port is no longer available -- destroy the widget
                mainLayout->removeWidget(serialPortWidgets[portName]);
                delete serialPortWidgets[portName];
                serialPortWidgets.remove(portName);
            }
        }
    }

    mainLayout->removeWidget(spacer);
    mainLayout->addWidget(spacer);
}

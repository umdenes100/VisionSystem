#include "SerialPortWidget.h"
#include "ui_SerialPortWidget.h"
#include "missions/BlackBoxMission.h"
#include "missions/ChemicalMission.h"
#include "missions/DebrisMission.h"
#include "missions/FireMission.h"
#include "missions/WaterMission.h"

#include <QStringList>

SerialPortWidget::SerialPortWidget(QString portName, Arena &arena, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortWidget),
    mArena(arena)
{
    ui->setupUi(this);

    this->portName = portName;

    // Initialize the label
    ui->portNameLabel->setText(portName);

    // Initialize this widget's communication pane
    communicationWidget = new CommunicationWidget(portName, this);
    // When the communication button is pressed, open the pane
    connect(ui->communicationButton, SIGNAL(clicked()), communicationWidget, SLOT(show()));
    connect(ui->communicationButton, SIGNAL(clicked()), communicationWidget, SLOT(raise()));

    commandMode = false;
    running = false;
    lapped = false;
    time = new QTime();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(updateTime()));
    mType = BLACK_BOX;
}

SerialPortWidget::~SerialPortWidget()
{
    delete ui;
    serialPort->close();
    delete serialPort;
}

void SerialPortWidget::start()
{
    // Initialize the serial port
    serialPort = new QSerialPort(portName, this);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);

    // When there is data to process, fire the readData() method
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));

    while (!serialPort->isOpen())
        serialPort->open(QSerialPort::ReadWrite);
    // Open the serial port
    //if (serialPort->open(QSerialPort::ReadWrite))
        ui->communicationButton->setEnabled(true);
    // Required for APC operation
    serialPort->setRequestToSend(false);
    serialPort->clear();
}

void SerialPortWidget::readData()
{
    // Iterate through all characters delivered
    while (serialPort->bytesAvailable()) {
        // Read out data from serial port
        char requestChar;
        serialPort->getChar(&requestChar);

        if (requestChar == '#') {
            // # indicates a command
            // Switch to command mode and begin storing characters to buffer
            commandMode = true;
            buffer = QString("");
        } else {
            // If in command mode...
            if (commandMode) {
                if (requestChar == '*') {
                    // * indicates end of command
                    // Exit command mode and handle or delegate
                    commandMode = false;
                    communicationWidget->missionMode = true;
                    command(buffer);
                    communicationWidget->missionMode = false;
                } else
                    // Add character to end of command buffer
                    buffer.append(requestChar);
            } else {
                communicationWidget->addChar(requestChar);
            }
        }
    }
}

void SerialPortWidget::command(QString commandString)
{
    // If the command is all numbers, a marker was requested
    bool ok = true;
    int markerNumber = commandString.toInt(&ok);
    if (ok) {
        Marker marker(markerNumber);
        bool markerPresent = mArena.getPosition(markerNumber, marker);
        if(markerPresent){
            QString response = QString("") +
                    QString::number(marker.id) + QString(",") +
                    QString::number(marker.x) + QString(",") +
                    QString::number(marker.y) + QString(",") +
                    QString::number(marker.theta) + QString("\n");
            sendMessage(response);
        }
    } else {
        if (commandString.contains("start")) {
            time->start();
            running = true;
            communicationWidget->setTimerMain(0);
            communicationWidget->setTimerLap(0);
            timer->start(100);
            QStringList list = commandString.split(" ").mid(0, 2);
            QString teamName = commandString.section(' ', 2);
            QString teamString = list[1];
            ui->portNameLabel->setText(teamName);
            communicationWidget->setWindowTitle(teamName);
            mType = static_cast<TeamType>(teamString.toInt());
            if (mType == BLACK_BOX) {
                mission = new BlackBoxMission();
            } else if (mType == CHEMICAL) {
                mission = new ChemicalMission();
            } else if (mType == DEBRIS) {
                mission = new DebrisMission();
            } else if (mType == FIRE) {
                mission = new FireMission();
            } else if (mType == WATER) {
                mission = new WaterMission();
            }
            communicationWidget->addQString("\n*** MISSION MESSAGE ***\n");
            communicationWidget->addQString("Start of mission\n");
            communicationWidget->addQString(QString("**************************\n"));
        } else if (commandString.contains("base")) {
            QString param = commandString.split(" ")[1];
            QString result = mission->baseObjective(param);
            communicationWidget->addQString("\n*** MISSION MESSAGE ***\n");
            communicationWidget->addQString(result);
            communicationWidget->addQString(QString("**************************\n"));
        } else if (commandString.contains("bonus")) {
            QString param = commandString.split(" ")[1];
            QString result = mission->bonusObjective(param);
            communicationWidget->addQString("\n*** MISSION MESSAGE ***\n");
            communicationWidget->addQString(result);
            communicationWidget->addQString(QString("**************************\n"));
        } else if (commandString.contains("end")) {
            if (running) {
                communicationWidget->addQString("\n*** MISSION MESSAGE ***\n");
                communicationWidget->addQString("End of mission\n");
                communicationWidget->addQString(QString("**************************\n"));
                communicationWidget->setTimerMain(time->elapsed());
                running = false;
                lapped = false;
                timer->stop();
            }
        } else if (commandString.contains("destination")) {
            QString response = QString("");
            if (mType != BLACK_BOX) {
                Position destination = mArena.getTargetLocation();
                response += QString::number(destination.x) + QString(",");
                response += QString::number(destination.y) + QString("\n");
            } else {
                response += QString("0,0\n");
            }
            sendMessage(response);
        } else if (commandString.contains("navigated")) {
            if (mType == CHEMICAL && running && !lapped) {
                communicationWidget->setTimerLap(time->elapsed());
                lapped = true;
            }
            communicationWidget->addQString("\n*** MISSION MESSAGE ***\n");
            communicationWidget->addQString(QString("Team has reached destination"));
            communicationWidget->addQString(QString("\n**************************\n"));
        }
    }
}

void SerialPortWidget::sendMessage(QByteArray message)
{
    serialPort->write(message);
}

void SerialPortWidget::sendMessage(QString message)
{
    sendMessage(QByteArray().append(message));
}

void SerialPortWidget::on_portNameLabel_textEdited(const QString &arg1)
{
    communicationWidget->setWindowTitle(arg1);
}

void SerialPortWidget::updateTime()
{
    communicationWidget->setTimerMain(time->elapsed());
}

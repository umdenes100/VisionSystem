#-------------------------------------------------
#
# Project created by QtCreator 2017-01-04T14:25:51
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

TARGET = VisionSystem3
TEMPLATE = app


SOURCES += main.cpp\
        Arena.cpp\
        Camera.cpp\
        MainWindow.cpp\
	SerialPortWidget.cpp\
	SerialPortListWidget.cpp\
    CommunicationWidget.cpp\
    missions/BlackBoxMission.cpp\
    missions/ChemicalMission.cpp\
    missions/DebrisMission.cpp\
    missions/FireMission.cpp\
    missions/WaterMission.cpp

HEADERS  += Arena.h\
        Camera.h\
        MainWindow.h\
	SerialPortWidget.h\
	SerialPortListWidget.h\
	Marker.h\
        Position.h\
        Obstacle.h\
    CommunicationWidget.h\
    missions/Mission.h\
    missions/BlackBoxMission.h\
    missions/ChemicalMission.h\
    missions/DebrisMission.h\
    missions/FireMission.h\
    missions/WaterMission.h

FORMS    += MainWindow.ui \
    SerialPortWidget.ui \
    CommunicationWidget.ui

RESOURCES += images.qrc

unix|win32: LIBS += -L/usr/local/lib -laruco -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

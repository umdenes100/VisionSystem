#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "SerialPortListWidget.h"
#include "Arena.h"
#include "Camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onNewFrame(QImage image);
    void onApplySettingsClicked();
    void onRandomizeButtonClicked();
    void on_resetCamera_clicked();

private:
    Ui::MainWindow *ui;

    // Utility functions
    void fillDefaultSettings();

    // Objects
    SerialPortListWidget *splw;
    QImage qimage;
    QString checkboxText;

    Arena mArena;
    Camera mCamera;

    // Settings
    float arenaWidth;
    float arenaHeight;
};

#endif // MAINWINDOW_H

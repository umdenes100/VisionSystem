#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mArena(),
    mCamera(mArena)
{
    ui->setupUi(this);
    splw = new SerialPortListWidget(mArena, this);
    ui->communicationVBoxLayout->addWidget(splw);

    // Apply settings button
    fillDefaultSettings();
    connect(ui->applySettingsPushButton, SIGNAL(clicked()), SLOT(onApplySettingsClicked()));

    // Drawing options
    connect(ui->targetSiteCheckbox, SIGNAL(toggled(bool)), &mCamera, SLOT(onDrawDestinationChanged(bool)));
    connect(ui->obstaclesCheckbox, SIGNAL(toggled(bool)), &mCamera, SLOT(onDrawObstaclesChanged(bool)));
    connect(ui->customCheckbox, SIGNAL(toggled(bool)), &mCamera, SLOT(onDrawCustomChanged(bool)));
    connect(ui->customX, SIGNAL(valueChanged(double)), &mCamera, SLOT(onCustomXChanged(double)));
    connect(ui->customY, SIGNAL(valueChanged(double)), &mCamera, SLOT(onCustomYChanged(double)));
    mCamera.onDrawCustomChanged(ui->customCheckbox->isChecked());
    mCamera.onCustomXChanged(ui->customX->value());
    mCamera.onCustomYChanged(ui->customY->value());

    // Camera sliders
    connect(ui->cameraFocusSlider, SIGNAL(valueChanged(int)), &mCamera, SLOT(onFocusChanged(int)));
    connect(ui->cameraBrightnessSlider, SIGNAL(valueChanged(int)), &mCamera, SLOT(onBrightnessChanged(int)));
    connect(ui->cameraSharpnessSlider, SIGNAL(valueChanged(int)), &mCamera, SLOT(onSharpnessChanged(int)));

    connect(ui->applySettingsPushButton, SIGNAL(clicked()), SLOT(onApplySettingsClicked()));

    connect(&mCamera, SIGNAL(newFrame(QImage)), SLOT(onNewFrame(QImage)));
    connect(ui->randomStartButton, SIGNAL(clicked()), SLOT(onRandomizeButtonClicked()));

    mArena.randomize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewFrame(QImage image) {
    ui->imageLabel->setPixmap(
        QPixmap::fromImage(image.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio))
    );
}

void MainWindow::onApplySettingsClicked()
{
    // Camera device
    uint cameraDevice = ui->cameraDeviceSpinBox->value();

    // Camera resolution
    QStringList resString = ui->cameraResolutionComboBox->currentText().split("x",QString::SkipEmptyParts);
    QSize resolution = QSize(resString.at(0).toInt(),resString.at(1).toInt());

    // Frame rate
    uint frameRate = ui->frameRateLineEdit->text().toInt();

    // Marker size
    float markerSize = ui->markerSizeLineEdit->text().toFloat();

    mCamera.applySettings(cameraDevice, resolution, frameRate, markerSize);
    this->on_resetCamera_clicked();

    // Arena size
    float width = ui->arenaWidthLineEdit->text().toFloat();
    float height = ui->arenaHeightLineEdit->text().toFloat();

    mArena.setSize(width, height);
}

void MainWindow::onRandomizeButtonClicked() {
    mArena.randomize();
}

void MainWindow::fillDefaultSettings()
{
    ui->cameraDeviceSpinBox->setValue(0);
    ui->cameraResolutionComboBox->setCurrentText("1920x1080");
    ui->frameRateLineEdit->setText("25");
    ui->markerSizeLineEdit->setText("0.1");
    ui->arenaWidthLineEdit->setText("4.0");
    ui->arenaHeightLineEdit->setText("2.0");
    ui->cameraBrightnessSlider->setValue(50);
    ui->cameraSharpnessSlider->setValue(255);
    ui->cameraFocusSlider->setValue(0);

    onApplySettingsClicked();
}


void MainWindow::on_resetCamera_clicked()
{
   mCamera.resetCamera();
   if (mCamera.isBestekerCamera) {
       ui->cameraFocusSlider->setValue(0);
       ui->cameraBrightnessSlider->setValue(0);
       ui->cameraSharpnessSlider->setValue(255);
   } else {
       ui->cameraFocusSlider->setValue(128);
       ui->cameraBrightnessSlider->setValue(128);
       ui->cameraSharpnessSlider->setValue(128);
   }
}

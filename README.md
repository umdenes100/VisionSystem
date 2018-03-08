# VisionSystem

Vision System is a computer-vision-based marker tracker for use in the University of Maryland, College Park's ENES100 course.

## Installation

Vision System is a Qt-based application which relies on OpenCV and the ArUco library for use. For a new installation, being by installing OpenCV.

1. Download the source of the [latest version of OpenCV](https://opencv.org/releases.html)
2. Unpack the archive
3. Open a terminal and change the working directory to the unpacked folder

```
mkdir build
cd build
cmake ..
sudo make install
```

While OpenCV is installing, you may begin installing Qt.

1. Download the [latest version of Qt](https://www.qt.io/download). Enterprise, Open Source, and Community editions are all acceptable for Vision System.
2. Run the downloaded installer (you may need to add execution privileges to the file).
3. Follow the prompts to install Qt. Make sure to include Qt Creator and at least one version of Qt.

Once OpenCV has finished installing (it is okay for Qt to still be installing), install ArUco.

1. Download the source of the [latest version of ArUco](https://sourceforge.net/projects/aruco/files/)
2. Unpack the archive
3. Open a terminal and change the working directory to the unpacked folder

```
mkdir build
cd build
cmake ..
sudo make install
```

For Vision System to work properly, Video4Linux2 (v4l2) must be installed. As of Antergos 18.3, v4l2 is included as part of the OS image. On Ubuntu or other versions of linux, v4l2 can be installed from the package manager.

To be able to communicate with the rovers, Vision System must have access to the serial ports of the computer. Add whichever user you are using to run Vision System to the OS's group for serial port access. If you don't know which group this is, plug in one APC220 and run

```
ls -l /dev/ttyUSB0
```

In the sample output

```
crw-rw----  1 root dialout   20,   0 Mar  1 12:00 /dev/ttyUSB0
```

the group is `dialout`.

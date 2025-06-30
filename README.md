# Qt Face Detection Camera App

A simple cross-platform Qt5 application that uses OpenCV to display live webcam video with face detection and lets you save snapshots with a shortcut key.

---

## Features

- Live camera preview with face detection (using Haar cascades)
- Draw rectangles and labels on detected faces
- Save captured images to `~/Pictures` by pressing **Space**
- Confirmation message box after saving image
- Cross-platform: tested on Linux (Ubuntu, Arch Linux)

---

## Requirements

- Qt 5 (Core, Widgets)
- OpenCV 4
- C++11 compatible compiler

---

## Installing Dependencies

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential qt5-qmake qtbase5-dev libopencv-dev libopencv-imgproc-dev libopencv-objdetect-dev
```

- `qt5-qmake` and `qtbase5-dev` for Qt development
- `libopencv-dev` and related packages for OpenCV core + image processing + face detection

---

### Arch Linux

```bash
sudo pacman -Syu
sudo pacman -S qt5-base opencv
```

---

## Build Instructions

1. Place `frontalface.xml` (Haar cascade file) in the executable directory or provide a correct path.

2. Prepare your `.pro` file:

```pro
QT += core gui widgets
CONFIG += c++11

SOURCES += main.cpp

INCLUDEPATH += /usr/include/opencv4
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_videoio
```

3. Build steps:

```bash
qmake
make
```

4. Run:

```bash
./cameraapp
```

---

## Usage

- The app will open your default webcam.
- Faces will be detected and highlighted with rectangles and labels.
- Press **Space** to save the current frame to your `~/Pictures` folder.
- After saving, a message box will confirm the filename.

---

## Notes

- Ensure your webcam is accessible and not used by other applications.
- The `frontalface.xml` cascade file is required. You can find it under OpenCV's data directory, e.g., `/usr/share/opencv4/haarcascades/frontalface_default.xml` or download from the OpenCV GitHub repo.
- Modify the path in your code accordingly.

---

## License

MIT License

---

## Contact

Created by nimacpp


# Qt Camera App

A simple cross-platform Qt5 app to capture webcam images.

## Features

- Live camera preview
- Capture photo to `~/Pictures`
- Keyboard shortcuts:
  - Space → Capture image
  - Ctrl+S → Capture image
- Native system theme (GNOME, KDE, Windows)

## Requirements

- Qt 5 (with Multimedia module)

## Build

```bash
qmake
make
./cameraapp

QT += core gui widgets multimedia
CONFIG += c++11

SOURCES += main.cpp

INCLUDEPATH += /usr/include/opencv4
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui \
        -lopencv_objdetect -lopencv_videoio -lopencv_imgcodecs

#-------------------------------------------------
#
# Project created by QtCreator 2013-01-30T12:22:25
#
#-------------------------------------------------

QT       += core gui

TARGET = untitled55
TEMPLATE = app


SOURCES += main.cpp \
    bgdetector.cpp \
    markerfinder.cpp \
    physicalexercisedetector.cpp \
    VideoSource/webcamemul.cpp \
    VideoSource/webcam.cpp \
    VideoSource/iwebcam.cpp

HEADERS  += \
    bgdetector.h \
    markerfinder.h \
    physicalexercisedetector.h \
    VideoSource/webcamemul.h \
    VideoSource/webcam.h \
    VideoSource/iwebcam.h

FORMS    +=
INCLUDEPATH += C:/OpenCV/mingw/install/include
LIBS += C:/OpenCV/mingw/install/lib/*.a






















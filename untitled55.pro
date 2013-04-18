#-------------------------------------------------
#
# Project created by QtCreator 2013-01-30T12:22:25
#
#-------------------------------------------------

QT       += core gui

TARGET = untitled55
TEMPLATE = app


SOURCES += main.cpp \
    physicalexercisedetector.cpp \
    VideoSource/webcamemul.cpp \
    VideoSource/webcam.cpp \
    VideoSource/iwebcam.cpp \
    BackgroundSubtraction/bgteacher.cpp \
    BackgroundSubtraction/bgdetector.cpp \
    MarkerFinder/markerfinder.cpp \
    MarkerFinder/colorsstorage.cpp

HEADERS  += \
    physicalexercisedetector.h \
    VideoSource/webcamemul.h \
    VideoSource/webcam.h \
    VideoSource/iwebcam.h \
    BackgroundSubtraction/bgteacher.h \
    BackgroundSubtraction/bgdetector.h \
    MarkerFinder/markerfinder.h \
    MarkerFinder/colorsstorage.h

FORMS    +=
INCLUDEPATH += C:/OpenCV/mingw/install/include
LIBS += C:/OpenCV/mingw/install/lib/*.a































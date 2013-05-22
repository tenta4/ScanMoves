#-------------------------------------------------
#
# Project created by QtCreator 2013-01-30T12:22:25
#
#-------------------------------------------------

QT       += core gui

TARGET = untitled55
TEMPLATE = app


SOURCES +=  \
    main.cpp \
    \
    gamemodule.cpp \
    \
    VideoSource/webcamemul.cpp \
    VideoSource/webcam.cpp \
    VideoSource/iwebcam.cpp \
    RecognitionBase/physicalexercisedetector.cpp \
    RecognitionBase/BackgroundSubtraction/bgteacher.cpp \
    RecognitionBase/BackgroundSubtraction/bgdetector.cpp \
    RecognitionBase/MarkerFinder/markerfinder.cpp \
    RecognitionBase/MarkerFinder/colorsstorage.cpp \
    RecognitionBase/MarkerFinder/marker.cpp \
    RecognitionBase/MarkersStorage/markerpolarcs.cpp \
    RecognitionBase/MarkersStorage/markersstorage.cpp


HEADERS  += \
    gamemodule.h \
    \
    VideoSource/webcamemul.h \
    VideoSource/webcam.h \
    VideoSource/iwebcam.h \
    \
    RecognitionBase/physicalexercisedetector.h \
    RecognitionBase/BackgroundSubtraction/bgteacher.h \
    RecognitionBase/BackgroundSubtraction/bgdetector.h \
    RecognitionBase/MarkerFinder/markerfinder.h \
    RecognitionBase/MarkerFinder/colorsstorage.h \
    RecognitionBase/MarkerFinder/marker.h \
    RecognitionBase/MarkersStorage/markerpolarcs.h \
    RecognitionBase/MarkersStorage/markersstorage.h

FORMS    +=
INCLUDEPATH += C:/OpenCV/mingw/install/include
LIBS += C:/OpenCV/mingw/install/lib/*.a











































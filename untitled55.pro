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
    RecognitionBase/marker.cpp \
    RecognitionBase/BackgroundSubtraction/bgteacher.cpp \
    RecognitionBase/BackgroundSubtraction/bgdetector.cpp \
    RecognitionBase/MarkerFinder/markerfinder.cpp \
    RecognitionBase/MarkerFinder/colorsstorage.cpp \
    RecognitionBase/MarkersStorage/markersstorage.cpp \
    movecreator.cpp \
    RecognitionBase/markersdrawing.cpp \
    RecognitionBase/markersio.cpp


HEADERS  += \
    gamemodule.h \
    \
    VideoSource/webcamemul.h \
    VideoSource/webcam.h \
    VideoSource/iwebcam.h \
    \
    RecognitionBase/physicalexercisedetector.h \
    RecognitionBase/marker.h \
    RecognitionBase/BackgroundSubtraction/bgteacher.h \
    RecognitionBase/BackgroundSubtraction/bgdetector.h \
    RecognitionBase/MarkerFinder/markerfinder.h \
    RecognitionBase/MarkerFinder/colorsstorage.h \
    RecognitionBase/MarkersStorage/markersstorage.h \
    movecreator.h \
    RecognitionBase/markersdrawing.h \
    RecognitionBase/markersio.h

FORMS    +=
INCLUDEPATH += C:/OpenCV/mingw/install/include
LIBS += C:/OpenCV/mingw/install/lib/*.a



















































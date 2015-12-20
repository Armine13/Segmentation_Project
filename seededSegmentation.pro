#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T19:14:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = seededSegmentation
TEMPLATE = app

SOURCES += main.cpp\
    GUI/mainwindow.cpp \
    GUI/markerbutton.cpp \
    GUI/scribblearea.cpp \
    GUI/segmentationmarkerwidget.cpp \
    GUI/tab.cpp \
    segmentation/segmentation.cpp

HEADERS  += GUI/mainwindow.h \
    GUI/markerbutton.h \
    GUI/scribblearea.h \
    GUI/segmentationmarkerwidget.h \
    GUI/tab.h \
    segmentation/segmentation.h

FORMS    += GUI/mainwindow.ui \
    GUI/tab.ui

RESOURCES += \
    GUI/tangomfk.qrc

#Linux
#CONFIG += link_pkgconfig
#PKGCONFIG += opencv #eigen3

INCLUDEPATH += C:\opencv-mingw\eigen-eigen-c58038c56923
#INCLUDEPATH += /home/armine/eigen-eigen-b30b87236a1b
#INCLUDEPATH += /home/masters/eigen-eigen-b30b87236a1b


#Windows
INCLUDEPATH += C:\opencv-mingw\eigen-eigen-c58038c56923

INCLUDEPATH += C:\opencv-mingw\install\include
LIBS += -L"C:/opencv-mingw/install/x64/mingw/bin"
LIBS += -lopencv_core2410 -lopencv_highgui2410 -lopencv_imgproc2410


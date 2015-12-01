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

CONFIG += link_pkgconfig
PKGCONFIG += opencv eigen3

#INCLUDEPATH += /home/armine/eigen-eigen-b30b87236a1b
#INCLUDEPATH += /home/masters/eigen-eigen-b30b87236a1b

#INCLUDEPATH += /usr/local/include/opencv2
#INCLUDEPATH += /usr/local/include/opencv
#INCLUDEPATH +=/usr/local/include/opencv2/core
#INCLUDEPATH +=/usr/local/include/opencv2/imgproc
#INCLUDEPATH +=/usr/local/include/opencv2/ml
#INCLUDEPATH +=/usr/local/include/opencv2/highgui
#LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui


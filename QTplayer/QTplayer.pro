#-------------------------------------------------
#
# Project created by QtCreator 2018-07-21T15:46:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTplayer
TEMPLATE = app

QT += multimedia
QT += multimediawidgets
QT += network

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    qtplayer.qrc

DISTFILES += \
    image/openfile.png

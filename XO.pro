#-------------------------------------------------
#
# Project created by QtCreator 2014-06-10T13:57:17
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XO
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    xml.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    xml.h \
    game.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc


#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T22:30:01
#
#-------------------------------------------------

QT       += core gui
QT +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    bathcar.cpp \
    client.cpp \
    fix.cpp \
    insurance.cpp \
    usermanagement.cpp \
    newfixinfo.cpp \
    connect.cpp \
    newbathcar.cpp \
    newinsuranceoraccident.cpp \
    newclient.cpp \
    logindialog.cpp \
    concerning.cpp

HEADERS  += mainwindow.h \
    bathcar.h \
    client.h \
    fix.h \
    insurance.h \
    usermanagement.h \
    newfixinfo.h \
    connect.h \
    newbathcar.h \
    newinsuranceoraccident.h \
    newclient.h \
    logindialog.h \
    concerning.h
RESOURCES += \
    image.qrc
FORMS += \
    logindialog.ui

RC_ICONS = CarManage.ico

#-------------------------------------------------
#
# Project created by QtCreator 2018-07-23T13:37:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Car
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    send_client.cpp \
    mainwindow.cpp \
    send_controller.cpp \
    send_filedialog.cpp \
    send_list_item.cpp \
    send_socket.cpp

HEADERS += \
    send_client.h \
    mainwindow.h \
    send_controller.h \
    send_filedialog.h \
    send_list_item.h \
    send_socket.h

FORMS += \
    send_client.ui \
    mainwindow.ui
QT +=network

#INCLUDEPATH += F:\msvc_build\opencv\build\include

#LIBS += F:\msvc_build\opencv\build\x64\vc15\lib\*.lib

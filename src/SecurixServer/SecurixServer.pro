QT += core gui network
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SecurixServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        sslserver.cpp \
        backend.cpp

HEADERS += \
        mainwindow.h \
        sslserver.h \
        backend.h

FORMS += \
        mainwindow.ui

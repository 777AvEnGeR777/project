#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T12:59:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPPProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authwindow.cpp \
    Account.cpp \
    Card.cpp \
    Data.cpp \
    Encryptor.cpp \
    Parser.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    Account.h \
    Card.h \
    Data.h \
    Encryptor.h \
    IWrappable.h \
    Parser.h

FORMS    += mainwindow.ui \
    authwindow.ui

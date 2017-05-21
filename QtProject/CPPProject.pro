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
    Parser.cpp \
    passwordstrengthchecker.cpp \
    passwordgenerator.cpp \
    accountform.cpp \
    cardform.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    Account.h \
    Card.h \
    Data.h \
    Encryptor.h \
    IWrappable.h \
    Parser.h \
    passwordstrengthchecker.h \
    enums.h \
    passwordgenerator.h \
    accountform.h \
    cardform.h

FORMS    += mainwindow.ui \
    authwindow.ui \
    accountform.ui \
    cardform.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lcryptlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lcryptlib
else:unix: LIBS += -L$$PWD/libs/ -lcryptlib

INCLUDEPATH += $$PWD/libs/Debug
DEPENDPATH += $$PWD/libs/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libcryptlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libcryptlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/cryptlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/cryptlib.lib
else:unix: PRE_TARGETDEPS += $$PWD/libs/libcryptlib.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -ltinyxml2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -ltinyxml2
else:unix: LIBS += -L$$PWD/libs/ -ltinyxml2

INCLUDEPATH += $$PWD/libs/Debug
DEPENDPATH += $$PWD/libs/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libtinyxml2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libtinyxml2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/tinyxml2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/tinyxml2.lib
else:unix: PRE_TARGETDEPS += $$PWD/libs/libtinyxml2.a

RESOURCES +=

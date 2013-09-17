#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T16:42:53
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = mixpanel-qt
TEMPLATE = lib

DESTDIR = $$PWD/../../lib/release
debug: {
     DESTDIR = $$PWD/../../lib/debug
}

DEFINES += MIXPANELQT_LIBRARY

SOURCES += mixpanel.cpp

HEADERS += mixpanel.h\
        mixpanel-qt_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5
    INCLUDEPATH += /opt/local/include/
}

unix|win32: LIBS += -lqjson

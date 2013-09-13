#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T16:42:53
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = mixpanel-qt
TEMPLATE = lib
DESTDIR = ../lib


DEFINES += MIXPANELQT_LIBRARY

SOURCES += src/mixpanel.cpp

HEADERS += src/mixpanel.h\
        src/mixpanel-qt_global.h

debug: {
     unix: TARGET = $$join(TARGET,,,_debug)
     else: TARGET = $$join(TARGET,,,d)
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}


unix|win32: LIBS += -lqjson

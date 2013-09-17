#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T16:42:53
#
#-------------------------------------------------

release: {
DEFAULT_SUBDIR = release
}
else: debug: {
     DEFAULT_SUBDIR = debug
}

QT       += network

QT       -= gui

TARGET = mixpanel-qt
TEMPLATE = lib

DESTDIR = $$PWD/../../lib/$$DEFAULT_SUBDIR

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
    LIBS += -L/opt/local/lib/
}

unix|win32: LIBS += -lqjson

#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T16:44:34
#
#-------------------------------------------------

CONFIG(debug, debug|release) {
     DEFAULT_SUBDIR = debug
}
else: {
     DEFAULT_SUBDIR = release
}
QT       += testlib network

QT       -= gui

TARGET = tst_mixpaneltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_mixpaneltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/debug/release/ -lmixpanel-qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/debug/debug/ -lmixpanel-qt
else:unix: LIBS += -L$$PWD/../../lib/debug/ -lmixpanel-qt

macx {
    QMAKE_POST_LINK += cp $$PWD/../../lib/$${DEFAULT_SUBDIR}/*.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/
}

INCLUDEPATH += $$PWD/../../lib $$PWD/../src
DEPENDPATH += $$PWD/../../lib

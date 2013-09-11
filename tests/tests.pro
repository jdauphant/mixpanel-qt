#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T16:44:34
#
#-------------------------------------------------

QT       += testlib network

QT       -= gui

TARGET = tst_mixpaneltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_mixpaneltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-mixpanel-qt-Desktop-Release/release/ -lmixpanel-qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-mixpanel-qt-Desktop-Release/debug/ -lmixpanel-qt
else:unix: LIBS += -L$$PWD/../../build-mixpanel-qt-Desktop-Release/ -lmixpanel-qt

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

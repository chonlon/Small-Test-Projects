#-------------------------------------------------
#
# Project created by QtCreator 2018-02-13T21:07:40
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = TopWindow
TEMPLATE = app

CONFIG  -= app_bundle
DEFINES += QT_MESSAGELOGCONTEXT
DEFINES += QT_DEPRECATED_WARNINGS

# Output directory
CONFIG(debug, debug|release) {
    output = debug
}
CONFIG(release, debug|release) {
    output = release
}

DESTDIR     = bin
OBJECTS_DIR = $$output
MOC_DIR     = $$output
RCC_DIR     = $$output
UI_DIR      = $$output

include(gui/gui.pri)
include(util/util.pri)

SOURCES += \
        main.cpp

RESOURCES += \
    top-window-resources.qrc

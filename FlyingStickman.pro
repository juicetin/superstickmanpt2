#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T10:21:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlyingStickman
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    fileio.cpp \
    gameengine.cpp \
    player.cpp \
    background.cpp \
    concretebuilder.cpp \
    game.cpp \
    movingplayer.cpp \
    obstaclefactory.cpp \
    obstacle.cpp

HEADERS  += dialog.h \
    fileio.h \
    background.h \
    gameengine.h \
    gamebuilder.h \
    player.h \
    concretebuilder.h \
    game.h \
    movingplayer.h \
    fileioadapter.h \
    obstaclefactory.h \
    obstacle.h

FORMS    += dialog.ui

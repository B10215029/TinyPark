#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T09:41:15
#                                     by b10215029
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyPark
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    transform.cpp \
    gameobject.cpp \
    camera.cpp \
    light.cpp \
    shaderprogram.cpp \
    vec.cpp \
    mat.cpp \
    displaywidget.cpp \
    mesh.cpp \
    texture.cpp \
    particle.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    transform.h \
    gameobject.h \
    camera.h \
    light.h \
    shaderprogram.h \
    vec.h \
    mat.h \
    displaywidget.h \
    mesh.h \
    texture.h \
    particle.h \
    scene.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

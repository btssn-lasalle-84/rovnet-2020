#-------------------------------------------------
#
# Project created by QtCreator 2020-02-12T14:03:40
#
#-------------------------------------------------

QT       += core gui serialport gamepad multimedia sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_Rovnet
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv /usr/include/opencv2

INCLUDEPATH += . /usr/include/qwt/

LIBS += -lqwt-qt5

OPENCV_LIBS = $$system(pkg-config --libs-only-l opencv)
LIBS += $$OPENCV_LIBS

message($$INCLUDEPATH)
message($$LIBS)

#DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    ihmconfiguration.cpp \
    ihmgraphiques.cpp \
        main.cpp \
        ihmrov.cpp \
        rov.cpp \
        camera.cpp \
        communicationrov.cpp \
        manette.cpp \
        capteurs.cpp \
    ihmaccueil.cpp \
    ihmcreationcampagne.cpp \
    campagne.cpp \
    ihmalbumphoto.cpp \
    ihmreglagevideo.cpp \
    basededonnees.cpp

HEADERS += \
    ihmconfiguration.h \
    ihmgraphiques.h \
        ihmrov.h \
        rov.h \
        camera.h \
        communicationrov.h \
        manette.h \
        capteurs.h \
    ihmaccueil.h \
    ihmcreationcampagne.h \
    campagne.h \
    ihmalbumphoto.h \
    ihmreglagevideo.h \
    basededonnees.h

COPIES += images bd design
images.files = images
images.path = $$OUT_PWD/
images.base = $$PWD/
bd.files = campagnes.sqlite
bd.path = $$OUT_PWD/
bd.base = $$PWD/
design.files = design
design.path = $$OUT_PWD/
design.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT

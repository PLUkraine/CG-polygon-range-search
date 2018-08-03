#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T13:33:46
#
#-------------------------------------------------

QT       += opengl

TARGET = WidgetLibrary
TEMPLATE = lib

DEFINES += WIDGETLIBRARY_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Models/graphicalmodel.cpp \
    Models/pointbasedmodel.cpp \
    Models/pointsmodel.cpp \
    Models/polygonmodel.cpp \
    canvas.cpp \
    datarenderer.cpp

HEADERS +=\
        widgetlibrary_global.h \
    Models/graphicalmodel.h \
    Models/pointbasedmodel.h \
    Models/pointsmodel.h \
    Models/polygonmodel.h \
    canvas.h \
    datarenderer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../GeometrySearchLibrary
DEPENDPATH += $$PWD/../GeometrySearchLibrary

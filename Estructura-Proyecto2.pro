#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T11:45:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Estructura-Proyecto2
TEMPLATE = app


SOURCES += main.cpp\
        Menu.cpp \
    GrafoForm.cpp \
    OrdenamientoForm.cpp

HEADERS  += Menu.h \
    GrafoForm.h \
    OrdenamientoForm.h \
    Nodo.h \
    Grafo.h \
    Cola.h \
    Arista.h \
    AristaDoble.h \
    ColaDoble.h

FORMS    += Menu.ui \
    GrafoForm.ui \
    OrdenamientoForm.ui

#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T09:34:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Chart-Drawer
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           lib/qcustomplot.cpp \
           model/harmonic.cpp \
           dialog/insertharmonicdialog.cpp \
           model/harmoniccollection.cpp \
           model/harmonicfactory.cpp \
           model/anglefunction.cpp \
    utils/math.cpp \
    utils/range.cpp \
    model/harmonicplotitemsprovider.cpp

HEADERS  += mainwindow.h \
            stdafx.h \
            lib/qcustomplot.h \
            model/harmonic.h \
            model/anglefunction.h \
            dialog/insertharmonicdialog.h \
            model/harmoniccollection.h \
            model/harmonicfactory.h \
            model/iharmonicfactory.h \
            model/iharmonic.h \
    utils/math.h \
    utils/range.h \
    model/harmonicplotitemsprovider.h

FORMS    += mainwindow.ui \
            dialog/insertharmonicdialog.ui

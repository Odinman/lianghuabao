#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T12:46:33
#
#-------------------------------------------------

QT       += core gui widgets
# QT += core_private

TEMPLATE = app

include(../bftrader.pri)

SOURCES += main.cpp\
    ui/mainwindow.cpp \
    profile.cpp \
    servicemgr.cpp \
    pushservice.cpp \
    rpcservice.cpp \
    dbservice.cpp \
    gatewaymgr.cpp \
    ui/tablewidget_helper.cpp \
    ui/debugform.cpp \
    ui/workingorderform.cpp \
    ui/tradeform.cpp \
    protoutils.cpp \
    ui/finishedorderform.cpp \
    ctamgr.cpp

HEADERS  += ui/mainwindow.h \
    profile.h \
    servicemgr.h \
    pushservice.h \
    rpcservice.h \
    dbservice.h \
    gatewaymgr.h \
    ui/tablewidget_helper.h \
    ui/debugform.h \
    ui/workingorderform.h \ 
    ui/tradeform.h \
    protoutils.h \
    ui/finishedorderform.h \
    ctamgr.h

FORMS    += ui/mainwindow.ui \
    ui/debugform.ui \
    ui/workingorderform.ui \ 
    ui/tradeform.ui \
    ui/finishedorderform.ui

include(../base/base.pri)
include(../sdk/sdk.pri)
include(../third_party/breakpad.pri)
include(../third_party/mhook.pri)
include(../third_party/leveldb.pri)
include(../third_party/grpc.pri)

RESOURCES += \
    systray.qrc


QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DeviceController.cpp \
    Message.cpp \
    c_window.cpp \
    celmodel.cpp \
    dftplotter.cpp \
    dsp.cpp \
    main.cpp \
    mainwindow.cpp \
    messagehandler.cpp \
    messageprocessor.cpp \
    minfft.c \
    packet.cpp \
    qcustomplot.cpp \
    simpletabledata.cpp \
    timeplotter.cpp

HEADERS += \
    DeviceController.h \
    Message.h \
    c_window.h \
    celmodel.h \
    dftplotter.h \
    dsp.h \
    mainwindow.h \
    messagehandler.h \
    messageprocessor.h \
    minfft.h \
    packet.h \
    qcustomplot.h \
    simpletabledata.h \
    timeplotter.h

FORMS += \
    c_window.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

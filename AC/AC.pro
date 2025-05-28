QT += core network gui testlib

CONFIG += c++17 cmdline
CONFIG += -qreal float

QT += widgets
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Message.cpp \
        TcpServer.cpp \
        ac.cpp \
        acstatehandler.cpp \
        celhandler.cpp \
        cellstorage.cpp \
        datachanel.cpp \
        dataserver.cpp \
        logger.cpp \
        logmessage.cpp \
        main.cpp \
        messagehandler.cpp \
        messageprocessor.cpp \
        p2sockethandler.cpp \
        packet.cpp \
        planfactory.cpp \
        planstorage.cpp \
        reportstatechecker.cpp \
        sector.cpp \
        sectorplan.cpp \
        segmentplan.cpp \
        sequentialidprovider.cpp \
        sessionrequesthandler.cpp \
        stophandler.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Message.h \
    TcpServer.h \
    ac.h \
    acstatehandler.h \
    celhandler.h \
    cellstorage.h \
    datachanel.h \
    dataserver.h \
    logger.h \
    logmessage.h \
    messagebroker.h \
    messagehandler.h \
    messageprocessor.h \
    p2sockethandler.h \
    packet.h \
    planfactory.h \
    planstorage.h \
    reportstatechecker.h \
    sector.h \
    sectorplan.h \
    segmentplan.h \
    sequentialidprovider.h \
    sessionrequesthandler.h \
    stophandler.h

DISTFILES += \
    Signal.txt

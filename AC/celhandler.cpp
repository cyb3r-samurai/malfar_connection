#include "celhandler.h"

CelHandler::CelHandler(QObject *parent)
    : MessageHandler{parent}
{}

bool CelHandler::handleMessage(Packet &packet)
{
    if (packet.header.msg_type == 0x01) {
        QDataStream stream(&packet.data, QIODevice::ReadOnly);
        stream.setByteOrder(QDataStream::LittleEndian);
        Cel cel;
        stream >> cel;
        qDebug() << "Cel recieved";
        qDebug() << cel.chanel_number;
        emit celCreated(std::make_shared<Cel>(std::move(cel)), packet.id);
        return true;
    }
    else {
        return false;
    }
}

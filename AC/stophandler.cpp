#include "stophandler.h"

StopHandler::StopHandler(QObject *parent)
    : MessageHandler{parent}
{}

bool StopHandler::handleMessage(Packet &packet)
{
    if(packet.header.msg_type == 0x02) {
        emit stopRecieve(packet.id);
        return true;
    }
    else {
        return false;
    }
}

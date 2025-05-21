#include "acstatehandler.h"

AcStateHandler::AcStateHandler(QObject *parent)
    : MessageHandler{parent}
{}

bool AcStateHandler::handleMessage(const Packet &packet)
{
    if (packet.header.msg_type == 0x03) {
        emit requestCreated(packet.id);
        return true;
    }
    else {
        return false;
    }
}

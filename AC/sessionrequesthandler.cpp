#include "sessionrequesthandler.h"

SessionRequestHandler::SessionRequestHandler(QObject *parent)
    : MessageHandler{parent}
{}

bool SessionRequestHandler::handleMessage(const Packet & packet)
{
    if (packet.header.msg_type == 0x04) {
        emit requestRecieved(packet.id);
        return true;
    }
    return false;
}

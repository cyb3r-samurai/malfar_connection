#include "sessionrequesthandler.h"

SessionRequestHandler::SessionRequestHandler(QObject *parent)
    : MessageHandler{parent}
{}

bool SessionRequestHandler::handleMessage(Packet & packet)
{
    if (packet.header.msg_type == 0x03) {
        emit requestRecieved(packet.id);
        return true;
    }
    return false;
}

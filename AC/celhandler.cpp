#include "celhandler.h"

CelHandler::CelHandler(QObject *parent)
    : MessageHandler{parent}
{}

bool CelHandler::handleMessage(const Packet &packet)
{
    if (packet.header.msg_type == 0x01) {
        QDataStream stream(packet.data);
        stream.setByteOrder(QDataStream::LittleEndian);
        auto ptr1 = std::make_shared<Cel>();
        stream >> *(ptr1.get());
        auto &seq_provider = SequentialIdProvider::get();
        ptr1->id = seq_provider.next_cel();
        qInfo() << "Получено целеуказание";
        emit celCreated(ptr1, packet.id);
        return true;
    }
    else {
        return false;
    }
}

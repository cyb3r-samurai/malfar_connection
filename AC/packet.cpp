#include "packet.h"

Packet::Packet(Header header_, QByteArray data_) : header(header_), data(data_)
{

}

QByteArray Header::serializeStruct()
{
    QByteArray data;
    QDataStream stream(&data, QDataStream::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << version << msg_type << zero << time << n;

    return data;
}

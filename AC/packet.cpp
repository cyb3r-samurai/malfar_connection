#include "packet.h"

Packet::Packet()
{

}

Packet::Packet(Header header_, QByteArray data_, long long id_) :
    header{header_}, data{data_}, id{id_}
{

}

QByteArray Header::serializeStruct()
{
    QByteArray data;
    QDataStream stream(&data, QDataStream::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream << version << msg_type << zero << time << n;

    return data;
}

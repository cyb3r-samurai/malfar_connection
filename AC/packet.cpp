#include "packet.h"

Packet::Packet()
{

}

Packet::Packet(const Header& header_,  const QByteArray& data_, long long id_) :
    header{header_}, data{data_}, id{id_}
{

}

QByteArray Header::serializeStruct() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << version << msg_type << zero << time << n;

    return data;
}

#ifndef PACKET_H
#define PACKET_H

#include <QDataStream>
#include <QByteArray>

class Header {
public:
    uint16_t version = 0xAC01;
    uint8_t msg_type;
    uint8_t zero = 0x00;
    double time;
    uint32_t n;

    QByteArray serializeStruct();
};

class Packet {
public:
    Packet();
    Packet(Header header_, QByteArray data_, long long id_);

    Header header;
    QByteArray data;
    long long id;
};

#endif // PACKET_H

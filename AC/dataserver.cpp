#include "dataserver.h"

DataServer::DataServer(QObject *parent)
    : QObject{parent}
{
    reset_flag = false;

    tcp_socket = new QTcpSocket(this);
    tcp_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(tcp_socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError)
#else
    connect(tcp_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [this](QAbstractSocket::SocketError)
#endif
            {
                qDebug() <<  "TCP"  << QString(tcp_socket->errorString());
            });

    connect(tcp_socket, &QTcpSocket::stateChanged, this, [](int state)
            {
                if (state == QAbstractSocket::UnconnectedState)
                {
                    qDebug() << "TcpSocket disconected";
                }
                else if (state == QAbstractSocket::ConnectedState)
                {
                    qDebug() << "UdpSocket disconected";
                }
            });

    connect(tcp_socket, &QTcpSocket::readyRead, this, &DataServer::readyReadTcp);

    udp_socket = new QUdpSocket(this);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(udp_socket, &QUdpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError)
#else
    connect(udp_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [this](QAbstractSocket::SocketError)
#endif
            {
                qDebug() << "UDP" << udp_socket->errorString();
            });
    connect(udp_socket, &QUdpSocket::stateChanged, this, [this](int state)
            {
                if (state == QAbstractSocket::UnconnectedState)
                {
                    qDebug() << "Udp Socket unconnected";
                    //recieve_timer->stop();                                  // Stop polling
                }
                else if (state == QAbstractSocket::ConnectedState)
                {
                    qDebug() << "TCP Connection established";                    // Start polling
                }
            });
    connect(udp_socket, &QUdpSocket::readyRead, this, &DataServer::readyReadUdp);

}

void DataServer::readyReadTcp()
{
    struct packet_header packet_header;
    tcp_socket->read((char *)&packet_header, sizeof(packet_header));

    if (checkHeader(&packet_header) != true)
    {
        tcp_socket->readAll(); // clear buffer
        return;
    }

    // приём данных пакета

    qint64 data_size = packet_header.data_size;
    while (data_size)
    {
        QByteArray data = tcp_socket->read(data_size);
        data_size -= data.size();

        if (data_size)
        {
            if (tcp_socket->waitForReadyRead(100) == false)
            {
                qDebug() << "missing data";
                return;
            }
        }
    }
}


void DataServer::readyReadUdp()
{

}

bool DataServer::checkHeader(packet_header *packet_header)
{
    if (packet_header->protocol_version != protocol_version)
    {
        qDebug() << "version";
        return false;
    }


    if (packet_header->flasgs.overflow)
    {
        qDebug() << "Packet loss";
    }

    return true;
}

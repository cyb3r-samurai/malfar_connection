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

void DataServer::onCel(int dataChanelNumber)
{

}

void DataServer::onEndCel(int dataChanelNumber)
{

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
    while (udp_socket ->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();

        struct packet_header *packet_header =
            reinterpret_cast<struct packet_header *>(datagram.data().data());

        if(checkHeader(packet_header)!= true)
        {
            qDebug() << "error header";
            return;
        }

        const char *payload_data = datagram.data().data() + sizeof(struct packet_header);

        int total_reports = packet_header->data_size / report_size;
        if (total_reports % chanel_count != 0) {
            qDebug() << "missing data";
        }

        int total_sets = total_reports / chanel_count;

        for(int i = 0; i < total_sets; ++i) {
            for(int ch = 0; ch < chanel_count; ++ch) {
                int offset = (i* chanel_count +ch) * report_size;
                const int16_t* report = reinterpret_cast<const int16_t *>(payload_data + offset);
                int16_t i_data = qFromLittleEndian<qint16>(report[0]);
                int16_t q_data = qFromLittleEndian<qint16>(report[1]);
            }
        }
    }

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

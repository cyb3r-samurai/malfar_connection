#include "dataserver.h"

DataServer::DataServer(QObject *parent)
    : QObject{parent}
{
    reset_flag = false;


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
    if (udp_socket ->hasPendingDatagrams()) {
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

                for(int i = 1; i <=4; i++) {
                    if(m_cell_storage[ch*i].started()) {
                        if(m_cell_storage[ch*i].size() == 0) {
                            m_cell_storage[ch*i].setTime();
                        }
                        m_cell_storage[ch*i].append(i_data, q_data);
                    }
                }
            }
        }
    }
}

void DataServer::onAcceptCel(int data_chanel, int real_data_chanel, int sector,const QDateTime& start_time,int ka_number, int az, int angle)
{
        qint16 az_[2];
        az_[0]= az;
        az_[1] = angle;
    if(!m_cell_storage[real_data_chanel * sector].started()) {
        m_cell_storage[real_data_chanel * sector].set(data_chanel,0,ka_number,start_time,az_);
    }
    else {
        m_cell_storage[real_data_chanel * sector].sendAll();
        m_cell_storage[real_data_chanel * sector].set(data_chanel,0,ka_number,start_time,az_);

    }

}

void DataServer::onStop(int data_chanel, int real_data_chanel, int sector)
{
    Q_ASSERT(m_cell_storage[real_data_chanel* sector].started());

    m_cell_storage[real_data_chanel * sector].sendAll();

    m_cell_storage[real_data_chanel * sector].finish();
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


void DataServer::connect_server()
{
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

        tcp_socket->connectToHost("127.0.0.1:502", 9999);
        udp_socket->bind(QHostAddress::Any, 9999);


    m_p2SocketHandler = new P2SocketHandler;
    thread_p2 = new QThread;
    connect(thread_p2, &QThread::started, m_p2SocketHandler, &P2SocketHandler::start);
    m_p2SocketHandler->moveToThread(thread_p2);
    thread_p2->start();

    for(int i = 1; i <= 24; ++i) {
        m_cell_storage.emplace(std::make_pair(i, new CellStorage));
        connect(&m_cell_storage[i],&CellStorage::ready_to_write, m_p2SocketHandler,&P2SocketHandler::Send);
    }

}


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
    if(udp_socket ->hasPendingDatagrams()) {
        if(udp_socket->pendingDatagramSize() < 900){
            return;
        }
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        const struct packet_header *packet_header =
            reinterpret_cast<const struct packet_header *>(datagram.data().constData());

        if(checkHeader(packet_header)!= true)
        {
            qDebug() << errors++;
            return;
        }

        const char *payload_data = datagram.data().constData() + sizeof(struct packet_header);

        int total_reports = packet_header->data_size / report_size;
        if (total_reports % chanel_count != 0) {
            qDebug() << "missing data";
            return;
        }

        int total_sets = total_reports / chanel_count;

        for(int i = 0; i < total_sets; ++i) {
            for(int ch = 0; ch < chanel_count; ++ch) {
                int offset = (i* chanel_count +ch) * report_size;
                const int16_t* report = reinterpret_cast<const int16_t *>(payload_data + offset);
                int16_t i_data = qFromLittleEndian<qint16>(report[0]);
                int16_t q_data = qFromLittleEndian<qint16>(report[1]);

                for(int i = 0; i < 4; i++) {
                    if(m_cell_storage[i*chanel_count + ch].started()) {
                        if(m_cell_storage[i*chanel_count + ch].size() == 0) {
                            m_cell_storage[i*chanel_count + ch].setTime(getTime());
                        }
                        m_cell_storage[i*chanel_count +ch].append(i_data, q_data);
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
        if(m_cell_storage[real_data_chanel * sector].size() != 0) {
            m_cell_storage[real_data_chanel * sector].sendAll();
        }
        m_cell_storage[real_data_chanel * sector].set(data_chanel,0,ka_number,start_time,az_);

    }

}

void DataServer::onStop(int data_chanel, int real_data_chanel, int sector)
{
    qDebug() << "on Stop called" << data_chanel << real_data_chanel << sector;
    Q_ASSERT(m_cell_storage[real_data_chanel* sector].started());
    if(m_cell_storage[real_data_chanel * sector].size() > 0) {
        m_cell_storage[real_data_chanel * sector].sendAll();
    }
    m_cell_storage[real_data_chanel * sector].finish();
}

void DataServer::onStopDataChanel(quint8 dataChanelNumber)
{
    qDebug() << "on Stop data chanel called" << dataChanelNumber;
    auto stopFunc = [dataChanelNumber](auto& it) {
        if((&it)->second.getDataChanel() == dataChanelNumber) {
            if((&it)->second.size() != 0){
                (&it)->second.sendAll();
                (&it)->second.finish();
            }
        }
    };

    std::for_each(m_cell_storage.begin(), m_cell_storage.end(), stopFunc);
}

bool DataServer::checkHeader(const packet_header *packet_header)
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

bool DataServer::setAffinity(int cpuCore)
{
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpuCore, &cpuset);

    pthread_t current_thread = pthread_self();
    return (pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset) == 0);

}

double DataServer::getTime() const
{
    auto now = QDateTime::currentDateTime();
    double OADate2 = (now.toMSecsSinceEpoch() /86400000.0) + 25569.0;

    return OADate2;
}


void DataServer::connect_server()
{
    //qDebug() << "affinity"<< setAffinity(0);

    tcp_socket = new QTcpSocket(this);
    tcp_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(tcp_socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError)
#else
    connect(tcp_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [this](QAbstractSocket::SocketError)
#endif
            {
                qWarning() <<  "modbus TCP"  << QString(tcp_socket->errorString());
            });

    connect(tcp_socket, &QTcpSocket::stateChanged, this, [](int state)
            {
                if (state == QAbstractSocket::UnconnectedState)
                {
                    qWarning() << "modbus TcpSocket disconected";
                }
                else if (state == QAbstractSocket::ConnectedState)
                {
                    qWarning() << "modbus TcpSocket connected";
                }
            });

    connect(tcp_socket, &QTcpSocket::readyRead, this, &DataServer::readyReadTcp);

    udp_socket = new QUdpSocket(this);
    udp_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(udp_socket, &QUdpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError)
#else
    connect(udp_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [this](QAbstractSocket::SocketError)
#endif
            {
                qDebug() << "modbus UDP" << udp_socket->errorString();
            });
    connect(udp_socket, &QUdpSocket::stateChanged, this, [this](int state)
            {
                if (state == QAbstractSocket::UnconnectedState)
                {
                    qDebug() << "modbus Udp Socket unconnected";
                    //recieve_timer->stop();                                  // Stop polling
                }
                else if (state == QAbstractSocket::ConnectedState)
                {
                    qDebug() << "modbus TCP Connection established";                    // Start polling
                }
            });
    connect(udp_socket, &QUdpSocket::readyRead, this, &DataServer::readyReadUdp);

        tcp_socket->connectToHost("192.168.220.213", 9999);
        udp_socket->bind(QHostAddress::Any, 9999);


    m_p2SocketHandler = new P2SocketHandler;
    thread_p2 = new QThread;
    connect(thread_p2, &QThread::started, m_p2SocketHandler, &P2SocketHandler::start);
    m_p2SocketHandler->moveToThread(thread_p2);
    thread_p2->start(QThread::TimeCriticalPriority);

    storage_thread = new QThread();
    for(int i = 0; i <= 24; ++i) {
        m_cell_storage.emplace(std::make_pair(i, new CellStorage()));
        m_cell_storage[i].setParent(nullptr);
        m_cell_storage[i].moveToThread(storage_thread);
        connect(&m_cell_storage[i],&CellStorage::ready_to_write, m_p2SocketHandler,&P2SocketHandler::Send);
    }
    storage_thread->start(QThread::TimeCriticalPriority);
}

void DataServer::onTotalStop()
{
    qDebug() << "onTotalStop called";
    auto stopFunc = [](auto& it) {
        if((&it)->second.size() != 0) {
            (&it)->second.sendAll();
        }
        (&it)->second.finish();
    };

    std::for_each(m_cell_storage.begin(), m_cell_storage.end(), stopFunc);
}

void DataServer::onFinishSegment(int data_chanel, int real_data_chanel, int sector)
{
    qDebug() << "on Stop called" << data_chanel << real_data_chanel << sector;
    Q_ASSERT(m_cell_storage[real_data_chanel* sector].started());
    if(m_cell_storage[real_data_chanel * sector].size() > 0) {
        m_cell_storage[real_data_chanel * sector].sendAll();
    }
    m_cell_storage[real_data_chanel * sector].finish();
}

void DataServer::onStopSegment(quint8 data_chanel_number, quint8 real_chanel_number, quint8 sector)
{
    if(m_cell_storage[real_chanel_number * sector].started()) {
        qDebug() << "onStopSegment called" << data_chanel_number << real_chanel_number, sector;
        if(m_cell_storage[real_chanel_number * sector].size() > 0){
            m_cell_storage[real_chanel_number * sector].sendAll();
        }
        m_cell_storage[real_chanel_number* sector].finish();
    }
}


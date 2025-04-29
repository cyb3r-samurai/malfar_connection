#include "TcpServer.h"
#define HEADER_SIZE 12

TcpServer::TcpServer(QObject* parent) :
    QObject{parent}
{
    // m_ac = new AC();
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> dist(-127, 128);
    // signal_data = new QList<c_pair>;
    // for (qsizetype i =0; i < 1100; i++) {
    //     c_pair data;
    //     data.I = dist(rng);
    //     data.Q = dist(rng);
    //     signal_data->append(data);
    // }

    // QDateTime now = QDateTime::currentDateTime();
    // quint64  sec = now.toSecsSinceEpoch();
    // qDebug() << sec;

    // double OADAte = double(now.toSecsSinceEpoch()) / double (86400) + 25569;
   // std::cout << OADAte;
    //qDebug() << OADAte;

    server_ = new QTcpServer(this);
    message_processor_ = new MessageProcessor();

    connect(server_, &QTcpServer::newConnection, this, &TcpServer::on_client_connecting);
    connect(this, &TcpServer::client_msg_received, message_processor_, &MessageProcessor::on_client_msg_recieved);
    connect(message_processor_, &MessageProcessor::message_created, this, &TcpServer::on_message_ready);

    started_ = server_->listen(QHostAddress::Any, 5555);
    if (!started_) {
        qDebug() << "Server could not start";
    } else {
        qDebug() <<"Server started";
    }
}


void TcpServer::keep_alive()
{
    // if(!socket_ || !socket_->isOpen()) {
    //     qDebug() << "Socket not open or null";
    //     return;
    // }
    // Header header_test;
    // header_test.msg_type = 0x83;
    // header_test.n =  No_alignmet_size::report + 512;
    // qDebug() << "Header n " << header_test.n;
    // QByteArray header_bytes = header_test.serializeStruct();
    // Report test(256);
    // test.m = 256;
    // for(qsizetype i = 0;i < 256; i++) {
    //     test.info[i][0] =signal_data->at(i).I;
    //     test.info[i][1] = signal_data->at(i+256).Q;
    // }
    // QByteArray data = test.serializeStruct();
    // socket_->write(header_bytes);
    // socket_->write(data);


    // Header header_test2;
    // header_test2.msg_type = 0x83;
    // header_test2.n =  No_alignmet_size::report + 512;
    // QByteArray header_bytes2 = header_test2.serializeStruct();
    // Report test2(256);
    // test2.chanel_number = 8;
    // test2.m = 256;
    // for(qsizetype i = 0;i < 256; i++) {
    //     test2.info[i][0] =signal_data->at(i+512).I;
    //     test2.info[i][1] = signal_data->at(i+768).Q;
    // }
    // QByteArray data2 = test2.serializeStruct();
    // socket_->write(header_bytes2);
    // socket_->write(data2);
}

void TcpServer::on_client_connecting()
{
    qDebug() << "a client connected to server";
    socket_ = server_->nextPendingConnection();
    connect(socket_, &QTcpSocket::readyRead, this, &TcpServer::client_data_ready);
    connect(socket_, &QTcpSocket::disconnected, this, &TcpServer::client_disconnected);
    socketList_.append(socket_);
    m_timer_ = new QTimer(this);
    connect(m_timer_, &QTimer::timeout, this, &TcpServer::keep_alive, Qt::QueuedConnection);
    m_timer_->start(5000);
}

void TcpServer::client_disconnected()
{
    qDebug() << "Client Disconected";
}

void TcpServer::client_data_ready()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    Header header;
    QByteArray header_bytes;
    QByteArray msg_bytes;

    while(socket->bytesAvailable() >= HEADER_SIZE) {
        header_bytes = socket->read(HEADER_SIZE);
        header = DeserializeHeader(header_bytes);
        msg_bytes = socket->read(header.n);
        emit client_msg_received(header, msg_bytes);
    }
}

void TcpServer::on_message_ready(Header header, QByteArray data)
{
    QByteArray header_bytes = header.serializeStruct();
    socket_->write(header_bytes);
    socket_->write(data);
    qDebug() << "Client message send";
}


Header TcpServer::DeserializeHeader(QByteArray &data)
{
    Header header;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> header.version >> header.msg_type >> header.time >> header.n;

    return header;
}

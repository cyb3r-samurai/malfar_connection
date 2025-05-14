#include "TcpServer.h"
#define HEADER_SIZE 16

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

     QDateTime now = QDateTime::currentDateTime();
     quint64  sec = now.toSecsSinceEpoch();
     qDebug() << sec;

     double OADAte = double(now.toSecsSinceEpoch()) / double (86400) + 25569;
   // std::cout << OADAte;
    //qDebug() << OADAte;

    loadSettings();
    thread_message_processor = new QThread();
    thread_ac = new QThread();


    m_plan_storage = new PlanStorage();
    server_ = new QTcpServer(this);
    m_ac = new AC(m_plan_storage);
    m_report_state_checker = new ReportStateChecker(m_plan_storage);
    message_processor_ = new MessageProcessor(m_plan_storage, m_report_state_checker, m_ac);

    message_processor_->moveToThread(thread_message_processor);
    m_ac->moveToThread(thread_ac);

    thread_ac->start();
    thread_message_processor->start();
    connect(server_, &QTcpServer::newConnection, this, &TcpServer::on_client_connecting);
    connect(this, &TcpServer::client_msg_received, message_processor_, &MessageProcessor::on_client_msg_recieved);
    connect(message_processor_, &MessageProcessor::message_created, this, &TcpServer::on_message_ready);
    connect(this, &TcpServer::connected, message_processor_, &MessageProcessor::on_connected);
  //  connect(message_processor_, &MessageProcessor::cel_recieved, m_ac, &AC::OnCelRecieved);

    started_ = server_->listen(QHostAddress::Any, 5555);
    if (!started_) {
        qDebug() << "Server could not start";
    } else {
        qDebug() <<"Server started";
    }
    qDebug() << QThread::currentThreadId();
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

    emit connected();
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
        qDebug() << "msg bytes";
        qDebug() << header.n;
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
    stream.setByteOrder(QDataStream::BigEndian);

    stream >> header.version >> header.msg_type >>header.zero >> header.time >> header.n;
    qDebug() <<"Header Check";
    qDebug() << header.version;
    qDebug() << header.msg_type;
    qDebug() << header.zero;
    qDebug() << header.time;
    qDebug() << header.n;

    return header;
}

void TcpServer::loadSettings()
{
    QSettings settings;
    qDebug() << settings.fileName();
    m_preferences.port = settings.value("port", 5555).toInt();
}

void TcpServer::saveSettings()
{
    QSettings settings;
    settings.setValue("port", 5555);
}


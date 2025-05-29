#include "TcpServer.h"
#include <QTimer>
#define HEADER_SIZE 16

TcpServer::TcpServer(QObject* parent) :
    QObject{parent}
{
    loadSettings();
    server_ = new QTcpServer(this);
    started_ = server_->listen(QHostAddress::Any, 5555);
    if (!started_) {
        qWarning() << "Server could not start";
        QTimer::singleShot(500, this, &TcpServer::Timequit);
    } else {
        qInfo() <<"Server started";
    }

    thread_message_processor = new QThread();
    thread_ac = new QThread();
    thread_data_server = new QThread();

    m_ac = new AC();
    m_report_state_checker = new ReportStateChecker(m_ac->plan_storage());
    message_processor_ = new MessageProcessor(m_ac->plan_storage(), m_report_state_checker, m_ac);
    m_data_server = new DataServer();

    message_processor_->moveToThread(thread_message_processor);
    m_ac->moveToThread(thread_ac);
    m_data_server->moveToThread(thread_data_server);


    connect(server_, &QTcpServer::newConnection, this, &TcpServer::on_client_connecting);
    connect(this, &TcpServer::client_msg_received, message_processor_, &MessageProcessor::on_client_msg_recieved);
    connect(message_processor_, &MessageProcessor::message_created, this, &TcpServer::on_message_ready);
    connect(this, &TcpServer::connected, message_processor_, &MessageProcessor::on_connected);
    connect(m_ac, &AC::accept_cell, m_data_server, &DataServer::onAcceptCel);
    connect(m_ac, &AC::finish_data_chanel, m_data_server, &DataServer::onStop);
    connect(this, &TcpServer::connect_data_server,m_data_server,&DataServer::connect_server );
    connect(thread_data_server,&QThread::started, m_data_server,&DataServer::connect_server);

    thread_ac->start();
    thread_message_processor->start();
   // thread_data_server->start();
}

bool TcpServer::isStarted() const
{
    return started_;
}

void TcpServer::Timequit()
{
    QCoreApplication::quit();
}

void TcpServer::on_client_connecting()
{
    qInfo() << "П1 connected to server";
    socket_ = server_->nextPendingConnection();
 //   socket_->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption,64*1024*1024);
    connect(socket_, &QTcpSocket::readyRead, this, &TcpServer::client_data_ready);
    connect(socket_, &QTcpSocket::disconnected, this, &TcpServer::client_disconnected);
    client_connected = true;

    emit connected();
}

void TcpServer::client_disconnected()
{
    qInfo() << "Client Disconected";
    client_connected = false;
}

void TcpServer::client_data_ready()
{
    if(!header_readed) {
        if(socket_->bytesAvailable() >= HEADER_SIZE){
            header_bytes = socket_->read(HEADER_SIZE);
            header_ = DeserializeHeader(header_bytes);
            data_size = header_.n;
            header_readed = true;
        }
    }
    if(header_readed) {
        if(data_size >0) {
            QByteArray chunk = socket_->read(qMin(data_size,socket_->bytesAvailable()));
            msg_bytes += chunk;;
            data_size -= chunk.size();
        }
        if(data_size == 0){
            emit client_msg_received(header_, msg_bytes);
            header_readed = false;
            msg_bytes.clear();
            header_bytes.clear();
        }
    }
    // while(socket_->bytesAvailable() >= HEADER_SIZE) {
    //     header_bytes = socket_->read(HEADER_SIZE);
    //     header = DeserializeHeader(header_bytes);
    //     qint64 data_size = header.n;
    //     while(data_size >= 0){
    //         msg_bytes += socket_->read(data_size);
    //         qDebug() << msg_bytes.size();
    //         if(data_size > 0)
    //             socket_->waitForReadyRead(300);
    //         data_size -= msg_bytes.size();

    //     }
    // }
    // emit client_msg_received(header_, msg_bytes);
}

void TcpServer::on_message_ready(const Header& header, const QByteArray& data)
{
    QByteArray header_bytes = header.serializeStruct();
    socket_->write(header_bytes);
    socket_->write(data);
}

bool TcpServer::getClient_connected() const
{
    return client_connected;
}


Header TcpServer::DeserializeHeader(QByteArray &data)
{
    Header header;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> header.version >> header.msg_type >>header.zero >> header.time >> header.n;

    return header;
}

void TcpServer::loadSettings()
{
    QSettings settings;
    qDebug()<<"Путь к конфигурационному файлу:"<< settings.fileName();
    m_preferences.port = settings.value("port", 5555).toInt();
}

void TcpServer::saveSettings()
{
    QSettings settings;
    settings.setValue("port", 5555);
    settings.setValue("p2/port", 4444);
    settings.setValue("p2/ip", "127.0.0.1");
}


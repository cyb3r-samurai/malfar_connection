#include "p2sockethandler.h"

P2SocketHandler::P2SocketHandler(QObject *parent)
    : QObject{parent}
{}

P2SocketHandler::~P2SocketHandler()
{
    m_socket->disconnect();
    delete m_socket;
}

void P2SocketHandler::start()
{
    loadSettings();
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(m_ip, m_port);

    m_socket = new QTcpSocket(this);
    m_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError)
#else
    connect(tcp_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [this](QAbstractSocket::SocketError)
#endif
            {
                qDebug() <<  "TCP"  << QString(m_socket->errorString());
            });

    connect(m_socket, &QTcpSocket::stateChanged, this, [](int state)
            {
                if (state == QAbstractSocket::UnconnectedState)
                {
                    qDebug() << "Socket disconected";
                }
                else if (state == QAbstractSocket::ConnectedState)
                {
                    qDebug() << "Socket conected";
                }
            });

}

void P2SocketHandler::Send(Report & report)
{
    QByteArray data = report.serializeStruct();
    Header header;
    header.msg_type = 0x82;
    header.n = 20 + (2 * report.m);

    Q_ASSERT(data.size() == header.n);

    m_socket->write(header.serializeStruct());
    m_socket->write(data);
    qDebug() << "data sended";
}

void P2SocketHandler::loadSettings()
{
    QSettings settings;
    m_port = settings.value("p2/port", 4444).toInt();
    m_ip = settings.value("p2/ip" "127.0.0.1").toString();
}

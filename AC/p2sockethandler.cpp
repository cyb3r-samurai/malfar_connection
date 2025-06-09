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

    reconnectTimer = new QTimer;
    reconnectTimer->setSingleShot(true);
    connect(reconnectTimer, &QTimer::timeout, this, [this]() {

            m_socket->abort();
            m_socket->connectToHost("192.168.220.114", 4444);
            m_socket->waitForConnected(4000);
            if(m_socket->state() != QAbstractSocket::ConnectedState){
                reconnectTimer->start(5000);
            }
    });

    m_socket = new QTcpSocket(this);
    m_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    m_socket->connectToHost("192.168.220.114", 4444);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError)
#else
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [this](QAbstractSocket::SocketError)
#endif
            {
                qDebug() <<  "TCP"  << QString(m_socket->errorString());
                if(m_socket->state()!= QAbstractSocket::ConnectedState) {
                    connected = false;
                    reconnectTimer->start(5000);
                }
            });

    connect(m_socket, &QTcpSocket::stateChanged, this, [this](int state)
            {
                if (state == QAbstractSocket::UnconnectedState)
                {
                    qDebug() << "p2 Socket disconected";
                    connected = false;
                }
                else if (state == QAbstractSocket::ConnectedState)
                {
                    qDebug() << "Socket conected";
                    connected = true;
                }
            });
    connect(m_socket, &QTcpSocket::disconnected, this, [this](){
        if(m_socket->state() != QAbstractSocket::ConnectedState){
        reconnectTimer->start(5000);
            connected= false;
        }
});
}

void P2SocketHandler::stop()
{

}

void P2SocketHandler::Send(std::shared_ptr<Report>report)
{
    if(connected){
        QByteArray data = report->serializeStruct();
    Header header;
    header.msg_type = 0x82;
    header.n = 20 + (2 * report->m);
    header.time = getTime();

    Q_ASSERT(data.size() == header.n);

    m_socket->write(header.serializeStruct());
    count += m_socket->write(data);
    if (count > 1000000){
        qDebug() << "count 1000000"<<count;
        count = 0;
    }
    }
}

void P2SocketHandler::loadSettings()
{
    QSettings settings;
    m_port = settings.value("p2/port", 4444).toInt();
    m_ip = settings.value("p2/ip", "127.0.0.1").toString();
}

double P2SocketHandler::getTime() const
{
    auto now = QDateTime::currentDateTime();
    double OADate2 = (now.toMSecsSinceEpoch() /86400000.0) + 25569.0;

    return OADate2;
}

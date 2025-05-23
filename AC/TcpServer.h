#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Message.h"
#include "packet.h"
#include "messageprocessor.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <random>

struct c_pair{
    qint8 I;
    qint8 Q;
};
class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    bool isStarted() const;
    void StartSending();

    signals:
    void ClientConnected();
    void DataRecieved(QByteArray);
    void client_msg_received(Header, QByteArray);


private slots:
    void keep_alive();

    void on_client_connecting();
    void client_disconnected();

    void client_data_ready();
    void on_message_ready(Header, QByteArray);

private:
    QTcpServer* server_;
    QList<QTcpSocket *> socketList_;
    QTcpSocket* socket_;
    bool started_;
    QTimer* m_timer_;
    MessageProcessor message_processor_;

    Header DeserializeHeader(QByteArray& data);
    QList<c_pair>* signal_data;
};
#endif // TCPSERVER_H

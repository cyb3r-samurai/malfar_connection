#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "ac.h"
#include "Message.h"
#include "messageprocessor.h"
#include "packet.h"
#include "planstorage.h"
#include "reportstatechecker.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>

#include <memory>

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
    MessageProcessor *message_processor_;
    AC* m_ac;
    PlanStorage* m_plan_storage;
    ReportStateChecker * m_report_state_checker;

    QThread * thread_message_processor;
    QThread * thread_ac;

    bool started_;

    Header DeserializeHeader(QByteArray& data);
};
#endif // TCPSERVER_H

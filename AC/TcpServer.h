#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "ac.h"
#include "Message.h"
#include "messageprocessor.h"
#include "packet.h"
#include "planstorage.h"
#include "reportstatechecker.h"
#include "dataserver.h"

#include "sched.h"

#include <QObject>
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>
#include <QSettings>

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

    bool getClient_connected() const;

signals:
    void ClientConnected();
    void DataRecieved(QByteArray);
    void client_msg_received(const Header&, const QByteArray&);
    void connected();
    void finish();
    void connect_data_server();

public slots:
    void Timequit();

private slots:
    void on_client_connecting();
    void client_disconnected();


    void client_data_ready();

    void on_message_ready(const Header&, const QByteArray&);

private:

    void setAffinity(int cpuCore);

    Header header_;
    QByteArray  header_bytes;
    QByteArray msg_bytes;
    bool header_readed;
    qint64 data_size;

    QTcpServer* server_;
    QTcpSocket* socket_;

    MessageProcessor *message_processor_;
    AC* m_ac;
    PlanStorage* m_plan_storage;
    ReportStateChecker * m_report_state_checker;
    DataServer * m_data_server;

    QThread * thread_message_processor;
    QThread * thread_ac;
    QThread * thread_data_server;

    bool started_ = false;
    bool client_connected = false;

    Header DeserializeHeader(QByteArray& data);

    void loadSettings();
    void saveSettings();




    struct SPreferences {
        int port;
    };
    SPreferences m_preferences;
};
#endif // TCPSERVER_H

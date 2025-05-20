#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include "Message.h"
#include "packet.h"

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QThread>


class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    void connect_to_device(QString ip, int port);
    void disconnect();
    QAbstractSocket::SocketState state();
    bool is_connected();

signals:
    void connected();
    void disconnected();
    void state_changed(QAbstractSocket::SocketState);
    void error_occured(QAbstractSocket::SocketError);
    void data_ready(Packet);

public slots:
    void send(QByteArray& header, QByteArray& msg);
private slots:
    void socket_state_changed(QAbstractSocket::SocketState);
    void socket_ready_read();
private:
    QTcpSocket socket_;
    QString ip_;
    int port_;

    Header DeserializeHeader(QByteArray& data);
};

#endif // DEVICECONTROLLER_H

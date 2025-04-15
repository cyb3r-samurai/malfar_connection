#include "DeviceController.h"
#define HEADER_SIZE 12

DeviceController::DeviceController(QObject *parent)
    : QObject{parent}
{
    connect(&socket_, &QTcpSocket::connected, this, &DeviceController::connected);
    connect(&socket_, &QTcpSocket::disconnected, this, &DeviceController::disconnected);
    connect(&socket_, &QTcpSocket::stateChanged, this, &DeviceController::socket_state_changed);
    connect(&socket_, &QTcpSocket::errorOccurred, this, &DeviceController::error_occured);
    connect(&socket_, &QTcpSocket::readyRead, this, &DeviceController::socket_ready_read);
}

void DeviceController::connect_to_device(QString ip, int port)
{
    if (socket_.isOpen()){
        if (ip_ == ip && port_ == port) {
            return;
       }
        socket_.close();
    }
    ip_ = ip;
    port_ = port;
    socket_.connectToHost(ip_, port_);
}

void DeviceController::disconnect()
{
    socket_.close();
}

QAbstractSocket::SocketState DeviceController::state()
{
    return socket_.state();
}


bool DeviceController::is_connected()
{
    return socket_.state() == QAbstractSocket::ConnectedState;
}

void DeviceController::send(QByteArray header, QByteArray msg)
{
    socket_.write(header);
    socket_.write(msg);

}

void DeviceController::socket_state_changed(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::SocketState::UnconnectedState) {
        socket_.close();
    }
    emit state_changed(state);
}

void DeviceController::socket_ready_read()
{
    qDebug() << "socket thread " << QThread::currentThreadId() ;
    while(socket_.bytesAvailable() >= HEADER_SIZE) {
        QByteArray header_bytes = socket_.read(HEADER_SIZE);
        Header header = DeserializeHeader(header_bytes);

        QByteArray data_bytes = socket_.read(header.n);
        Packet packet(header, data_bytes);

        emit data_ready(packet);
    }
}

Header DeviceController::DeserializeHeader(QByteArray& data)
{
    Header header;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> header.version >> header.msg_type >> header.zero >> header.time >> header.n;

    return header;
}

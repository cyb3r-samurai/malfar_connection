#ifndef DATASERVER_H
#define DATASERVER_H

#include "cellstorage.h"
#include "Message.h"

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QtEndian>
#include <QDateTime>
#include <QTimer>
#include <QThread>


class DataServer : public QObject
{
    Q_OBJECT
public:
    explicit DataServer(QObject *parent = nullptr);

signals:


private slots:
    void readyReadTcp();
    void readyReadUdp();

public slots:
    void onAcceptCel(int, int, int, const QDateTime&,int,  int, int);
    void onStop(int, int, int);
    void connect_server();

private:
    const uint8_t protocol_version = 2;
    const uint8_t BUF_NUMBER = 6;

    struct packet_header                        // Заголовок пакета
    {
        uint8_t protocol_version;               // Версия протокола
        uint8_t counter;                        // Счётчик переданных пакетов
        struct
        {
            uint8_t overflow            : 1;    // Флаг переполнения буфера
            uint8_t                     : 7;
        } flasgs;
        uint8_t                         : 8;
        uint32_t timestamp;                     // Метка времени пакета
        uint16_t buf_size;                      // Сколько байт данных доступно в буфере
        uint16_t data_size;                     // Сколько байт данных следует в пакете
    } __attribute__((packed));

    bool reset_flag;
    bool recording;

    const int chanel_count = 6;
    const int report_size = 4;

    QTcpSocket *tcp_socket;
    QUdpSocket *udp_socket;

    bool checkHeader(struct packet_header *packet_header);
    std::map<int, CellStorage> m_cell_storage;
};

#endif // DATASERVER_H

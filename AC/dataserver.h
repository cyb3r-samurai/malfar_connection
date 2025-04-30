#ifndef DATASERVER_H
#define DATASERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QUdpSocket>

class DataServer : public QObject
{
    Q_OBJECT
public:
    explicit DataServer(QObject *parent = nullptr);


signals:

private slots:
    void readyReadTcp();
    void readyReadUdp();

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

    QTcpSocket *tcp_socket;
    QUdpSocket *udp_socket;

    bool checkHeader(struct packet_header *packet_header);
};

#endif // DATASERVER_H

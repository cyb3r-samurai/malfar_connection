#ifndef P2SOCKETHANDLER_H
#define P2SOCKETHANDLER_H

#include "Message.h"
#include "packet.h"

#include <QObject>
#include <QVariant>
#include <QSettings>
#include <QTcpSocket>
#include <QTimer>
#include <QDateTime>

class P2SocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit P2SocketHandler(QObject *parent = nullptr);
    ~P2SocketHandler();

public slots:
    void Send(std::shared_ptr<Report>);
    void start();
    void stop();

signals:
    void p2StateChnge(bool);
private:
    void loadSettings();
    QTcpSocket* m_socket;
    QString m_ip;
    int m_port;
    long long count;
    QTimer* reconnectTimer;
    bool connected = false;

    double getTime() const;
};

#endif // P2SOCKETHANDLER_H

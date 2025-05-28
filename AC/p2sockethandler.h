#ifndef P2SOCKETHANDLER_H
#define P2SOCKETHANDLER_H

#include "Message.h"
#include "packet.h"

#include <QObject>
#include <QVariant>
#include <QSettings>
#include <QTcpSocket>

class P2SocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit P2SocketHandler(QObject *parent = nullptr);
    ~P2SocketHandler();
    void start();

public slots:
    void Send(Report &);

signals:

private:
    void loadSettings();
    QTcpSocket* m_socket;
    QString m_ip;
    int m_port;
};

#endif // P2SOCKETHANDLER_H

#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include <QDebug>
#include <QDateTime>

#include "Message.h"
#include "packet.h"

class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessor(QObject *parent = nullptr);

signals:
    void message_created(Header, QByteArray);

public slots:
    void on_client_msg_recieved(Header, QByteArray);

private:
    void create_responce(quint8);
    quint32 seconds_since_epoch();
    QDateTime secondsToDatetime(quint32 sec) const;
};

#endif // MESSAGEPROCESSOR_H

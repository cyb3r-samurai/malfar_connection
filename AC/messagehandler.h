#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

#include "Message.h"
#include "packet.h"

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr);
    virtual bool handleMessage(Packet&) = 0;
};

#endif // MESSAGEHANDLER_H

#ifndef SESSIONREQUESTHANDLER_H
#define SESSIONREQUESTHANDLER_H

#include <QObject>
#include "messagehandler.h"

class SessionRequestHandler : public MessageHandler
{
    Q_OBJECT
public:
    explicit SessionRequestHandler(QObject *parent = nullptr);
    virtual bool handleMessage(Packet &) override;

signals:
    void requestRecieved(long long);
};

#endif // SESSIONREQUESTHANDLER_H

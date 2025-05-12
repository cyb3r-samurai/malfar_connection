#ifndef STOPHANDLER_H
#define STOPHANDLER_H

#include <QObject>
#include "messagehandler.h"

class StopHandler : public MessageHandler
{
    Q_OBJECT
public:
    explicit StopHandler(QObject *parent = nullptr);
    virtual bool handleMessage(Packet &) override;
signals:
    void stopRecieve(long long);
};

#endif // STOPHANDLER_H

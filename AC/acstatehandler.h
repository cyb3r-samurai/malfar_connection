#ifndef ACSTATEHANDLER_H
#define ACSTATEHANDLER_H

#include <QObject>
#include "messagehandler.h"

class AcStateHandler : public MessageHandler
{
    Q_OBJECT
public:
    explicit AcStateHandler(QObject *parent = nullptr);
    virtual bool handleMessage(const Packet& packet) override;

signals:
    void requestCreated(long long);
};

#endif // ACSTATEHANDLER_H

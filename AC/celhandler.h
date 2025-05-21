#ifndef CELHANDLER_H
#define CELHANDLER_H

#include <QObject>
#include <QDebug>

#include <memory>

#include "messagehandler.h"

class CelHandler : public MessageHandler
{
    Q_OBJECT
public:
    explicit CelHandler(QObject *parent = nullptr);
    virtual bool handleMessage(const Packet&) override;

signals:
   void celCreated(std::shared_ptr<Cel>, long long);

};

#endif // CELHANDLER_H

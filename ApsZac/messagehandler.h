#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "packet.h"
#include "Message.h"
#include "simpletabledata.h"
#include "celmodel.h"

#include <QDebug>

class MessageHandler
{
public:
    MessageHandler();
    virtual bool HandleMessage(Packet &packet) = 0;
};

class RecieveStateHandler : public MessageHandler
{
public:
    RecieveStateHandler();
    virtual bool HandleMessage(Packet &pakcket) override;
    RecieveState deserialize_recieve_state(QByteArray& data);

private:
};

class StatusHandler : public MessageHandler
{
public:
    StatusHandler();
    virtual bool HandleMessage(Packet &packet)override;
    Status deserialize_status(QByteArray& data);
};

class SessionsInfoHandler : public MessageHandler
{
public:
    SessionsInfoHandler(SimpleTableData *model);
    virtual bool HandleMessage(Packet &pakcket) override;
    SessionsInfo deserialize_sessions_info(QByteArray& data);

private:
    SimpleTableData *model;
};

class ReportHandler : public MessageHandler
{
public:
    ReportHandler(CelModel *celmodel);
    virtual bool HandleMessage(Packet &pakcket) override;
    Report deserialize_report(QByteArray& data);

private:
    CelModel * m_celmodel;
};

class  AcStateHandler : public MessageHandler
{
public:
    AcStateHandler();
    virtual bool HandleMessage(Packet &pakcket) override;
    AcState deserialize_ac_state(QByteArray& data);
private:
};
#endif // MESSAGEHANDLER_H

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
    RecieveStateHandler(QList<QPair<Header, RecieveState>> *storage);
    virtual bool HandleMessage(Packet &pakcket) override;
    RecieveState deserialize_recieve_state(QByteArray& data);

private:
    QList<QPair<Header, RecieveState>>* recieve_state_storage_;
};

class SessionsInfoHandler : public MessageHandler
{
public:
    SessionsInfoHandler(QList<QPair<Header, SessionsInfo>> *storage, SimpleTableData *model);
    virtual bool HandleMessage(Packet &pakcket) override;
    SessionsInfo deserialize_sessions_info(QByteArray& data);

private:
    QList<QPair<Header, SessionsInfo>>* sessions_info_storage_;
    SimpleTableData *model;
};

class ReportHandler : public MessageHandler
{
public:
    ReportHandler(QList<QPair<Header, Report>> *storage, CelModel *celmodel);
    virtual bool HandleMessage(Packet &pakcket) override;
    Report deserialize_report(QByteArray& data);

private:
    QList<QPair<Header, Report>>* report_info_storage_;
    CelModel * m_celmodel;
};

class  AcStateHandler : public MessageHandler
{
public:
    AcStateHandler(QList<QPair<Header, AcState>> *storage);
    virtual bool HandleMessage(Packet &pakcket) override;
    AcState deserialize_ac_state(QByteArray& data);
private:
    QList<QPair<Header,AcState>>* ac_state_storage_;
};
#endif // MESSAGEHANDLER_H

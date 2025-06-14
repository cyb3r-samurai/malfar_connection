#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QThread>
#include <QList>

#include "ac.h"
#include "acstatehandler.h"
#include "Message.h"
#include "messagebroker.h"
#include "packet.h"
#include "planstorage.h"
#include "reportstatechecker.h"
#include "messagehandler.h"
#include "celhandler.h"
#include "stophandler.h"
#include "sequentialidprovider.h"
#include "sessionrequesthandler.h"

#include <functional>

class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessor(PlanStorage * p_s, ReportStateChecker * r_s, AC* ac, QObject *parent = nullptr);

signals:
    void message_created(Header, QByteArray);
    void cel_recieved(std::shared_ptr<Cel> m_cel);
    void timeToCreateStartMessage();

public slots:
    void on_client_msg_recieved(const Header&, const QByteArray&);
    void handlePacket(const Packet& packet);
    void savePacket(const Packet& packet);
    void on_connected();

private slots:
    void onReciveStateCreated(std::shared_ptr<RecieveState>);
    void onSessionStateCreated(std::shared_ptr<SessionInfo>);
    void onAcStateCreated(std::shared_ptr<AcState>);
    void statusResponse(long long, quint8);

private:
    QTimer* my_timer;
    bool m_connected = false;
    quint32 seconds_since_epoch();
    QDateTime secondsToDatetime(quint32 sec) const;

    QVector<Packet>* m_packet_storage;
    QList<std::shared_ptr<MessageHandler>>* m_msg_handlers;
    ReportStateChecker* m_state_checker;
    PlanStorage* m_plan_storage;

    AC* m_ac;
    std::map<int, SectorPlan>* m_test_data;

    void print_current_state() const;
    void initHandlers();
    void initResponceMessageCreation();
    void initMessageBroker();
    void initPacketStorage();
    void startTimer();
    double getTime() const;
};

#endif // MESSAGEPROCESSOR_H

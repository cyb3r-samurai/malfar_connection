#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QThread>

#include "Message.h"
#include "packet.h"
#include "planstorage.h"


class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessor(PlanStorage * p_s, QObject *parent = nullptr);

signals:
    void message_created(Header, QByteArray);
    void cel_recieved(std::shared_ptr<Cel> m_cel);

public slots:
    void on_client_msg_recieved(Header, QByteArray);

private slots:
    void keep_alive();

private:
    QTimer* my_timer;
    void create_responce(quint8);
    quint32 seconds_since_epoch();
    QDateTime secondsToDatetime(quint32 sec) const;
    QList<RecieveState> m_recieve_state;

    PlanStorage* m_plan_storage;
    std::map<int, SectorPlan>* m_test_data;
    void print_current_state() const;
};

#endif // MESSAGEPROCESSOR_H

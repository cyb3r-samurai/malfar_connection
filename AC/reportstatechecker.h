//Класс для запросоов телеметрии

#ifndef REPORTSTATECHECKER_H
#define REPORTSTATECHECKER_H

#include "Message.h"
#include "planstorage.h"
#include "datachanel.h"

#include <QTimer>
#include <QThread>
#include <QObject>
#include <QDebug>

#include <map>
#include <memory>

class ReportStateChecker : public QObject
{
    Q_OBJECT
public:
    explicit ReportStateChecker(PlanStorage* p_s, QObject *parent = nullptr);

public slots:
    void onTimer();
    void onRequest(long long);
    void onAcStateRequest(long long);
    void onStartingServer();

signals:
    void reciveStateCreated(std::shared_ptr<RecieveState>);
    void acStateCreated(std::shared_ptr<AcState>);
    void sessionInfoCreated(std::shared_ptr<SessionInfo>);

private:
//    QTimer* m_timer;
    PlanStorage *m_plan_storage;

    std::map<int, DataChanel> m_data_chanel_plans;

    void create_ac_state();
    void create_session_info();
    void create_recieve_state();
};

#endif // REPORTSTATECHECKER_H

//Класс для запросоов телеметрии

#ifndef REPORTSTATECHECKER_H
#define REPORTSTATECHECKER_H

#include "Message.h"
#include "planstorage.h"
#include "datachanel.h"

#include <QTimer>
#include <QObject>

#include <map>
#include <memory>

class ReportStateChecker : public QObject
{
    Q_OBJECT
public:
    explicit ReportStateChecker(PlanStorage* p_s, QObject *parent = nullptr);

public slots:
    void onTimer();

signals:
    void reciveStateCreated(std::shared_ptr<RecieveState>);
    void acStateCreated(std::shared_ptr<AcState>);

private:
//    QTimer* m_timer;
    PlanStorage *m_plan_storage;

    std::map<int, DataChanel> *m_data_chanel_plans;

    void create_recieve_state();
    void create_ac_state();
};

#endif // REPORTSTATECHECKER_H

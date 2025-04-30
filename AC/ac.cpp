#include "ac.h"

AC::AC(PlanStorage *p_s, QObject *parent) :
    QObject{parent}, m_plan_storage{p_s}
{
    m_chanel_plans = new std::map<int, DataChanel>;
    m_sector_plans = new std::map<int, SectorPlan> ;
    m_plan_factory =  new PlanFactory(m_chanel_plans, m_sector_plans);

    m_timer = new QTimer;
   // m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, this, &AC::CheckTime);
}

void AC::OnCelRecieved(std::shared_ptr<Cel> cel)
{
    qDebug() << "cel recieved in ac";
    qDebug() << QThread::currentThreadId();
    qDebug() << cel->chanel_number;

    if(m_plan_factory->createPlan(cel)) {
        qDebug() << "Plan created";
        m_plan_storage->changePlans(*m_sector_plans, *m_chanel_plans);
    }
    else {

    }
}


void AC::CheckTime()
{
    int size = m_sector_plans->size();
    for(int i = 1; i < size; i++) {

    }

}

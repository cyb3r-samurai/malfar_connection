#include "ac.h"


AC::AC(QObject *parent) :
    QObject{parent}
{
    m_chanel_plans = new std::map<int, DataChanel>;
    m_sector_plans = new std::map<int, SectorPlan> ;
    m_plan_factory =  new PlanFactory(m_chanel_plans, m_sector_plans);

    m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, this, &AC::CheckTime);
}

void AC::OnCelRecieved(std::shared_ptr<Cel> cel)
{
    if(m_plan_factory->createPlan(cel)) {

    }
    else {

    }
}

#include "ac.h"

AC::AC(QObject *parent) :
    QObject{parent}
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
    qDebug() << cel->chanel_number;

    if(m_plan_factory->createPlan(cel)) {
        qDebug() << "Plan created";
        (*m_sector_plans)[1].display_info();
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

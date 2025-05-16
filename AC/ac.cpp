#include "ac.h"

AC::AC(PlanStorage *p_s, QObject *parent) :
    QObject{parent}, m_plan_storage{p_s}
{
    m_chanel_plans = new std::map<int, DataChanel>;
    m_sector_plans = new std::map<int, SectorPlan> ;
    m_plan_factory =  new PlanFactory(m_chanel_plans, m_sector_plans);

    m_timer = new QTimer;
    m_timer->setTimerType(Qt::PreciseTimer);
    startAtNextSecond();
    connect(m_timer, &QTimer::timeout, this, &AC::CheckTime);
}

void AC::OnCelRecieved(std::shared_ptr<Cel> cel, long long packet_id)
{
    if(m_plan_factory->createPlan(cel)) {
        qInfo() << "Планы созданы в канале данных:" << cel->chanel_number;
        m_plan_storage->changePlans(*m_sector_plans, *m_chanel_plans);
        emit messageHandled(packet_id, 0);
    }
    else {

    }
}


void AC::onStopRecieve(long long packet_id)
{
    m_chanel_plans->clear();
    m_sector_plans->clear();
    m_plan_storage->changePlans(*m_sector_plans, *m_chanel_plans);
    emit messageHandled(packet_id, 0);
}


void AC::CheckTime()
{
    int size = m_sector_plans->size();
    auto sector_it =  m_sector_plans->begin();

    QDateTime now = QDateTime::currentDateTime();

    while(sector_it != m_sector_plans->end()) {
        auto segment_list = sector_it->second.getSegment_plan();
        auto segment_it = segment_list->begin();
        while (segment_it != segment_list->end()) {
            auto segment_ptr = segment_it->get();
            auto first_time_it = segment_ptr->time_cel->time.begin();
            if (first_time_it != segment_ptr->time_cel->time.end()) {
                QDateTime first_time = *first_time_it;
                while (first_time <= now) {
                   // qint64 sec2 = (first_time - 25569) * 86400;
                   // QDateTime time = QDateTime::fromSecsSinceEpoch(sec2);
                    qInfo() << "Целеукозание применено: угол" << segment_ptr->time_cel->angle.front() << ", азимут" << segment_ptr->time_cel->az.front()
                            << "Запланированное время: " << first_time.time();
                    ++first_time_it;
                    segment_ptr->time_cel->time.pop_front();
                    segment_ptr->time_cel->angle.pop_front();
                    segment_ptr->time_cel->az.pop_front();
                    if(first_time_it == segment_ptr->time_cel->time.end()) {
                        m_chanel_plans->at(segment_ptr->data_chanel_number).pop();
                        if(m_chanel_plans->at(segment_ptr->data_chanel_number).is_empty()) {
                            m_chanel_plans->extract(segment_ptr->data_chanel_number);
                            qInfo() << "Планы слежения в канале данных:"<< segment_ptr->data_chanel_number << "выполнены";
                        }
                        segment_list->erase(segment_it++);
                        if (segment_it == segment_list->end()) {
                            m_sector_plans->erase(sector_it++);
                        }
                        m_plan_storage->changePlans(*m_sector_plans, *m_chanel_plans);
                        break;
                    }
                    first_time = *first_time_it;
            }
        }

            if (first_time_it != segment_ptr->time_cel->time.end()) {
                ++segment_it;
                }
        }
        if( sector_it != m_sector_plans->end()) {
            ++sector_it;
        }
    }
}

void AC::startAtNextSecond()
{
    QDateTime now = QDateTime::currentDateTime();
    int msecToNextSecond = 1000 - now.time().msec();
    QTimer::singleShot(msecToNextSecond, [this](){
        m_timer->start(500);
    });
}


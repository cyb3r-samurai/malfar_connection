#include "ac.h"

AC::AC(QObject *parent) :
    QObject{parent}
{
    m_plan_storage = new PlanStorage;
    m_chanel_plans = m_plan_storage->data_chanels_plans();
    m_sector_plans = m_plan_storage->sector_plans();

    m_plan_factory =  new PlanFactory(m_plan_storage);

    m_plan_factory_thread = new QThread;

    m_plan_factory->moveToThread(m_plan_factory_thread);

    m_plan_factory_thread->start();

    m_timer = new QTimer;
    m_timer->setTimerType(Qt::PreciseTimer);
    startAtNextSecond();
    connect(m_timer, &QTimer::timeout, this, &AC::CheckTime);
}


void AC::onStopRecieve(long long packet_id)
{
    m_plan_storage->lockWrite();
    m_chanel_plans->clear();
    m_sector_plans->clear();
    m_plan_storage->unloock();
    qDebug() << "recive stoped";
    emit messageHandled(packet_id, 0);
}


void AC::CheckTime()
{
    m_plan_storage->lockWrite();
    auto sector_it =  m_sector_plans->begin();

    QDateTime now = QDateTime::currentDateTime();

    while(sector_it != m_sector_plans->end()) {
        bool sector_erased = false;
        auto segment_list = sector_it->second.getSegment_plan();
        auto segment_it = segment_list->begin();
        while (segment_it != segment_list->end()) {
            bool segment_erased = false;
            auto segment_ptr = segment_it->get();
            auto first_time_it = segment_ptr->time_cel->time.begin();
            if (first_time_it != segment_ptr->time_cel->time.end()) {
                QDateTime first_time = *first_time_it;
                while (first_time <= now) {
                   // qint64 sec2 = (first_time - 25569) * 86400;
                   // QDateTime time = QDateTime::fromSecsSinceEpoch(sec2);
                    qInfo() << "Целеукозание применено: канал данных"<< segment_ptr->data_chanel_number << ", сектор приема" << sector_it->first
                            << ", азимут" << segment_ptr->time_cel->az.front() << "угол" << segment_ptr->time_cel->angle.front() << '\n'
                            << "номер физического канала данных:"<<segment_ptr->chanel_number <<"Запланированное время: " << first_time.time();
                    emit accept_cell(segment_ptr->data_chanel_number,segment_ptr->chanel_number,
                                     segment_ptr->sector_number, QDateTime::currentDateTime(),segment_ptr->ka_number,
                                     segment_ptr->time_cel->az.front(),segment_ptr->time_cel->angle.front());
                    ++first_time_it;
                    segment_ptr->time_cel->time.pop_front();
                    segment_ptr->time_cel->angle.pop_front();
                    segment_ptr->time_cel->az.pop_front();
                    if(first_time_it == segment_ptr->time_cel->time.end()) {
                        m_chanel_plans->at(segment_ptr->data_chanel_number).pop();
                        qDebug() << "Chanel" << segment_ptr->data_chanel_number << "pop" << m_chanel_plans->at(segment_ptr->data_chanel_number).segments().size();
                        qInfo() << m_chanel_plans->size() << m_sector_plans->size();
                        if(m_chanel_plans->at(segment_ptr->data_chanel_number).is_empty()) {
                            qInfo() << "Планы слежения в канале данных:"<< segment_ptr->data_chanel_number << "выполнены.";
                            m_chanel_plans->extract(segment_ptr->data_chanel_number);
                            emit finish_data_chanel(segment_ptr->data_chanel_number, segment_ptr->chanel_number, segment_ptr->sector_number);
                        }
                        segment_list->erase(segment_it++);
                        segment_erased = true;
                        if (segment_list->empty()) {
                            qInfo() << "Планы слежения в секторе" << sector_it->first << "выполнены.";
                            m_sector_plans->erase(sector_it++);
                            sector_erased = true;
                        }
                        qInfo() << m_chanel_plans->size()<< m_sector_plans->size();
                        break;
                    }
                    first_time = *first_time_it;
                }
            }

            if (!segment_erased) {
                ++segment_it;
            }
        }
        if(!sector_erased) {
            ++sector_it;
        }
    }
    m_plan_storage->unloock();
}

void AC::startAtNextSecond()
{
    QDateTime now = QDateTime::currentDateTime();
    int msecToNextSecond = 1000 - now.time().msec();
    QTimer::singleShot(msecToNextSecond, [this](){
        m_timer->start(500);
    });
}

PlanFactory *AC::plan_factory() const
{
    return m_plan_factory;
}

PlanStorage *AC::plan_storage() const
{
    return m_plan_storage;
}


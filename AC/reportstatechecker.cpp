#include "reportstatechecker.h"

ReportStateChecker::ReportStateChecker(PlanStorage *p_s, QObject *parent)
    : QObject{parent}, m_plan_storage{p_s}
{
//    m_timer = new QTimer();
//    connect(m_timer, &QTimer::timeout, this, &ReportStateChecker::onTimer);
}

void ReportStateChecker::onTimer()
{
    m_plan_storage->lockRead();
    m_data_chanel_plans = m_plan_storage->data_chanels_plans();
    m_plan_storage->unloock();

    //TODO:: получить телеметрию
    if(m_data_chanel_plans) {
        create_recieve_state();
    }
}

void ReportStateChecker::create_recieve_state()
{
    auto recievedStatePtr = std::make_shared<RecieveState>();
    quint8 active_chanels_count = m_data_chanel_plans->size();
    recievedStatePtr->initializeChanelMas(active_chanels_count);
    recievedStatePtr->n = active_chanels_count;
    for (int i = 1; i <= active_chanels_count; ++i) {
        ChanelInfo *current_chanel = &(recievedStatePtr->chanel_mas[i-1]);
        std::list<std::shared_ptr<SegmentPlan> > test = (*m_data_chanel_plans)[i].segments();
        auto it = test.begin();
        while(it != test.end()) {
            auto current_segment = it->get();
            current_chanel->freq = current_segment->freq;
            current_chanel->ka_number = current_segment->ka_number;
            current_chanel->vec[0] = 123; // must be calculated
            current_chanel->vec[1] = 123; // must be calculated
            current_chanel->real_chanel_number = current_segment->chanel_number;
            current_chanel->pol = (*it)->pol;
            current_chanel->signal_level = 0; // must be calculated
            current_chanel->sector_number = current_segment->sector_number;
            current_chanel->sector_state = 0; // must be calculated
            current_chanel->sector_start = 0; // must be taken from sector plan
            current_chanel->sector_end = 0; // must be taken from sector plan
            ++it;
        }
    }
    emit reciveStateCreated(recievedStatePtr);
}
